import serial
import time
import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, fftfreq
import csv
import threading

class StatAnalysis:
    def __init__(self, port='COM6', baudrate=115200):
        self.port = port
        self.baudrate = baudrate
        self.data = []
        self.ser = None
        self.recording_thread = None

    def open_port(self):
        self.ser = serial.Serial(self.port, self.baudrate)
        time.sleep(2)  # Wait for the serial connection to initialize

    def record_data(self, duration):
        def record():
            start_time = time.time()
            self.data = []
            timestampOld = 0

            print("Flushing buffers..")
            self.ser.flush()
            self.ser.reset_input_buffer()

            while time.time() - start_time < duration:
                if self.ser.in_waiting > 0:
                    line = self.ser.readline()
                    line = line.decode('utf-8')
                    line = line.replace('\x00', '')  # Remove null characters
                    if not line:  # Skip empty lines
                        continue
                    parts = line.split()
                    if len(parts) == 4:
                        timestamp, x, y, z = parts
                        try:
                            self.data.append([int(timestamp), float(x), float(y), float(z)])
                            if (int(timestamp) - int(timestampOld)) > 20000:
                                print("-------ERROR------")
                                print(timestampOld)
                                print(timestamp)
                                print([int(timestamp), float(x), float(y), float(z)])
                                print("------------------")
                            timestampOld = timestamp
                        except ValueError:
                            print("ValueError")
                            pass

            self.data = np.array(self.data)
            self.data = self.data[1:]  # Discard the first sample

        self.recording_thread = threading.Thread(target=record)
        self.recording_thread.start()

    def wait_for_recording(self):
        if self.recording_thread:
            self.recording_thread.join()

    def calculate_frame_frequency(self):
        timestamps = self.data[:, 0]
        time_diffs = np.diff(timestamps)
        frame_frequency = 1000 / np.mean(time_diffs)  # Convert to Hz
        return frame_frequency

    def plot_data(self, save_folder, plot_filename):
        timestamps = self.data[:, 0]
        x = self.data[:, 1]
        y = self.data[:, 2]
        z = self.data[:, 3]

        fig, axs = plt.subplots(3, 2, figsize=(15, 10))

        # Time-domain plots
        axs[0, 0].plot(timestamps, x, label='X')
        axs[1, 0].plot(timestamps, y, label='Y')
        axs[2, 0].plot(timestamps, z, label='Z')

        for i, axis in enumerate(['X', 'Y', 'Z']):
            axs[i, 0].set_title(f'{axis} over time')
            axs[i, 0].set_xlabel('Timestamp (ms)')
            axs[i, 0].set_ylabel(f'{axis}')
            axs[i, 0].legend()

        # FFT plots
        N = len(timestamps)
        T = (timestamps[-1] - timestamps[0]) / (N - 1) / 1000  # Sample spacing in seconds
        for i, data in enumerate([x, y, z]):
            yf = fft(data)
            xf = fftfreq(N, T)[:N // 2]
            axs[i, 1].plot(xf, 2.0 / N * np.abs(yf[:N // 2]), label=f'{["X", "Y", "Z"][i]} FFT')
            axs[i, 1].set_title(f'{["X", "Y", "Z"][i]} FFT')
            axs[i, 1].set_xlabel('Frequency (Hz)')
            axs[i, 1].set_ylabel('Amplitude')
            axs[i, 1].legend()

        plt.tight_layout()
        plot_filepath = os.path.join(save_folder, plot_filename)
        plt.savefig(plot_filepath)
        #plt.show()

    def save_to_csv(self, filename):
        header = ['Timestamp (ms)', 'X', 'Y', 'Z']
        with open(filename, mode='w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(header)
            writer.writerows(self.data)

    def close_port(self):
        if self.ser and self.ser.is_open:
            self.ser.close()

    def ensure_folder_exists(self, folder):
        if not os.path.exists(folder):
            os.makedirs(folder)

# Usage Example
if __name__ == "__main__":
    duration = 150  # Recording duration in seconds 2.5min
    save_folder = 'test_køkkenbord_150s'  # Change this folder name as needed
    filenames = ['fail_100']
    
    stat_analysis = StatAnalysis()
    stat_analysis.open_port()
    stat_analysis.ensure_folder_exists(save_folder)

    for filename in filenames:
        input(f"Press Enter to start recording for {filename}...")
        print(f"STARTING RECORDING FOR {filename}")
        
        stat_analysis.record_data(duration)
        stat_analysis.wait_for_recording()
        
        frame_frequency = stat_analysis.calculate_frame_frequency()
        print(f'Frame Frequency: {frame_frequency} Hz')
        
        output_filename = f"{filename}.csv"
        stat_analysis.save_to_csv(os.path.join(save_folder, output_filename))
        
        plot_filename = f"{filename}.png"
        stat_analysis.plot_data(save_folder, plot_filename)
        
        print(f"Saved data to {output_filename} and plot to {plot_filename}")

    stat_analysis.close_port()
    print("All recordings completed.")
