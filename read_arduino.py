# root@orangepizerolts:~/alpha-sensor# cat read_arduino.py 
import serial
import time
import simplejson as json
from datetime import datetime
import os.path

# Open the serial connection to the Arduino Uno
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
time.sleep(2)

# Check if the data.json file exists
if os.path.exists('data.json'):
    # Load existing data from data.json
    with open('data.json', 'r') as file:
        existing_data = json.load(file)
        timestamps = existing_data['timestamp']
        h_values = existing_data['humidity']
        t_values = existing_data['temperature']
        index_values = existing_data['index']
else:
    # Initialize lists for storing the data
    timestamps = []
    h_values = []
    t_values = []
    index_values = []

# Read data from Arduino Uno
# Inside the while loop
while True:
    data = ser.readline().decode('utf-8').strip()
    if data:
        print("Received data:", data)
        h, t, i = data.split(", ")

        # Initialize variables to store converted values
        h_val, t_val, i_val = None, None, None

        # Extract values from the received data with error handling
        try:
            h_val = float(h.split(":")[1])
            t_val = float(t.split(":")[1])
            i_val = float(i.split(":")[1].rstrip(','))
        except ValueError as e:
            print(f"Error: {e}")

        # Get the current timestamp
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Append the values to the respective lists only if all conversions were successful
        if all(val is not None for val in [h_val, t_val, i_val]):
            timestamps.append(timestamp)
            h_values.append(h_val)
            t_values.append(t_val)
            index_values.append(i_val)

            # Create the data dictionary
            data_dict = {
                "timestamp": timestamps,
                "humidity": h_values,
                "temperature": t_values,
                "index": index_values
            }

            # Write data to data.json file
            with open('data.json', 'w') as file:
                json.dump(data_dict, file, indent=4)

    time.sleep(1)

# Close the serial connection
ser.close()