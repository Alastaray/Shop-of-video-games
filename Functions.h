#pragma once
#include <conio.h>
#include <iostream>
char* IntToChar(int value);
bool CompareStr(const char* value, const char* source);
void Move(char& key, int& x, int& y, int how_change_x = 0, int how_change_y = 0);
