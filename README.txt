#Objective
This project try to combine Arduino Uno and Orange Pi Zero.
Arduino Uno read DHT22 sensor, control fan and send data to oled and serial port.
Orange Pi Zero will read data from serial port and save data into data.json and serve python flask as web service to provide simple realtime dashboard graphical data.

#Requirements:
Arduino Uno
Orange Pi Zero LTS
DHT22
OLED SSD1309
Relay 5V

#Software required:
Ubuntu Bionic 18.04
Python3
Pip3
Flask

Arduino Uno:
compile & install file sketch_dht_oled.ino

Orange Pi Zero:
git clone this repo

#Start & serve flask in the background and when server start:
# mv start_flask.sh /etc/init.d/
# chmod +x /etc/init.d/start_flask.sh
# update-rc.d start_flask.sh defaults

Troubleshoot:
#Make sure service are running
service --status-all
#Start all service (read_arduino & flask)
service start_flask.sh status
service start_flask.sh start

#Read data from Arduino:
cd /alpha-sensor
nohup python3 read_arduino.py &
chmod a+rw /dev/ttyACM0 /*if permission not given */

#If flask port already used:
fuser -k 5000/TCP
export FLASK_ENV=development
export FLASK_APP=dash.py
flask run --host=0.0.0.0

#If permission denied issues happen (in pc conn to opi through serial usb):
chown username /dev/ttyUSB0

#Check orangepi CPU temp:
cat /sys/class/thermal/thermal_zone*/temp

Check in browser: http://192.168.1.227:5000
Orange Pi default user: root/orangepi
