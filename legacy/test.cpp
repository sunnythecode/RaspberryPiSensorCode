#include "PiModule.h"
#include <iostream>
#include <string>
#include <unistd.h>

int main() {
    /*
    std::cout << "check 0";
    PiModule pi = PiModule(0);
    //pi.pi_thread.detach();
    std::cout << "check 1";
    std::cout << pi.get_distance() << "." << std::endl;
    pi.pi_thread.detach();
    for (int i = 0; i < 10; i++) {
        std::cout << pi.get_distance() << std::endl;
        usleep(1000000);
    }
    

    pi.stop_server();
    
    std::cout << "stop";
    */
   PiModule pi = PiModule(0);
   pi.pi_thread.detach();
   while (1) {
       std::cout << pi.get_distance() << std::endl;
       usleep(1000000);
   }
   
   return 0;


}