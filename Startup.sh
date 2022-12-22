
cd ~

cd /home/pi/RaspberryPiSensorCode/
g++ /home/pi/RaspberryPiSensorCode/rpi/lidar.cpp /home/pi/RaspberryPiSensorCode/rpi/src/lidarlite_v3.cpp -I . -o /home/pi/RaspberryPiSensorCode/bin/lidar.out
g++ -Wall -pthread /home/pi/RaspberryPiSensorCode/rpi/ultrasonic.cpp -I . -lpigpio -lrt -o /home/pi/RaspberryPiSensorCode/bin/us.out

cd ~

echo "[Unit]
Description=SensorUDP
After=multi-user.target
[Service]
Type=idle
ExecStart=./home/pi/RaspberryPiSensorCode/bin/lidar.out
[Install]
WantedBy=multi-user.target" | sudo tee /lib/systemd/system/sensorsUDP.service


sudo chmod 644 /lib/systemd/system/sensorsUDP.service
sudo systemctl daemon-reload
sudo systemctl enable sensorsUDP.service