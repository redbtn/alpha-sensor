#!/bin/bash

exec > /var/log/start_flask.log 2>&1

# Change permissions on /dev/ttyACM0
chmod a+rw /dev/ttyACM0

# Change to the directory where your Python script is located
cd /root/alpha-sensor/

# Start your Python script in the background and detach it from the terminal
nohup python3 read_arduino.py &

# Set environment variables for Flask
#export FLASK_ENV=development
export FLASK_APP=dash.py

# Start the Flask app, binding it to all network interfaces
flask run --host=0.0.0.0 &

# Log 
# echo "Start Flask" >> /var/log/start_flask.log

exit 0
