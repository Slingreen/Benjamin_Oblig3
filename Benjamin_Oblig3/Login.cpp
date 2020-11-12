/**********************************************************************************************************
 *  @file    login.CPP
 *  @author  Benjamin A.E. Darici
 */
#include "login.h"  //  login(), drawGrid(), movement()
#include <iostream> //  toupper(), cout, endl
#include <conio.h>  //  _getch()
#include <string>   // string, to_string()
#include <fstream>

 //	A "main" function for the login page
bool login()
{
    char grid[4][4]{
        {'A','B','C','D'},
        {'E','F','G','H'},
        {'I','J','K','L'},
        {'M','N','O','P'} };
    int pos[2]{ 0,0 },
        attempt{ 0 };
    bool enter;
    std::string pasword, answer;

    getPassword(answer);
    do
    {
        pos[0] = pos[1] = 0;
        pasword = "";
        enter = false;
        do
        {
            std::cout << "Enter password: " << std::endl;
            drawGrid(pos, grid);
            pasword += (grid[pos[0]][pos[1]]);
            movement(pos, enter);
            system("CLS");
        } while (!enter);
        if (pasword == answer) {
            return true;
        }
        attempt++;
    } while (attempt < 3);

    return false;
}

//  Draws the grid from where the input is taken
void drawGrid(int(&pos)[2], char(&grid)[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        std::cout << std::endl << "------------------" << std::endl;
        for (int j = 0; j < 4; j++)
        {
            if (i == pos[0] && j == pos[1]) {
                std::cout << " | *";
            }
            else
            {
                std::cout << " | " << grid[i][j];
            }
        }
        std::cout << " | ";
    }
    std::cout << std::endl << "------------------" << std::endl;
}

//  Movement options for the login grid
void movement(int(&pos)[2], bool& e)
{
    char c;
    bool move = false;
    while (!move)
    {
        c = _getch();
        if (toupper(c) == 'W')
        {
            if (pos[0] != 0) {
                pos[0] -= 1;
                move = true;
            }
        }
        else if (toupper(c) == 'A')
        {
            if (pos[1] != 0) {
                pos[1] -= 1;
                move = true;
            }
        }
        else if (toupper(c) == 'S')
        {
            if (pos[0] != 3) {
                pos[0] += 1;
                move = true;
            }
        }
        else if (toupper(c) == 'D')
        {
            if (pos[1] != 3) {
                pos[1] += 1;
                move = true;
            }
        }
        else if (c == 13)
        {
            e = true;
            move = true;
        }
    }
}

void getPassword(std::string& p) {
    std::fstream File("pword.txt", std::ios::in);
    if (File)
    {
        //perror("File exists");
        std::getline(File, p);
    }
    else
    {
        perror("File ");
    }
    File.close();
}

void newPassword() {
    std::fstream File("pword.txt", std::ios::out);
    std::string pasword{""};
    char grid[4][4]{
        {'A','B','C','D'},
        {'E','F','G','H'},
        {'I','J','K','L'},
        {'M','N','O','P'} };
    int pos[2]{ 0,0 };
    bool enter = false;
    do
    {
        std::cout << "Enter password: " << std::endl;
        drawGrid(pos, grid);
        pasword += (grid[pos[0]][pos[1]]);
        movement(pos, enter);
        system("CLS");
    } while (!enter);
    File << pasword;
    File.close();
}