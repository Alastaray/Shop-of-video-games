#pragma once
#include <iostream>
#include <conio.h>
#include "fun_console.h"
#include "Products and customers.h"
#include "List.h"
#include "Functions.h"
using namespace std;

enum position
{
	LeftTop,
	LeftBot,
	CenterTop,
	CenterBot,
	RightTop,
	RightBot
};


void DrawMessage(const char* message, unsigned int _width = 17, unsigned int _height = 3, unsigned int position = CenterTop, int indent_letf = 0, int indent_top = 10);


class Window
{
public:
	
	Window(unsigned int _width, unsigned int _height, unsigned int position, int indent_letf = 0, int indent_top = 0);
	~Window();
	void SetWinParam(unsigned int _width, unsigned int _height, unsigned int position, int indent_letf = 0, int indent_top = 0);
	void DrawBox();
	virtual void FillLine(int _x = 0, int _y = 0);
	int GetWidth() { return width - 2; }
	int GetHeight() { return height - 2; }
	int GetX() { return px + 1; }
	int GetY() { return py + 1; }

	template <class type>
	void WriteLine(type val, int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1);
	template <class type>
	void DrawBox(type val, int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1);
	template <class type>
	void FillLine(type val, int pos_x=0, int pos_y=0);
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
		px, py;
	unsigned txcolor, bgcolor,
		activeTxcolor, activeBgcolor;
};
template <class type>
void Window::WriteLine(type val, int pos_x, int pos_y, int indent_letf, int indent_top)
{
	GotoXY(px + pos_x + indent_letf, py + pos_y + indent_top);
	cout << val;
}
template <class type>
void Window::DrawBox(type val, int pos_x, int pos_y, int indent_x, int indent_y)
{
	DrawBox();
	WriteLine(val, pos_x, pos_y, indent_x, indent_y);
}
template <class type>
void Window::FillLine(type val, int pos_x, int pos_y)
{
	SetColor(activeTxcolor, activeBgcolor);
	FillLine(0, pos_y);
	WriteLine(val, pos_x, pos_y);
	SetColor(txcolor, bgcolor);
}


class Table:public Window
{
public:
	Table(unsigned int _width=0, unsigned int _height=0, unsigned int position=0, unsigned int _cols = 0, unsigned int _rows = 0, int indent_letf = 0, int indent_top = 0);
	void DrawTable();
	void SetCols(unsigned int num_cols);
	void SetRows(unsigned int num_cols);
	unsigned int GetRows() { return rows; }
	unsigned int GetCols() { return cols; }
	unsigned int GetSizeRow() { return size_row; }
	unsigned int GetSizeCol() { return size_col; }
	void DrawHeadlines(const char** headlines);
	void FillLine(int _x = 0, int _y = 0);
protected:
	void DrawCols();
	void DrawRows();
	unsigned int cols, rows,
		size_col, size_row;
};


class Menu :public Window
{
public:
	Menu(unsigned int position, unsigned int _width = 0, unsigned int _height = 0, int indent_letf = 0, int indent_top = 0) :Window(_width, _height, position, indent_letf, indent_top)
	{
		this->position = position;
	}
	void SetMenuParam(int indent_letf = 0, int indent_top = 0);
	int GetSizeMenu() { return menu.GetCount(); }
	int DoMenu();
	void DrawMenu();
	void AddMenuItem(const char* item) { menu << item; }
	Menu& operator<<(const char* item) { AddMenuItem(item); return *this; }
private:
	List<const char*>menu;
	unsigned int position;
};

class Message :protected Window
{
public:
	Message(const char* _name, unsigned int _width, unsigned int _height, unsigned int position, int indent_letf = 0, int indent_top = 0) : Window(_width, _height, position, indent_letf, indent_top)
	{
		strcpy(name, _name);
	}
	void DrawActiveMsg(int pos_x = 0, int pos_y = 0) 
	{
		Window::DrawBox();
		Window::FillLine(name, pos_x, pos_y); 
	}
	void DrawMessage(int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1) { Window::DrawBox(name, pos_x, pos_y, indent_x, indent_y); }
	void WriteMessage(int pos_x = 0, int pos_y = 0, int indent_x = 1, int indent_y = 1) { Window::WriteLine(name, pos_x, pos_y, indent_x, indent_y); }
	void FillMessage(int pos_x = 0, int pos_y = 0) { Window::FillLine(name, pos_x, pos_y); }
private:
	char name[25];
};


class Input
{
public:
	Input() { buff = 0; }
	~Input() { delete buff; }
	double GetDouble(int max_len, int min_len = 0, int px = 0, int py = 0, int indent_letf = 0, int indent_top = 0);
	int GetInt(int max_len, int min_len = 0, int px = 0, int py = 0, int indent_letf = 0, int indent_top = 0);
	char* GetStr(int max_len, int min_len = 0, int px = 0, int py = 0, int indent_letf = 0, int indent_top = 0);
	char* Get(int max_len, int min_len=0, int px = 0, int py = 0, int indent_letf = 0, int indent_top = 0);
private:
	void DataPreparation(int max_len, int &px, int &py, int indent_letf = 0, int indent_top = 0);
	char* buff;
};

