all:
	g++ rpi/lidar.cpp rpi/src/lidarlite_v3.cpp -I . -o bin/lidar.out
	g++ -Wall -pthread rpi/ultrasonic.cpp -I . -lpigpio -lrt -o bin/us.out
	g++ -lpthread -pthread -std=c++11 legacy/test.cpp legacy/PiModule.cpp -o bin/legacy.out