#include <iostream>
#include "include/lidarlite_v3.h"
#include "config.h"


#include <linux/types.h>
#include <cstdio>
#include <unistd.h>
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
int sockfd;
char buffer[MAXLINE];

struct sockaddr_in	 servaddr;
LIDARLite_v3 myLidarLite;


void start_server() {
    
	
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
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &trueflag, sizeof trueflag);
	servaddr.sin_addr.s_addr = inet_addr("255.255.255.255");
	
	}

void sendmessage(const char* inp) {

	const char *hello = inp;
	int n;
    socklen_t len;
		
	sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("Hello message sent.\n");
			
	//n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
	//buffer[n] = '\0';
	//printf("Server : %s\n", buffer);
    //printf(buffer);
	
	//close(sockfd);
}



int main () 
{
    myLidarLite.i2c_init();
    myLidarLite.configure(lidar_mode);
    __u16 distance;
	__u8 busyflag;
    start_server();
    while (true) // for example: 100 measurements
    {

		if (busyflag == 0x00) {
			myLidarLite.takeRange();
			distance = myLidarLite.readDistance();
			string temp = to_string(distance);
			string msg = ID + temp;
			cout << msg;

			sendmessage(msg.c_str());
			usleep(10000);

		}

    }

    return 0;
}
