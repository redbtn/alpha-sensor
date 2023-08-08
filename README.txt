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
Start all service (read_arduino & flask)
# service start_flask.sh status
# service start_flask.sh start

#Read data from Arduino:
cd /alpha-sensor
python3 read_arduino.py
chmod a+rw /dev/ttyACM0 /*if permission not given */
#If flask port already used:
fuser -k 5000/TCP
export FLASK_ENV=development
export FLASK_APP=dash.py
flask run --host=0.0.0.0

Check in browser: http://192.168.1.227:5000
Orange Pi default user: root/orangepi