#include <iostream>
#include "IO_ControllerSerialClient.hpp"

// compile:
// g++ -std=c++17 -Wall -Wextra  main_example.cpp -o main_example.o 

int main (void)
{
    char option; 
    int pin;
    bool state;

    // initialise a io controller object:
    IO_ControllerSerialClient io_controller = IO_ControllerSerialClient("/dev/ttyUSB0");


    while (true)
    {
        std::cout << "\n\nEnter [r] to read a pin state, [w] to write a pin state, or [x] to exit: " << std::endl;
        std::cin >> option;

        if(option == 'r'){
            std::cout << "Enter the input pin number you want to read (0-3): " << std::endl;
            std::cin >> pin;
            if((pin < 0) || (pin > 3)){
                std::cerr << "ERROR: Pin Number " << pin << " is not an input!" << std::endl;
            }
            else{
                state = io_controller.readPinState(pin);
                std::cout << "Pin " << pin << " is on state " << state << std::endl;
            }
        }
        else if(option == 'w'){
            std::cout << "Enter the outpt pin number you want to write to (4-7), followed by the state (0/1): " << std::endl;
            std::cin >> pin >> state;
            if((pin < 4) || (pin > 7)){
                std::cerr << "ERROR: Pin Number " << pin << " is not an output!" << std::endl;
            }
            else{
                io_controller.writePinState(pin, state);
                std::cout << "Writing state " << state << " on pin " << pin << " .." << std::endl;
            }
        }
        else if(option == 'x'){
            break;
        }
        else{
            std::cerr << "ERROR: Undefined User Input! (" << option << ')' << std::endl;
        }
    }

    return EXIT_SUCCESS;
}