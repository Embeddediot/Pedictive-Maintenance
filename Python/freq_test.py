import tkinter as tk
from tkinter import scrolledtext
import serial
import threading
import time

class ComPortTester:
    def __init__(self, master):
        self.master = master
        self.master.title("COM Port Frame Frequency Tester")
        
        self.label = tk.Label(master, text="COM Port:")
        self.label.pack()
        
        self.com_port_entry = tk.Entry(master)
        self.com_port_entry.insert(0, "COM6")  # Default to COM6
        self.com_port_entry.pack()
        
        self.start_button = tk.Button(master, text="Start", command=self.start_test)
        self.start_button.pack()
        
        self.stop_button = tk.Button(master, text="Stop", command=self.stop_test)
        self.stop_button.pack()
        
        self.output_text = scrolledtext.ScrolledText(master, wrap=tk.WORD, width=50, height=20)
        self.output_text.pack()
        
        self.frame_label = tk.Label(master, text="Frame Frequency: N/A")
        self.frame_label.pack()
        
        self.running = False
        self.serial_thread = None

    def start_test(self):
        self.running = True
        self.output_text.insert(tk.END, "Starting...\n")
        self.serial_thread = threading.Thread(target=self.read_com_port)
        self.serial_thread.start()

    def stop_test(self):
        self.running = False
        if self.serial_thread:
            self.serial_thread.join()
        self.output_text.insert(tk.END, "Stopped.\n")
    
    def read_com_port(self):
        com_port = self.com_port_entry.get()
        try:
            ser = serial.Serial(com_port, 115200, timeout=1)
        except serial.SerialException as e:
            self.output_text.insert(tk.END, f"Error opening COM port: {e}\n")
            return

        frame_count = 0
        start_time = time.time()

        while self.running:
            try:
                line = ser.readline().decode('utf-8').strip()
                self.output_text.insert(tk.END, f"Raw data: {line}\n")
                if line == "test":
                    frame_count += 1
                    elapsed_time = time.time() - start_time
                    if elapsed_time > 0:
                        frame_frequency = frame_count / elapsed_time
                        self.frame_label.config(text=f"Frame Frequency: {frame_frequency:.2f} frames/sec")
                    
                    self.output_text.insert(tk.END, f"Parsed data: {line}\n")
                    self.output_text.see(tk.END)
                else:
                    self.output_text.insert(tk.END, f"Invalid data format: {line}\n")
                    self.output_text.see(tk.END)

            except Exception as e:
                self.output_text.insert(tk.END, f"Error reading from COM port: {e}\n")
                self.output_text.see(tk.END)

        ser.close()

if __name__ == "__main__":
    root = tk.Tk()
    app = ComPortTester(root)
    root.mainloop()
