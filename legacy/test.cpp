#include "PiModule.h"
#include <iostream>
#include <string>


int main() {
    
    PiModule pi = PiModule(0);
    pi.start_server();
    std::cout << pi.get_distance();
    pi.stop_server();
    std::cout << "stop";
    return 0;

}