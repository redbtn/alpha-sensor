#!/bin/bash
chmod a+rw /dev/ttyACM0
cd /apps
export FLASK_ENV=development
export FLASK_APP=dash.py
python3 read_arduino.py &
flask run --host=0.0.0.0 &
