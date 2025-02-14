from flask import Flask, render_template, request
import serial

app = Flask(__name__)

# Replace with your Arduino's serial port (e.g., 'COM3' for Windows or '/dev/ttyUSB0' for Linux)
ser = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/move_servo', methods=['POST'])
def move_servo():
    channel = request.form['channel']
    angle = request.form['angle']
    command = f"{channel} {angle}\n"
    ser.write(command.encode())
    return "OK"

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5001)
