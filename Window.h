#pragma once
#include <iostream>
#include <conio.h>
#include "fun_console.h"
#include "Products and customers.h"
#include "List.h"

using namespace std;

bool CompareStr(const char* value, const char* source);
void Move(char &key, int& x, int& y, int how_change_x = 0, int how_change_y = 0);


enum position
{
	LeftTop,
	LeftBot,
	CenterTop,
	CenterBot,
	RightTop,
	RightBot
};

class Window
{
public:
	
	Window(unsigned int _width, unsigned int _height, int position, int indent_letf = 0, int indent_top = 0);
	~Window();
	void SetWinParam(unsigned int _width, unsigned int _height, int position, int indent_letf = 0, int indent_top = 0);
	void DrawBox();
	virtual void FillRow(int _x = 0, int _y = 0);
	int GetWidth() { return width - 2; }
	int GetHeight() { return height - 2; }
	int GetX() { return x + 1; }
	int GetY() { return y + 1; }

	template <class type>
	void WriteLine(type val, int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1);
	template <class type>
	void DrawBox(type val, int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1);
	template <class type>
	void FillRow(type val, int pos_x=0, int pos_y=0, int indent_x = 1, int indent_y = 1);
protected:	
	enum Borders_name
	{
		TopLeftAngle,
		TopRightAngle,
		BotLeftAngle,
		BotRightAngle,
		HorizontalLine,
		VerticalLine,
		TopCrosshair,
		BotCrosshair,
		LeftCrosshair,
		RightCrosshair,
		Crosshair,
	};
	char borders[11];
	unsigned int height, width,
		x, y;
	unsigned txcolor, bgcolor,
		activeTxcolor, activeBgcolor;
};
template <class type>
void Window::WriteLine(type val, int pos_x, int pos_y, int indent_letf, int indent_top)
{
	GotoXY(x + pos_x + indent_letf, y + pos_y + indent_top);
	cout << val;
}
template <class type>
void Window::DrawBox(type val, int pos_x, int pos_y, int indent_x, int indent_y)
{
	DrawBox();
	WriteLine(val, pos_x, pos_y, indent_x, indent_y);
}
template <class type>
void Window::FillRow(type val, int pos_x, int pos_y, int indent_x, int indent_y)
{
	SetColor(activeTxcolor, activeBgcolor);
	FillRow(pos_x, pos_y);
	WriteLine(val, pos_x, pos_y, indent_x, indent_y);
	SetColor(txcolor, bgcolor);
}


class Table:public Window
{
public:
	Table(unsigned int _width, unsigned int _height, int position, int _cols = 0, int _rows = 0, int indent_letf = 0, int indent_top = 0);
	void DrawTable();
	void DrawCols();
	void DrawRows();
	void SetCols(int num_cols);
	void SetRows(int num_cols);
	void DrawHeadlines(const char** headlines);
	void FillRow(int _x = 0, int _y = 0);
protected:
	int cols, rows,
		size_cols, size_rows;
	char key;

};


class Menu :public Window
{
public:
	Menu(unsigned int _width, unsigned int _height, int position,  const char** _menu_headlines = 0, int _size = 0, int indent_letf = 0, int indent_top = 0):Window( _width,_height, position, indent_letf, indent_top)
	{

		menu_headlines = _menu_headlines;
		headlines_count = _size;
	}
	int GetHeadlinesCount() { return headlines_count; }
	void DrawMenu(const char** _menu_headlines = 0, int _size = 0);
	void DoMenu(const char** _menu_headlines = 0, int _size = 0, void (*func1) () = 0, void (*func2) () = 0, void (*func3) () = 0, void (*func4) () = 0, void (*func5) () = 0);
private:
	const char** menu_headlines;
	int headlines_count;
};

class Button :public Window
{
public:
	Button(const char* _name, unsigned int _width, unsigned int _height, int position, int indent_letf = 0, int indent_top = 0) : Window(_width, _height, position, indent_letf, indent_top)
	{
		strcpy(name, _name);

	}
	void DrawActiveBut(int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1) 
	{
		DrawBox();
		Window::FillRow(name, pos_x, pos_y, indent_x, indent_y); 
	}
	void DrawButton(int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1) { DrawBox(name, pos_x, pos_y, indent_x, indent_y); }
	void DrawName(int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1) { WriteLine(name, pos_x, pos_y, indent_x, indent_y); }
	void FillRow(int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1) { Window::FillRow(name, pos_x, pos_y, indent_x, indent_y); }
private:
	char name[25];
};


class Input
{
public:
	Input() { buff = 0; }
	~Input() { delete buff; }
	double GetDouble(int max_len, int min_len = 0, int x = 0, int y = 0, int indent_letf = 0, int indent_top = 0);
	int GetInt(int max_len, int min_len = 0, int x = 0, int y = 0, int indent_letf = 0, int indent_top = 0);
	char* GetStr(int max_len, int min_len = 0, int x = 0, int y = 0, int indent_letf = 0, int indent_top = 0);
	char* Get(int max_len, int min_len=0, int x = 0, int y = 0, int indent_letf = 0, int indent_top = 0);
private:
	void DataPreparation(int max_len, int &x, int &y, int indent_letf = 0, int indent_top = 0);
	char* buff;
};

