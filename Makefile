all:
	g++ -lpthread -std=c++11 legacy/test.cpp legacy/PiModule.cpp -o bin/legacy
	g++ 