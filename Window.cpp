#include "Window.h"





Window::Window(unsigned int _width, unsigned int _height, unsigned int position, int indent_letf, int indent_top)
{
	borders[TopLeftAngle] = 218;
	borders[TopRightAngle] = 191;
	borders[BotLeftAngle] = 192;
	borders[BotRightAngle] = 217;
	borders[HorizontalLine] = 196;
	borders[VerticalLine] = 179;
	borders[TopCrosshair] = 194;
	borders[BotCrosshair] = 193;
	borders[LeftCrosshair] = 195;
	borders[RightCrosshair] = 180;
	borders[Crosshair] = 197;
	txcolor = White;
	bgcolor = Black;
	activeTxcolor = Black;
	activeBgcolor = White;
	SetColor(txcolor, bgcolor);
	ShowCaret(false);
	SetWinParam(_width, _height, position, indent_letf, indent_top);
}
Window::~Window()
{
	SetColor(txcolor, bgcolor);
}
void Window::DrawBox()
{
	GotoXY(px, py);
	cout << borders[TopLeftAngle];
	for (int i = 0; i < GetWidth(); i++)
	{
		cout << borders[HorizontalLine];
	}
	cout << borders[TopRightAngle];
	GotoXY(px, py + 1);

	for (int i = 0; i < GetHeight(); i++)
	{
		cout << borders[VerticalLine];
		for (int j = 0; j < GetWidth(); j++)
		{
			cout << " ";
		}
		cout << borders[VerticalLine];
		GotoXY(px, py + 2 + i);
	}
	cout << borders[BotLeftAngle];
	for (int i = 0; i < GetWidth(); i++)
	{
		cout << borders[HorizontalLine];
	}
	cout << borders[BotRightAngle] << endl;

}
void Window::FillLine(int _x, int _y)
{
	GotoXY(GetX()+_x,GetY() + _y);
	for (int i = 0; i < GetWidth(); i++) {
		cout << " ";
	}

}
void Window::SetWinParam(unsigned int _width, unsigned int _height, unsigned int position, int indent_letf, int indent_top)
{
	height = _height;
	width = _width;
	switch (position)
	{
	case LeftTop:
		px = 0 + indent_letf;
		py = 0 + indent_top;
		if (width >= 120)width = 120;
		break;
	case LeftBot:
		px = 0 + indent_letf;
		py = 15 + indent_top;
		if (width >= 120)width = 120;
		break;
	case CenterTop:
		px = 40 + indent_letf;
		py = 0 + indent_top;
		if (width >= 80)width = 80;
		break;
	case CenterBot:
		px = 40 + indent_letf;
		py = 15 + indent_top;
		if (width >= 80)width = 80;
		break;
	case RightTop:
		px = 80 + indent_letf;
		py = 0 + indent_top;
		if (width >= 40)width = 40;
		break;
	case RightBot:
		px = 80 + indent_letf;
		py = 15 + indent_top;
		if (width >= 40)width = 40;
		break;
	default:
		cout << "Îøèáêà!" << endl;
		break;
	}

}

void Menu::SetMenuParam(int indent_letf, int indent_top)
{
	if (menu.GetCount())
	{
		int width = 0,len = 0;
		for (int i = 0; i < menu.GetCount(); i++)
		{
			len = strlen(menu[i]);
			if (width < len)width = len;
		}
		SetWinParam(width + 8, menu.GetCount() * 2 + 1, position, indent_letf, indent_top);
	}
}
int Menu::DoMenu()
{
	char key;
	int active = 0,
		step = 2;
	while (true)
	{
		DrawMenu();
		FillLine(menu[active/ step],3,active);
		Move(key, active, active, 0, step);
		if (key == 13)return active / step;
		if (key == 27)return -1;
		if (active < 0)active = GetSizeMenu()-1;
		if (active >= GetSizeMenu()* step) active = 0;
	}
}
void Menu::DrawMenu()
{
	DrawBox();
	for (int i = 0; i < GetSizeMenu(); i++)
	{
		WriteLine(menu[i], 3, i * 2);
	}
}





Table::Table(unsigned int _width, unsigned int _height, unsigned int position, unsigned int _cols, unsigned int _rows, int indent_letf, int indent_top) :Window(_width, _height, position, indent_letf, indent_top)
{
	SetCols(_cols);
	SetRows(_rows);
}
void Table::FillLine(int _x, int _y)
{

	for (int i = 0; i < size_row - 1; i++)
	{
		GotoXY(GetX() + _x, GetY() + _y + i);
		for (int j = 0; j < size_col - 1; j++)
		{
			cout << " ";
		}
	}
}
void Table::DrawCols()
{
	while (width < cols * 2)cols--;
	for (int i = 0; i < height; i++)
	{
		GotoXY(GetX(), py + i);

		for (int j = 1; j <= GetWidth(); j++)
		{
			if (i == 0 &&
				j % size_col == 0 &&
				j + size_col - 2 <= GetWidth())
				cout << borders[TopCrosshair];

			else if (i == height - 1 &&
				j % size_col == 0 &&
				j + size_col - 2 <= GetWidth())
				cout << borders[BotCrosshair];

			else if (j % size_col == 0 &&
				j + size_col - 2 <= GetWidth())
				cout << borders[VerticalLine];

			else if (i == 0 || i == height - 1)
				cout << borders[HorizontalLine];

			else
				cout << " ";
		}
	}
}
void Table::DrawRows()
{
	while (height < rows * 2)rows--;
	
	int row_size = 0;
	for (int i = 0; i < rows - 1; i++)
	{
		row_size += height / rows;
		if (row_size >= height - 1)break;
		GotoXY(px, py + row_size);
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << borders[LeftCrosshair];
			else if (j == width - 1)
				cout << borders[RightCrosshair];
			else if (cols&& j != 0 && j % size_col == 0 &&
				j + size_col - 2 <= GetWidth())
				cout << borders[Crosshair];
			else 
				cout << borders[HorizontalLine];
		}
	}
}
void Table::DrawTable()
{
	DrawBox();
	if (cols)DrawCols();
	if (rows)DrawRows();
}
void Table::DrawHeadlines(const char** headlines)
{
	size_col = width / cols;
	int pos_x = 0;
	for (int j = 0; j < cols; j++)
	{
		WriteLine(headlines[j], pos_x);
		pos_x += size_col;
	}

};
void Table::SetCols(unsigned int num_cols)
{
	if (num_cols > 0)
	{
		cols = num_cols;
		size_col = width / cols;
	}
	else cols = size_col = num_cols;
}
void Table::SetRows(unsigned int num_rows)
{
	if (num_rows > 0)
	{
		rows = num_rows;
		size_row = height / rows;
	}
	else rows = size_row = num_rows;
	
}



int Input::GetInt(int max_len, int min_len, int px, int py, int indent_letf, int indent_top)
{
	DataPreparation(max_len, px, py, indent_letf, indent_top);
	int key, i = 0;
	while (i < max_len)
	{
		key = _getch();
		if (key == 27) { buff[0] = 0; return 0; }
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
		if (key == 27) { buff[0] = 0; return 0; }
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
		if (key == 27) { buff[0] = 0; return buff; }
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
char* Input::Get(int max_len, int min_len, int px, int py, int indent_letf, int indent_top)
{
	DataPreparation(max_len, px, py, indent_letf, indent_top);
	int key, i = 0;	
	bool is_dot = false;
	while (i < max_len)
	{
		key = _getch();
		if (key == 27) { buff[0] = 0; return buff; }
		if (key == 13) { if(i>=min_len)break; }
		if(key==8)
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
		if ((key >= 'A' && key <= 'Z' && !i) || (key >= 'a' && key <= 'z')|| (key >= '0' && key <= '9') || (key == '.' && !is_dot))
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
	buff = new char[max_len + 1];
	buff[0] = 0;
	if (!px)px = GetCurrentX() + indent_letf;
	if (!py)py = GetCurrentY() + indent_top;
	GotoXY(px, py);
	for (int i = 0; i < max_len; i++)
		cout << " ";
	GotoXY(px, py);
}



void DrawMessage(const char* message, unsigned int width, unsigned int height, unsigned int position, int indent_letf, int indent_top)
{
	cls();
	Message msg(message, width, height, position, indent_letf, indent_top);
	msg.WriteMessage();
	_getch();
	cls();
}