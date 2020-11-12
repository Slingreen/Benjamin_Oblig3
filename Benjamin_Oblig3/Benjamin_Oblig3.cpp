/**********************************************************************************************************
 *      3rd obligatory assignment, Battleship and login
 *
 *      A program that allows you to play Battleship after you have succesfully loged in
 *
 *  @file    Benjamin_Oblig3.CPP
 *  @author  Benjamin A.E. Darici
 */

#include <iostream>
#include "Function.h"
#include "Login.h"
#include "battleship.h"

int main()
{
    char command{ ' ' };
    if (login())
    {
        writeMenu();

        command = Read_Command("Command");

        while (command != '3')
        {
            std::cin.ignore(32767, '\n');
            switch (command)
            {
            case '1': newPassword(); break;
            case '2': playShip(); break;
            default:
                std::cout << "Wrong input ... Do you want to try again: ";
                command = Read_Command("(y / n)");
                if (command == 'N')
                {
                    return 0;
                }
                break;
            }
            writeMenu();
            command = Read_Command("Command");
        }
    }
}