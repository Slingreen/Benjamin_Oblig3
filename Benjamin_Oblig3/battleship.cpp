/**********************************************************************************************************
 *  @file    battleship.CPP
 *  @author  Benjamin A.E. Darici
 */
#include "battleship.h"
#include <cstdlib>	//	srand(), rand()
#include <ctime>	//	time()
#include <iostream> //  cout, cin, endl
#include "Function.h"


void playShip()
{
    system("CLS");
    if (Read_Command("Do you want to play against an AI? Y/n") == 'Y')
    {
        play2();
    }
    else
    {
        play();
    }
    
}

void makeEmptyBoard(char(&board)[M][N])
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            board[i][j] = BLANK;
        }
    }
}

int randomRow(int i) 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
    return  std::rand() % i;
}

int randomColumn(int i) 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
    return  std::rand() % i;
}

void writeLetters()
{
    char letter{ 'A' };
    std::cout << " |";
    for (int i = 0; i < N; i++)
    {
        std::cout << letter << '|';
        letter++;
    }
}

void makeBoard(int numberOfShips, char(&board)[M][N])
{
    int rndC, rndR;
    for (int i = 0; i < numberOfShips; i++)
    {
        do
        {
            rndR = randomRow();
            rndC = randomColumn();
        } while (board[rndR][rndC] == SHIP);
        board[rndR][rndC] = SHIP;
    }
}

void makeBoard3(int numberOfShips, char(&board)[M][N])
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
    int rndC, rndR;
    bool filled{ true },
        vertical{ false };
    for (int i = 0; i < numberOfShips; i++)
    {
        vertical = std::rand() % 2;
        do
        {
            filled = false;
            if (vertical)
            {
                rndR = randomRow();
                rndC = randomColumn(N-2);
                for (int j = 0; j < 3; j++)
                {
                    if (board[rndR][rndC + j] == SHIP)
                    {
                        filled = true;
                        break;
                    }
                }
            }
            else 
            {
                rndR = randomRow(N-2);
                rndC = randomColumn();
                for (int j = 0; j < 3; j++)
                {
                    if (board[rndR + j][rndC] == SHIP)
                    {
                        filled = true;
                        break;
                    }
                }
            }
        } while (filled);
        if (vertical)
        {
            for (int i = 0; i < 3; i++)
            {
                board[rndR][rndC + i] = SHIP;
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                board[rndR + i][rndC] = SHIP;
            }
        }
    }
}

void printBoard(char(&board)[M][N])
{
    std::cout << std::endl << "--------------";
    for (int i = 0; i < M; i++)
    {
        std::cout << std::endl << M-i;
        for (int j = 0; j < N; j++)
        {
                std::cout << "|" << board[i][j];
        }
        std::cout << "|";
    }
    std::cout << std::endl << "--------------" << std::endl;
    writeLetters();
}

void printPlayerBoard(char(&board)[M][N])
{
    for (int i = 0; i < M; i++)
    {
        std::cout << std::endl << M-i;
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == SHIP)
            {
                std::cout << "|" << " ";
            }
            else
            {
                std::cout << "|" << board[i][j];
            }
        }
        std::cout << "|";
    }
    std::cout << std::endl << " -------------" << std::endl;
    writeLetters();
    std::cout << std::endl;
}

void shoot(char(&board)[M][N], int &shots, int &hits)
{
    char collum;
    int row;
    std::cout << "Choose your target: " << std::endl;
    std::cin >> collum >> row;
    if (board[M-row][letterToNumber(toupper(collum))] == SHIP)
    {
        board[M - row][letterToNumber(toupper(collum))] = HIT;
        hits++;
    }
    else if (board[M - row][letterToNumber(toupper(collum))] == BLANK)
    {
        board[M - row][letterToNumber(toupper(collum))] = MISS;
    }
    shots--;
}

void play()
{
    char board[M][N]; // 2d array with M rows and N columns // you can use vectors too
    int numberOfHits{ 0 };
    int numberOfShips{ 0 };
    int numberOfShots{ 16 };
    
    bool win{ false };
    bool large{ false };

    makeEmptyBoard(board); 

    if (Read_Command("Do you want to play with large ships? Y/n") == 'Y')
    {
        numberOfShips = 2;
        makeBoard3(numberOfShips, board);
        large = true;
    }
    else
    {
        numberOfShips = 11;
        makeBoard(numberOfShips, board);
    }

    do
    {
        system("CLS");
        std::cout
            << "You have " << numberOfShots << " shot(s) and have "
            << numberOfHits << " hit(s) of " << numberOfShips << " ships." << std::endl
            << "--------------";
        printPlayerBoard(board);
        shoot(board, numberOfShots, numberOfHits);

        if (large)
        {
            if (numberOfHits == (numberOfShips * 3))
            {
                win = true;
            }
        }
        else
        {
            if (numberOfHits == numberOfShips)
            {
                win = true;
            }
        }
    } while (numberOfShots > 0 || win);
    std::cout << "Game over! Here are the ships you may have missed";
    printBoard(board);
}

void play2()
{
    char board[M][N]; // 2d array with M rows and N columns // you can use vectors too
    int numberOfHits{ 0 };
    int numberOfShips{ 0 };
    int numberOfShots{ 16 };

    bool win{ false };
    bool large{ false };

    char aiBoard[M][N];
    int numberOfAIHits{ 0 };
    bool aiWin{ false };

    makeEmptyBoard(board);
    makeEmptyBoard(aiBoard);

    if (Read_Command("Do you want to play with large ships? Y/n") == 'Y')
    {
        numberOfShips = 2;
        makeBoard3(numberOfShips, board);
        makeBoard3(numberOfShips, aiBoard);
        large = true;
    }
    else
    {
        numberOfShips = 11;
        makeBoard(numberOfShips, board);
        makeBoard(numberOfShips, aiBoard);
    }
    system("CLS");
    do
    {  
        std::cout
            << "Number of shots left: " << numberOfShots << std::endl
            << "Player has " <<numberOfHits << " hit(s), and ai has " << numberOfAIHits << " hit(s) of " 
            << numberOfShips << " ships." << std::endl
            << "Player board: \t\tAI board: " << std::endl
            << " ------------- \t\t -------------";
        printPlayerBoard2(board, aiBoard);
        shoot(board, numberOfShots, numberOfHits);
        AIshoot(aiBoard, numberOfAIHits, large);
        system("CLS");
        if (large)
        {
            if (numberOfHits == (numberOfShips * 3))
            {
                win = true;
                std::cout << "Player won";
            }
            else if (numberOfAIHits == (numberOfShips * 3))
            {
                aiWin = true;
                std::cout << "AI won";
            }
        }
        else
        {
            if (numberOfHits == numberOfShips)
            {
                win = true;
                std::cout << "Player won";
            }
            else if (numberOfAIHits == numberOfShips)
            {
                aiWin = true;
                std::cout << "AI won";
            }
        }

    } while (numberOfShots > 0 && !win && !aiWin);
    
    printBoard(board);
    std::cout << "\nHere are the ships you may have missed" << std::endl;
    printBoard(aiBoard);
    std::cout << "\nAnd here are the ships the ai may have missed\n" << std::endl;
}

void printPlayerBoard2(char(&board)[M][N], char(&aBoard)[M][N])
{
    for (int i = 0; i < M; i++)
    {
        std::cout << std::endl << M - i;
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == SHIP)
            {
                std::cout << "|" << " ";
            }
            else
            {
                std::cout << "|" << board[i][j];
            }
        }
        std::cout << "| \t\t" << M - i;
        for (int j = 0; j < N; j++)
        {
            if (aBoard[i][j] == SHIP)
            {
                std::cout << "|" << " ";
            }
            else
            {
                std::cout << "|" << aBoard[i][j];
            }
        }
        std::cout << "|";
    }
    std::cout << std::endl << " ------------- \t\t -------------" << std::endl;
    writeLetters();
    std::cout << "\t\t";
    writeLetters();
    std::cout << std::endl;
}

void AIshoot(char(&board)[M][N], int& hits, bool l)
{
    int collum{ 0 }, row{ 0 };
    bool target{ false };
    
    if (l)
    {
        if ((hits % 3) == 0)
        {
            do
            {
                row = randomRow();
                collum = randomColumn();
            } while (board[row][collum] == HIT || board[row][collum] == MISS);
        }
        else
        {
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (board[i][j] == HIT)
                    {

                        if (i < M - 1 && board[i + 1][j] == HIT)
                        {
                            if (i < M - 2 && board[i + 2][j] != HIT && board[i + 2][j] != MISS)
                            {
                                row = i + 2;
                                collum = j;
                                target = true;
                                break;
                            }
                            else if (i > 0 && board[i - 1][j] != HIT && board[i - 1][j] != MISS)
                            {
                                row = i - 1;
                                collum = j;
                                target = true;
                                break;
                            }
                        }
                        else if (j < N - 1 && board[i][j + 1] == HIT)
                        {
                            if (j < N - 2 && board[i][j + 2] != HIT && board[i][j + 2] != MISS)
                            {
                                row = i;
                                collum = j + 2;
                                target = true;
                                break;
                            }
                            else if (j > 0 && board[i][j - 1] != HIT && board[i][j - 1] != MISS)
                            {
                                row = i;
                                collum = j - 1;
                                target = true;
                                break;
                            }
                        }
                        else if (i > 0 && board[i - 1][j] == HIT)
                        {
                            if (i < M - 1 && board[i + 1][j] != HIT && board[i + 1][j] != MISS)
                            {
                                row = i + 1;
                                collum = j;
                                target = true;
                                break;
                            }
                            else if (i > 1 && board[i - 2][j] != HIT && board[i - 2][j] != MISS)
                            {
                                row = i - 2;
                                collum = j;
                                target = true;
                                break;
                            }
                        }
                        else if (j > 0 && board[i][j - 1] == HIT)
                        {
                            if (j < N - 1 && board[i][j + 1] != HIT && board[i][j + 1] != MISS)
                            {
                                row = i;
                                collum = j + 1;
                                target = true;
                                break;
                            }
                            else if (j > 1 && board[i][j - 2] != HIT && board[i][j - 2] != MISS)
                            {
                                row = i;
                                collum = j - 2;
                                target = true;
                                break;
                            }
                        }
                        else
                        {
                            if (i < M - 1 && board[i + 1][j] != HIT && board[i + 1][j] != MISS)
                            {
                                row = i + 1;
                                collum = j;
                                target = true;
                                break;
                            }
                            else if (j < N - 1 && board[i][j + 1] != HIT && board[i][j + 1] != MISS)
                            {
                                row = i;
                                collum = j + 1;
                                target = true;
                                break;
                            }
                            else if (i > 0 && board[i - 1][j] != HIT && board[i - 1][j] != MISS)
                            {
                                row = i - 1;
                                collum = j;
                                target = true;
                                break;
                            }
                            else if (j > 0 && board[i][j - 1] != HIT && board[i][j - 1] != MISS)
                            {
                                row = i;
                                collum = j - 1;
                                target = true;
                                break;
                            }
                        }
                    }
                }
            }
            if (!target)
            {
                do
                {
                    row = randomRow();
                    collum = randomColumn();
                } while (board[row][collum] == HIT || board[row][collum] == MISS);
            }
        }
    }
    else
    {
        do
        {
            row = randomRow();
            collum = randomColumn();
        } while (board[row][collum] == HIT || board[row][collum] == MISS);
    }

    if (board[row][collum] == SHIP)
    {
        board[row][collum] = HIT;
        hits++;
    }
    else if (board[row][collum] == BLANK)
    {
        board[row][collum] = MISS;
    }
}

int letterToNumber(char letter) // only big letters
{
    return static_cast<int>(letter) - 65;
}