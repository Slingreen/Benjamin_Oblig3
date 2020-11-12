/**********************************************************************************************************
 *  @file    Function.CPP
 *  @author  Benjamin A.E. Darici
 */
#include "Function.h"   //  writeMenu(), Read_Command()
#include <iostream>     //  cout, toupper()

 // A tiny function to write out the choices the switch provides in the main function
void writeMenu()
{
    std::cout << "The following commands are available: \n"
        << "\t 1    Change Password\n"
        << "\t 2    Play battleship\n"
        << "\t 3    Quits program\n";
}

// A tiny function just to read input commands
char Read_Command(const char* c)
{
    char command;
    std::cout << c << ":  ";
    std::cin >> command;
    return(toupper(command));
}
