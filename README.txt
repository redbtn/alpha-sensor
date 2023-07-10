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

#Start & serve flask in the background and when server start:
# mv start_flask.sh /etc/init.d/
# chmod +x /etc/init.d/start_flask.sh
# update-rc.d start_flask.sh defaults

#To start immediately without reboot or check the service status:
# service start_flask.sh start
# service start_flask.sh status
