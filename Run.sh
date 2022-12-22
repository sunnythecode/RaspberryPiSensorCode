cd ~

cd /home/pi/RaspberryPiSensorCode/
g++ /home/pi/RaspberryPiSensorCode/rpi/lidar.cpp /home/pi/RaspberryPiSensorCode/rpi/src/lidarlite_v3.cpp -I . -o /home/pi/RaspberryPiSensorCode/bin/lidar.out
g++ -Wall -pthread /home/pi/RaspberryPiSensorCode/rpi/ultrasonic.cpp -I . -lpigpio -lrt -o /home/pi/RaspberryPiSensorCode/bin/us.out
sudo ./home/pi/RaspberryPiSensorCode/bin/lidar.out