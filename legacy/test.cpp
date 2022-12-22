#include "PiModule.h"
#include <iostream>
#include <string>
#include <unistd.h>

int main() {
    std::cout << "check 0";
    PiModule pi = PiModule(0);
    //pi.pi_thread.detach();
    std::cout << "check 1";
    for (int i = 0; i < 10; i++) {
        std::cout << pi.get_distance();
        usleep(1000000);
    }
     
    pi.stop_server();
    std::cout << "stop";
    return 0;

}