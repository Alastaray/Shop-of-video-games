#include "Other.h"


char* IntToChar(int value)
{
	char str[100];
	int len_value = 1;
	bool negative = false;
	if (value < 0)
	{
		negative = true;
		len_value++;
		value -= value * 2;
	}
	int val = value;
	while ((val /= 10) > 0) len_value++;
	for (int i = len_value - 1, j = 10, k = 1; i >= negative; i--, j *= 10, k *= 10)
	{
		str[i] = '0' + value % j / k;
	}
	if (negative)str[0] = '-';
	str[len_value] = '\0';
	return str;
}
bool CompareStr(const char* value, const char* source)
{
	int len = strlen(value),
		number_let = 0;
	switch (len)
	{
	case 1:
		for (int i = 0; i < strlen(source); i++)
			if (value[0] == source[i])
				return true;
		break;
	case 2:
		for (int i = 0; i < strlen(source); i++)
			if (value[0] == source[i] && value[1] == source[i + 1])
				return true;
	case 3:
		for (int i = 0; i < strlen(source); i++)
			if (value[0] == source[i] && value[1] == source[i + 1] && value[1] == source[i + 2] && (i + 2) < strlen(source))
				return true;
	default:
		for (int i = 0; i < len; i++)
			if (value[i] == source[i])
				number_let++;
		break;
	}

	if (number_let == len)return true;
	else return false;
}
void Move(char& key, int& x, int& y, int how_change_x, int how_change_y)
{
	key = _getch();
	if (key == 'w')y -= how_change_y;
	if (key == 's')y += how_change_y;
	if (key == 'd')x += how_change_x;
	if (key == 'a')x -= how_change_x;
	if (key == -32)
	{
		key = _getch();
		//down
		if (key == 80) y += how_change_y;
		//up
		if (key == 72) y -= how_change_y;
		//left
		if (key == 75) x -= how_change_x;
		//right
		if (key == 77) x += how_change_x;
	}
}



int Input::GetInt(int max_len, int min_len, int px, int py, int indent_letf, int indent_top)
{
	DataPreparation(max_len, px, py, indent_letf, indent_top);
	int key, i = 0;
	while (i < max_len)
	{
		key = _getch();
		if (key == 27) { ShowCaret(false);  buff[0] = 0; return 0; }
		if (key == 13) { if (i >= min_len)break; }
		if (key == 8)
		{
			buff[--i] = 0;
			GotoXY(GetCurrentX() - 1, GetCurrentY());
			cout << " ";
		}
		if (key >= '0' && key <= '9') {
			buff[i] = key;
			i++;
			buff[i] = 0;
		}
		GotoXY(px, py);
		cout << buff;
	}
	ShowCaret(false);
	return atoi(buff);
}
double Input::GetDouble(int max_len, int min_len, int px, int py, int indent_letf, int indent_top)
{
	DataPreparation(max_len, px, py, indent_letf, indent_top);
	int key, i = 0;
	bool is_dot = false;
	while (i < max_len)
	{
		key = _getch();
		if (key == 27) { ShowCaret(false);  buff[0] = 0; return 0; }
		if (key == 13) { if (i >= min_len)break; }
		if (key == 8)
		{
			buff[--i] = 0;
			GotoXY(GetCurrentX() - 1, GetCurrentY());
			cout << " ";
		}
		if ((key >= '0' && key <= '9') || (key == '.' && !is_dot))
		{
			if (key == '.')is_dot = true;
			buff[i] = key;
			i++;
			buff[i] = 0;
		}
		GotoXY(px, py);
		cout << buff;
	}
	ShowCaret(false);
	return atof(buff);
}
char* Input::GetStr(int max_len, int min_len, int px, int py, int indent_letf, int indent_top)
{
	DataPreparation(max_len, px, py, indent_letf, indent_top);
	int key, i = 0;
	while (i < max_len)
	{
		key = _getch();
		if (key == 27) { ShowCaret(false);  buff[0] = 0; return buff; }
		if (key == 13) { if (i >= min_len)break; }
		if (key == 8)
		{
			buff[--i] = 0;
			GotoXY(GetCurrentX() - 1, GetCurrentY());
			cout << " ";
		}
		if (key == 32)
		{
			buff[i] = key;
			i++;
			buff[i] = 0;
		}
		if ((key >= 'A' && key <= 'Z' && !i) || (key >= 'a' && key <= 'z'))
		{
			buff[i] = key;
			i++;
			buff[i] = 0;
		}
		GotoXY(px, py);
		cout << buff;
	}
	ShowCaret(false);
	return buff;
}
char* Input::GetData(int max_len, int min_len, int px, int py, int indent_letf, int indent_top)
{
	DataPreparation(max_len, px, py, indent_letf, indent_top);
	int key, i = 0;
	bool is_dot = false;
	while (i < max_len)
	{
		key = _getch();
		if (key == 27) { ShowCaret(false);  buff[0] = 0; return buff; }
		if (key == 13) { if (i >= min_len)break; }
		if (key == 8)
		{
			buff[--i] = 0;
			GotoXY(GetCurrentX() - 1, GetCurrentY());
			cout << " ";
		}
		if (key == 32)
		{
			buff[i] = key;
			i++;
			buff[i] = 0;
		}
		if ((key >= 'A' && key <= 'Z' && !i) || (key >= 'a' && key <= 'z') || (key >= '0' && key <= '9') || (key == '.' && !is_dot))
		{
			if (key == '.')is_dot = true;
			buff[i] = key;
			i++;
			buff[i] = 0;
		}
		GotoXY(px, py);
		cout << buff;
	}
	ShowCaret(false);
	return buff;
}
void Input::DataPreparation(int max_len, int& px, int& py, int indent_letf, int indent_top)
{
	ShowCaret(true);
	if (buff)delete buff;
	buff = new char[(max_len + 1)];
	buff[0] = 0;
	if (!px)px = GetCurrentX() + indent_letf;
	if (!py)py = GetCurrentY() + indent_top;
	GotoXY(px, py);
	for (int i = 0; i < max_len; i++)
		cout << " ";
	GotoXY(px, py);
}