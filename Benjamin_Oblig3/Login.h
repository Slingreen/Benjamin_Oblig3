#pragma once
#include <string>

bool login();
void drawGrid(int(&pos)[2], char(&grid)[4][4]);
void movement(int(&pos)[2], bool& e);
void getPassword(std::string& p);
void newPassword();