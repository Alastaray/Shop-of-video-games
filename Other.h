#pragma once
#include <conio.h>
#include <iostream>
#include "fun_console.h"
using namespace std;
#pragma warning(disable: 4996)


char* IntToChar(int value);
bool CompareStr(const char* value, const char* source);
void Move(char& key, int& x, int& y, int how_change_x = 0, int how_change_y = 0);


class Input
{
public:
	Input() { buff = 0; }
	~Input() { delete buff; }
	double GetDouble(int max_len, int min_len = 0, int px = 0, int py = 0, int indent_letf = 0, int indent_top = 0);
	int GetInt(int max_len, int min_len = 0, int px = 0, int py = 0, int indent_letf = 0, int indent_top = 0);
	char* GetStr(int max_len, int min_len = 0, int px = 0, int py = 0, int indent_letf = 0, int indent_top = 0);
	char* GetData(int max_len, int min_len = 0, int px = 0, int py = 0, int indent_letf = 0, int indent_top = 0);
	bool Success() { return buff[0]; }
	
private:
	char* buff;
	enum Keys
	{
		Esc = 27,
		Enter = 13,
		Backspace = 8,
		Space = 32,
		A = 'A',
		a = 'a',
		z = 'z',
		Z = 'Z',
		N0 = '0',
		N9 = '9',
		Dot = '.'
	};
	void DataPreparation(int max_len, int& px, int& py, int indent_letf = 0, int indent_top = 0);
	bool Ñomplement(int key, int& iter, int min_len, bool space = false);

};
