import tkinter as tk
from tkinter import ttk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import serial
import threading
import time

class SerialPlotter:
    def __init__(self, root):
        self.root = root
        self.root.title("Serial Data Plotter")
        
        self.fig = Figure()
        
        self.ax1 = self.fig.add_subplot(411)
        self.ax2 = self.fig.add_subplot(412)
        self.ax3 = self.fig.add_subplot(413)
        self.ax4 = self.fig.add_subplot(414)
        
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.root)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        
        self.x_data = []
        self.y_data = []
        self.z_data = []
        self.temp_data = []
        
        self.serial_port = serial.Serial('COM3', 115200, timeout=1)
        
        self.update_plot()
        self.read_serial_data()
    
    def read_serial_data(self):
        threading.Thread(target=self.read_from_serial, daemon=True).start()
    
    def read_from_serial(self):
        while True:
            try:
                line = self.serial_port.readline().decode('utf-8').strip()
                if line.startswith("Acceleration"):
                    _, values = line.split(':')
                    x, y, z = values.split()
                    self.x_data.append(float(x))
                    self.y_data.append(float(y))
                    self.z_data.append(float(z))
                elif line.startswith("Temperature"):
                    _, temp = line.split(':')
                    self.temp_data.append(float(temp))
            except ValueError as e:
                print(f"Error parsing line: {line} - {e}")
            time.sleep(0.01)
    
    def update_plot(self):
        len = -1000
        self.ax1.clear()
        self.ax1.plot(self.x_data[len:], label='X')
        self.ax1.set_title('X Acceleration')
        self.ax1.legend()
        
        self.ax2.clear()
        self.ax2.plot(self.y_data[len:], label='Y')
        self.ax2.set_title('Y Acceleration')
        self.ax2.legend()
        
        self.ax3.clear()
        self.ax3.plot(self.z_data[len:], label='Z')
        self.ax3.set_title('Z Acceleration')
        self.ax3.legend()
        
        self.ax4.clear()
        self.ax4.plot(self.temp_data[len:], label='Temperature')
        self.ax4.set_title('Temperature')
        self.ax4.legend()
        
        self.canvas.draw()
        self.root.after(100, self.update_plot)

if __name__ == "__main__":
    root = tk.Tk()
    app = SerialPlotter(root)
    root.mainloop()
