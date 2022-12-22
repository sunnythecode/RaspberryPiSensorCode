#include "PiModule.h"

// Server side implementation of UDP client-server model


#define PORT	 8080
#define MAXLINE 1024
	
PiModule::PiModule(int inputID) {
	ID = std::to_string(inputID);
	stop_thread = false;
}



void PiModule::run_update() {
	int n;
	socklen_t len;
	const char *hello = "Hello from server";
	while (!stop_thread) {
		n = recvfrom(sockfd_g, (char *)buffer_g, MAXLINE,
					MSG_WAITALL, ( struct sockaddr *) &cliaddr_g,
					&len);
		buffer_g[n] = '\0';
		printf("Client : %s\n", buffer_g);
		//sendto(sockfd_g, (const char *)hello, strlen(hello), 0, (const struct sockaddr *) &cliaddr_g, len);
		
		
		std::string buffer_str(buffer_g);
		if (buffer_str.rfind(ID + ":") == 0) { // If multiple Pis r sending, check ID prefix -> "0:data" or "1:data" where 0 and 1 are RPI IDs
			current_val = std::atof(buffer_g);
		}
		
		//frc::SmartDashboard::PutNumber(buffer_g, 0);
	}
}

void PiModule::start_server() {
    
	int sockfd;
	char buffer[MAXLINE];
	const char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int n;
    socklen_t len;
	
	sockfd_g = sockfd;
	buffer_g = buffer;
	cliaddr_g = cliaddr;

	len = sizeof(cliaddr); //len is value/result
	//std::thread UDP_thread([] {run_update());
	run_update();
	
}

double PiModule::get_distance() { return current_val; }

bool PiModule::stop_server() {
	stop_thread = true;
	//UDP_thread.join();
	return true;
}

