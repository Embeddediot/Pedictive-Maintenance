import serial
import numpy as np
import os
import threading
import queue
from tensorflow.keras.models import load_model

print(os.getcwd())

# Load your Keras model
# model = load_model('model.keras')
model = load_model('C:/Users/uller/OneDrive - Danmarks Tekniske Universitet/Uni/Kandidat/Sommer semester/SpecialCourse/GIT/Pedictive-Maintenance/Python/model.keras')


# Initialize the serial port
ser = serial.Serial('COM3', 115200, timeout=1)

# Thread-safe queue to hold the data for inference
data_queue = queue.Queue()

def parse_data(data_lines):
    """
    Parse the incoming data lines and extract features.
    """
    data = {'X': {}, 'Y': {}, 'Z': {}}
    for line in data_lines:
        try:
            parts = line.split(':')
            axis = parts[0].strip()
            if axis in ['X', 'Y', 'Z']:
                features = line.split(',')
                var = float(features[0].split(':')[2].strip())
                kurtosis = float(features[1].split(':')[1].strip())
                rms = float(features[2].split(':')[1].strip())
                data[axis] = {
                    f'{axis}_var': var,
                    f'{axis}_kurtosis': kurtosis,
                    f'{axis}_rms': rms
                }
        except (IndexError, ValueError) as e:
            print(f"Error parsing line '{line}': {e}")
            continue
    return data

def get_data():
    """
    Collect data from the serial port until we have data for all axes.
    """
    while True:
        data_lines = []
        for _ in range(3):
            line = ser.readline().decode('utf-8').strip()
            if line:
                data_lines.append(line)
        if len(data_lines) == 3:
            data = parse_data(data_lines)
            data_queue.put(data)

def prepare_input(data):
    """
    Prepare the input data array for the model.
    """
    data_array = np.array([
        data['X']['X_var'], data['Y']['Y_var'], data['Z']['Z_var'],
        data['X']['X_kurtosis'], data['Y']['Y_kurtosis'], data['Z']['Z_kurtosis'],
        data['X']['X_rms'], data['Y']['Y_rms'], data['Z']['Z_rms']
    ])
    reshaped_data = data_array.reshape(1, 9)
    return reshaped_data

def run_inference():
    """
    Run inference using the Keras model.
    """
    Classes = ['Fail', 'Idle', 'Normal_50', 'Normal_100', 'Blocked']
    
    while True:
        if not data_queue.empty():
            data = data_queue.get()
            input_data = prepare_input(data)
            result = model.predict(input_data)
            predicted_class = np.argmax(result, axis=1)
            print(Classes[int(predicted_class)])

if __name__ == '__main__':
    # Start the data collection thread
    data_thread = threading.Thread(target=get_data)
    data_thread.daemon = True
    data_thread.start()

    # Start the inference loop
    run_inference()
