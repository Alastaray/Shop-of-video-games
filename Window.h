#pragma once
#include <iostream>
#include <conio.h>
#include "fun_console.h"
#include "Products and customers.h"
#include "List.h"

using namespace std;

bool CompareStr(const char* value, const char* source);
void Move(char &key, int& x, int& y, int size_rows=0, int size_cols=0);


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
	template <class type>
	void WriteLine(type val, int _x = 0, int _y = 0, int indent_x = 1, int indent_y = 1);
	void SetWinParam(unsigned int _width, unsigned int _height, int position, int indent_letf=0, int indent_top=0);
	void DrawBox();
	virtual void FillRow(int pos=0);
	
	int GetWidth() { return width - 2; }
	int GetHeight() { return height - 2; }
	int GetX() { return x+1; }
	int GetY() { return y+1; }
	

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
void Window::WriteLine(type val, int _x, int _y, int indent_letf, int indent_top)
{
	GotoXY(x + indent_letf + _x, y + indent_top + _y);
	cout << val;
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
	void FillRow(int pos_x, int pos_y);
	void DrawHeadlines(const char** headlines);

protected:
	int cols, rows,
		size_cols, size_rows;
	char key;

};

class Button:public Window
{
public:
	Button(const char*_name,unsigned int _width, unsigned int _height, int position, int indent_letf=0, int indent_top=0): Window(_width, _height, position, indent_letf, indent_top)
	{
		strcpy(name, _name);
		
	}
	void DrawActiveBut();
	void DrawButton();


private:
	char name[25];
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


class Input
{
public:
	Input() { buff = 0; }
	~Input() { delete buff; }
	double GetDouble(int len, int x = 0, int y = 0, int indent_letf = 0, int indent_top = 0);
	int GetInt(int len, int x = 0, int y = 0, int indent_letf = 0, int indent_top = 0);
	char* GetStr(int len, int x = 0, int y = 0, int indent_letf = 0, int indent_top = 0);
	char* Get(int len, int x = 0, int y = 0, int indent_letf = 0, int indent_top = 0);
private:
	char* buff;
};

