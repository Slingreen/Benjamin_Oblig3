#pragma once

const int M{ 6 }, N{ 6 };
const char BLANK{ ' ' };
const char SHIP{ 'S' };
const char MISS{ 'M' };
const char HIT{ 'H' };

void playShip();
void makeEmptyBoard(char(&board)[M][N]);
int randomRow(int i = M);
int randomColumn(int i = N);
void writeLetters();
void makeBoard(int numberOfShips, char(&board)[M][N]);
void makeBoard3(int numberOfShips, char(&board)[M][N]);
void printBoard(char(&board)[M][N]);
void printPlayerBoard(char(&board)[M][N]);
void shoot(char(&board)[M][N], int& shots, int& hits);
void play();
void play2();
void printPlayerBoard2(char(&board)[M][N], char(&aBoard)[M][N]);
void AIshoot(char(&board)[M][N], int& hits, bool l);

int letterToNumber(char letter);