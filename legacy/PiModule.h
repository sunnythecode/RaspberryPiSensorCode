#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <thread>
#include <string>
#include <iostream>

class PiModule {
    public:
    std::string ID;
    bool stop_thread = false;
    
    PiModule(int inputID); //EVERYTHING NEEDS TO BE NONSTATIC

    void start_server(); // Run this function once and ur good to go (its threaded)
    double current_val = -1;
    double get_distance();
    double run_update();
    bool stop_server();

    int sockfd_g;
    char* buffer_g;
    struct sockaddr_in servaddr, cliaddr_g;



};