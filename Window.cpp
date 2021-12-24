#include "Window.h"





Window::Window(unsigned int _width, unsigned int _height, int position, int indent_letf, int indent_top)
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
	GotoXY(x, y);
	cout << borders[TopLeftAngle];
	for (int i = 0; i < GetWidth(); i++)
	{
		cout << borders[HorizontalLine];
	}
	cout << borders[TopRightAngle];
	GotoXY(x, y + 1);

	for (int i = 0; i < GetHeight(); i++)
	{
		cout << borders[VerticalLine];
		for (int j = 0; j < GetWidth(); j++)
		{
			cout << " ";
		}
		cout << borders[VerticalLine];
		GotoXY(x, y + 2 + i);
	}
	cout << borders[BotLeftAngle];
	for (int i = 0; i < GetWidth(); i++)
	{
		cout << borders[HorizontalLine];
	}
	cout << borders[BotRightAngle] << endl;

}
template <class type>
void Window::WriteLine(type val, int _x, int _y, int indent_letf, int indent_top)
{
	GotoXY(x + indent_letf + _x, y + indent_top + _y);
	cout << val;
}
void Window::FillRow(int pos)
{
	GotoXY(GetX(),GetY() + pos);

	for (int i = 0; i < GetWidth(); i++) {
		std::cout << " ";
	}

}
void Window::SetWinParam(unsigned int _width, unsigned int _height, int position, int indent_letf, int indent_top)
{
	height = _height;
	width = _width;
	switch (position)
	{
	case LeftTop:
		x = 0 + indent_letf;
		y = 0 + indent_top;
		if (width >= 120)width = 120;
		break;
	case LeftBot:
		x = 0 + indent_letf;
		y = 15 + indent_top;
		if (width >= 120)width = 120;
		break;
	case CenterTop:
		x = 40 + indent_letf;
		y = 0 + indent_top;
		if (width >= 80)width = 80;
		break;
	case CenterBot:
		x = 40 + indent_letf;
		y = 15 + indent_top;
		if (width >= 80)width = 80;
		break;
	case RightTop:
		x = 80 + indent_letf;
		y = 0 + indent_top;
		if (width >= 40)width = 40;
		break;
	case RightBot:
		x = 80 + indent_letf;
		y = 15 + indent_top;
		if (width >= 40)width = 40;
		break;
	default:
		cout << "Îøèáêà!" << endl;
		break;
	}

}

void Menu::DoMenu(const char** _menu_headlines, int _size, void (*func1) (), void (*func2) (), void (*func3) (), void (*func4) (), void (*func5) ())
{
	if (!_size)
	{
		_menu_headlines = menu_headlines;
		_size = headlines_count;
	}
	char key;
	int pos = 0,
		pos_max = _size * 2;
	while (true)
	{
		cls();
		DrawMenu(_menu_headlines, _size);
		SetColor(activeTxcolor, activeBgcolor);
		FillRow(pos);
		WriteLine(_menu_headlines[pos / 2], 0, pos, 4);
		SetColor(txcolor, bgcolor);
		key = _getch();
		if (key == 27)break;
		if (key == 13)
		{
			switch (pos / 2)
			{
			case 0:
				if (*func1)func1();
				break;
			case 1:
				if (*func2)func2();
				break;
			case 2:
				if (*func3)func3();
				break;
			case 3:
				if (*func4)func4();
				break;
			case 4:
				if (*func5)func5();
				return;
				break;
			}
		}
		if (key == 'w')pos -= 2;
		if (key == 's')pos += 2;
		if (key == -32) {
			key = _getch();
			//down
			if (key == 80) pos += 2;
			//up
			if (key == 72) pos -= 2;
		}
		if (pos >= pos_max)pos = 0;
		if (pos < 0)pos = pos_max - 2;
	}
}
void Menu::DrawMenu(const char** _menu_headlines, int _size)
{
	DrawBox();
	if (!_size)
	{
		_menu_headlines = menu_headlines;
		_size = headlines_count;
	}
	for (int i = 0, j = 0; i < _size * 2; j++, i += 2)
	{
		WriteLine(_menu_headlines[j], 0, i, 4);
	}
}


Table::Table(unsigned int _width, unsigned int _height, int position, int _cols, int _rows, int indent_letf, int indent_top) :Window(_width, _height, position, indent_letf, indent_top)
{
	cols = _cols;
	rows = _rows;
	size_cols = size_rows = 0;
}
void Table::FillRow(int pos_x, int pos_y, bool show)
{
	if (show)
	{
		for (int i = 0; i < size_rows - 1; i++)
		{
			GotoXY(GetX() + pos_x, GetY() + pos_y + i);
			for (int j = 0; j < size_cols - 1; j++)
			{
				cout << " ";
			}
		}
	}
}
void Table::DrawCols()
{
	while (width < cols * 2)cols--;
	size_cols = width / cols;
	for (int i = 0; i < height; i++)
	{
		GotoXY(GetX(), y + i);

		for (int j = 1; j <= GetWidth(); j++)
		{
			if (i == 0 &&
				j % size_cols == 0 &&
				j + size_cols - 2 <= GetWidth())
				cout << borders[TopCrosshair];

			else if (i == height - 1 &&
				j % size_cols == 0 &&
				j + size_cols - 2 <= GetWidth())
				cout << borders[BotCrosshair];

			else if (j % size_cols == 0 &&
				j + size_cols - 2 <= GetWidth())
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
	size_rows = height / rows;
	int row_size = 0;
	for (int i = 0; i < rows - 1; i++)
	{
		row_size += height / rows;
		if (row_size >= height - 1)break;
		GotoXY(x, y + row_size);
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << borders[LeftCrosshair];
			else if (j == width - 1)
				cout << borders[RightCrosshair];
			else if (cols&& j != 0 && j % size_cols == 0 &&
				j + size_cols - 2 <= GetWidth())
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
	size_cols = width / cols;
	int pos_x = 0;
	for (int j = 0; j < cols; j++)
	{
		WriteLine(headlines[j], pos_x);
		pos_x += size_cols;
	}

};


void Table::DoTable(List<Product>& list)
{
	char key;
	int pos_y = 0, pos_x = 0,
		col, row;
	bool show = true;
	Button sort("Sorting", 10, 3, RightTop, 0, 2);
	Button search("Search", 10, 3, RightTop, 0, 8);
	Button exit("Exit", 10, 3, RightBot);

	while (true)
	{
		DrawData(list);
		sort.DoButton();
		search.DoButton();
		exit.DoButton();
		if (!size_cols || !size_rows)break;
		SetColor(activeTxcolor, activeBgcolor);
		FillRow(pos_x, pos_y, show);
		col = pos_x / size_cols;
		row = pos_y / size_rows;
		switch (col)
		{
		case 0:
			WriteLine(list[row].GetId(), pos_x, pos_y);
			break;
		case 1:
			WriteLine(list[row].GetName(), pos_x, pos_y);
			break;
		case 2:
			WriteLine(list[row].GetAmount(), pos_x, pos_y);
			break;
		case 3:
			WriteLine(list[row].GetPrice(), pos_x, pos_y);
			break;
		case 4:
			WriteLine(list[row].GetPurchasePrice(), pos_x, pos_y);
			break;
		}
		SetColor(txcolor, bgcolor);
		key = _getch();
		if (key == 27)break;
		if (key == 13)return;
		if (key == 'w')pos_y -= size_rows;
		if (key == 's')pos_y += size_rows;
		if (key == 'd')pos_x += size_cols;
		if (key == 'a')pos_x -= size_cols;
		if (key == -32)
		{

			key = _getch();
			//down
			if (key == 80) pos_y += size_rows;
			//up
			if (key == 72) pos_y -= size_rows;
			//left
			if (key == 75) pos_x -= size_cols;
			//right
			if (key == 77) pos_x += size_cols;
		}
		if (pos_y >= size_rows * rows)pos_y = 0;
		if (pos_y < 0)pos_y = size_rows * (rows - 1);

		if (pos_x >= size_cols * cols)
		{
			pos_x = 0;
			/*show = false;
			if (pos_x >= size_cols * (cols + 1))pos_x = 0;*/
		}
		else
			if (!show)show = true;
		if (pos_x < 0)pos_x = size_cols * (cols - 1);
	}

}
void Table::DrawData(List<Product>& list)
{
	DrawTable();
	int pos_y = 0;
	int pos_x = 0;
	for (int i = 0; i < rows; i++)
	{		
		pos_x = 0;
		for (int j = 0; j < cols; j++)
		{
			switch (j)
			{
			case 0:
				WriteLine(list[i].GetId(), pos_x, pos_y);
				break;
			case 1:
				WriteLine(list[i].GetName(), pos_x, pos_y);
				break;
			case 2:
				WriteLine(list[i].GetAmount(), pos_x, pos_y);
				break;
			case 3:
				WriteLine(list[i].GetPrice(), pos_x, pos_y);
				break;
			case 4:
				WriteLine(list[i].GetPurchasePrice(), pos_x, pos_y);
				break;
			}
			pos_x += size_cols;
		}
		pos_y += size_rows;
	}
	
}



void Table::DoTable(List<Customer>& list)
{

	char key;
	int pos_y = 0, pos_x = 0,
		col, row;
	while (true)
	{				
		DrawData(list);
		if (!size_cols || !size_rows)break;
		SetColor(activeTxcolor, activeBgcolor);
		FillRow(pos_x, pos_y);
		col = pos_x / size_cols;
		row = pos_y / size_rows;
		switch (col)
		{
		case 0:
			WriteLine(list[row].GetId(), pos_x, pos_y);
			break;
		case 1:
			WriteLine(list[row].GetName(), pos_x, pos_y);
			break;
		case 2:
			WriteLine(list[row].GetProdName(), pos_x, pos_y);
			break;
		case 3:
			WriteLine(list[row].GetAmount(), pos_x, pos_y);
			break;
		case 4:
			WriteLine(list[row].GetPrice(), pos_x, pos_y);
			break;
		
		}
		SetColor(txcolor, bgcolor);
		key = _getch();
		if (key == 27)break;
		if (key == 13)
		{
			return;
		}
		if (key == 'w')pos_y -= size_rows;
		if (key == 's')pos_y += size_rows;
		if (key == 'd')pos_x += size_cols;
		if (key == 'a')pos_x -= size_cols;
		if (key == -32) {
			key = _getch();
			//down
			if (key == 80) pos_y += size_rows;
			//up
			if (key == 72) pos_y -= size_rows;
			//left
			if (key == 75) pos_x -= size_cols;
			//right
			if (key == 77) pos_x += size_cols;
		}
		if (pos_y >= size_rows * rows)pos_y = 0;
		if (pos_y < 0)pos_y = size_rows * (rows - 1);
		if (pos_x >= size_cols * cols)pos_x = 0;
		if (pos_x < 0)pos_x = size_cols * (cols - 1);
	}

}
void Table::DrawData(List<Customer>& list)
{
	DrawTable();
	int pos_y = 0;
	int pos_x = 0;
	for (int i = 0; i < rows; i++)
	{
		pos_x = 0;
		for (int j = 0; j < cols; j++)
		{
			switch (j)
			{
			case 0:
				WriteLine(list[i].GetId(), pos_x, pos_y);
				break;
			case 1:
				WriteLine(list[i].GetName(), pos_x, pos_y);
				break;
			case 2:
				WriteLine(list[i].GetProdName(), pos_x, pos_y);
				break;
			case 3:
				WriteLine(list[i].GetAmount(), pos_x, pos_y);
				break;
			case 4:
				WriteLine(list[i].GetPrice(), pos_x, pos_y);
				break;
			}
			pos_x += size_cols;
		}
		pos_y += size_rows;
	}

}

int Input::GetInt(int len, int x, int y, int indent_letf, int indent_top)
{
	ShowCaret(true);
	if (buff)delete buff;
	buff = new char[len + 1];
	buff[0] = 0;
	int key, i = 0;
	if (!x)x = GetCurrentX() + indent_letf;
	if (!y)y = GetCurrentY() + indent_top;
	GotoXY(x, y);
	while (i < len)
	{

		key = _getch();
		if (key == 27) { buff[0] = 0; return 0; }
		if (key == 13) { break; }
		if (key >= '0' && key <= '9') {
			buff[i] = key;
			i++;
			buff[i] = 0;
		}
		GotoXY(x, y);
		cout << buff;
	}
	ShowCaret(false);
	return atoi(buff);
}
double Input::GetDouble(int len, int x, int y, int indent_letf, int indent_top)
{
	ShowCaret(true);
	if (buff)delete buff;
	buff = new char[len + 1];
	buff[0] = 0;
	int key, i = 0;
	if (!x)x = GetCurrentX() + indent_letf;
	if (!y)y = GetCurrentY() + indent_top;
	bool is_dot = false;
	GotoXY(x, y);
	while (i < len)
	{

		key = _getch();
		if (key == 27) { buff[0] = 0; return 0; }
		if (key == 13) { break; }
		if ((key >= '0' && key <= '9') || (key == '.' && !is_dot))
		{
			if (key == '.')is_dot = true;
			buff[i] = key;
			i++;
			buff[i] = 0;
		}
		GotoXY(x, y);
		cout << buff;
	}
	ShowCaret(false);
	return atof(buff);
}
char* Input::GetStr(int len, int x, int y, int indent_letf, int indent_top)
{
	ShowCaret(true);
	if (buff)delete buff;
	buff = new char[len + 1];
	buff[0] = 0;
	int key, i = 0;
	if (!x)x = GetCurrentX() + indent_letf;
	if (!y)y = GetCurrentY() + indent_top;
	GotoXY(x, y);
	while (i < len)
	{
		key = _getch();
		if (key == 27) { buff[0] = 0; return buff; }
		if (key == 13) { break; }
		if ((key >= 'A' && key <= 'Z' && !i) || (key >= 'a' && key <= 'z'))
		{
			buff[i] = key;
			i++;
			buff[i] = 0;
		}
		GotoXY(x, y);
		cout << buff;
	}
	ShowCaret(false);
	return buff;
}

void Button::DoButton()
{
	DrawBox();	
	SetColor(activeTxcolor, activeBgcolor);
	FillRow();
	WriteLine(name);
	SetColor(txcolor, bgcolor);
}

bool CompareStr(const char* value, const char* source)
{
	int len_val = strlen(value);
	int number_let = 0;
	switch (len_val)
	{
	case 1:
		for (int i = 0; i < strlen(source); i++)
			if (value[0] == source[i])
				return true;
		break;
	case 2:
		for (int i = 0; i < strlen(source); i++)
			if (value[0] == source[i] && value[1] == source[i+1])
				return true;
	case 3:
		for (int i = 0; i < strlen(source); i++)
			if (value[0] == source[i] && value[1] == source[i + 1] && value[1] == source[i + 2]&& i + 2 < strlen(source))
				return true;
	default:
		for (int i = 0; i < len_val; i++)
			if (value[i] == source[i])
				number_let++;
		break;
	}
	
	if (number_let == len_val)return true;
	else return false;
}