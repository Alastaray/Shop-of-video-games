#include "Functions.h"
char* IntToChar(int value)
{
	int len_value = 1,
		val = value;
	char str[20];
	while ((val /= 10) > 0) len_value++;
	for (int i = len_value - 1, j = 10, k = 1; i >= 0; i--, j *= 10, k *= 10)
	{
		str[i] = '0' + value % j / k;
	}
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
			if (value[0] == source[i] && value[1] == source[i + 1] && value[1] == source[i + 2] && i + 2 < strlen(source))
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