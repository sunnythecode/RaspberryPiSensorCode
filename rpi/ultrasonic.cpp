#include <pigpio.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT	 8080
#define MAXLINE 1024

using namespace std;


struct timeval tv;
string ID = "0:"

void sendmessage(const char* inp) {
    int sockfd;
	char buffer[MAXLINE];
	const char *hello = inp;
	struct sockaddr_in	 servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	int trueflag = 1;
	setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &trueflag, sizeof trueflag
	servaddr.sin_addr.s_addr = inet_addr("255.255.255.255");
		
	int n;
    socklen_t len;
		
	sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("Hello message sent.\n");
			
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	buffer[n] = '\0';
	//printf("Server : %s\n", buffer);
    printf(buffer);
	
	close(sockfd);
}

double getTime()
{
	gettimeofday(&tv, NULL);

	return (double)tv.tv_sec + (double)tv.tv_usec * 0.000001;
}

// https://en.wikipedia.org/wiki/Speed_of_sound
// https://www.google.com/search?q=343+m%2Fs+to+cm%2Fs&oq=343+m%2Fs+to+cm%2Fs&aqs=chrome..69i57j6.443j0j9&sourceid=chrome&ie=UTF-8
int coefficient = 17150; // it should be selected experimentally - it is half of speed of sound in air in cm/s

int TRIG = 4; // BCM/GPIO pin number
int ECHO = 17; // BCM/GPIO pin number

void initializePins()
{
	gpioSetMode(TRIG, PI_OUTPUT);
	gpioSetMode(ECHO, PI_INPUT);
}

bool waitValue(int value, int limit = 1000000) // use 1000000 to increase measurement distance
{
	for(int i = 0; gpioRead(ECHO) == value; ++i)
	{
		if(i >= limit)
			return false;
	}

	return true;
}

double detectDistance()
{
	gpioWrite(TRIG, 0); // reset rangefinder state
	usleep(100000); // wait for reset state - use 100000 to speedup program
	gpioWrite(TRIG, 1); // hi state runs rangefinder measurement
	usleep(10); // 10 us of hi level is necessary to start measurement - depended on rangefinder model 
	gpioWrite(TRIG, 0); // prepare rangefinder for measurement

	if(waitValue(0)) // wait until lo level is achieved on echo pin
	{
		double pulseStart = getTime();

		if(waitValue(1)) // wait until hi level is achieved on echo pin - hi level duration is proportional to distance
		{
			double pulseEnd = getTime();

			double duration = pulseEnd - pulseStart;
			double distance = duration * coefficient;

			return distance;
		}
	}

	cout << "Measurement error!"; 

	// Troubleshooting:
	// - check correctness of pin connection, 
	// - check supply in case of many devices connected,
	// - check maximal supported distance by rangefinder

	return 0.0 / 0.0;
}

int main () 
{
	if(gpioInitialise() < 0)
		cout << "PIGPIO initialisation failure!" << endl; 

	else
	{
		cout << "PIGPIO initialisation success!" << endl;

		initializePins();

		for(int i = 0; i < 10; ++i) // for example: 100 measurements
		{
			double distance = detectDistance();
			string temp = to_string(distance);

			sendmessage(ID + temp);
		}

		gpioTerminate();
	}

	return 0; 
}
