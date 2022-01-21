#pragma once
#include "List.h"
#include "Other.h"



enum position
{
	LeftTop,
	LeftBot,
	CenterTop,
	CenterBot,
	RightTop,
	RightBot
};

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


class Window
{
public:
	Window(unsigned int _width, unsigned int _height, unsigned int position, int indent_letf = 0, int indent_top = 0);
	void SetWinParam(unsigned int _width, unsigned int _height, unsigned int position, int indent_letf = 0, int indent_top = 0);
	void DrawFrame();
	virtual void FillLine(int _x = 0, int _y = 0);
	int GetWidth() { return width - 2; }
	int GetHeight() { return height - 2; }
	int GetX() { return px + 1; }
	int GetY() { return py + 1; }
	void SetIndents(int indent_letf, int indent_top);
	template <class type>
	void WriteLine(const type& val, int indent_letf = 0, int indent_top = 0);
	template <class type>
	void DrawFrame(const type& val, int indent_letf = 0, int indent_top = 0);
	template <class type>
	void FillLine(const type& val, int indent_letf = 0, int indent_top = 0);
protected:	
	char borders[11];
	unsigned int height, width,
		px, py,
		position;
	unsigned txcolor, bgcolor,
		activeTxcolor, activeBgcolor;
};
template <class type>
void Window::WriteLine(const type& val, int indent_letf, int indent_top)
{
	GotoXY(GetX() + indent_letf, GetY() + indent_top);
	cout << val;
}
template <class type>
void Window::DrawFrame(const type& val, int indent_letf, int indent_top)
{
	DrawFrame();
	WriteLine(val, indent_letf, indent_top);
}
template <class type>
void Window::FillLine(const type& val, int indent_letf, int indent_top)
{
	SetColor(activeTxcolor, activeBgcolor);
	FillLine(0, indent_top);
	WriteLine(val, indent_letf, indent_top);
	SetColor(txcolor, bgcolor);
}


class Table:public Window
{
public:
	Table(unsigned int _width=0, unsigned int _height=0, unsigned int position=0, unsigned int _cols = 0, unsigned int _rows = 0, int indent_letf = 0, int indent_top = 0) :Window(_width, _height, position, indent_letf, indent_top)
	{
		SetCols(_cols);
		SetRows(_rows);
	}
	void DrawTable();
	void SetCols(unsigned int);
	void SetRows(unsigned int);
	int GetRows() { return rows; }
	int GetCols() { return cols; }
	int GetSizeRow() { return size_row; }
	int GetSizeCol() { return size_col; }
	void DrawHeadlines(const char**);
	void FillLine(int _x = 0, int _y = 0);
protected:
	void DrawCols();
	void DrawRows();
	int cols, rows,
		size_col, size_row;
};

class Menu :public Window
{
public:
	Menu(unsigned int position, unsigned int _width = 0, unsigned int _height = 0, int indent_letf = 0, int indent_top = 0) :Window(_width, _height, position, indent_letf, indent_top)
	{
		aling = true;
	}
	int DoMenu();
	void DrawMenu();
	void SetMenuParam(int indent_letf = 0, int indent_top = 0);
	int GetSizeMenu() { return menu_items.GetCount(); }
	void SetAling(bool _aling) { aling = _aling; }
	void AddMenuItem(const char* item) { menu_items << item; }
	Menu& operator<<(const char* item) { AddMenuItem(item); return *this; }
private:
	List<const char*>menu_items;
	bool aling;
};

class Message :protected Window
{
	char name[25];
public:
	Message(unsigned int _width = 0, unsigned int _height = 0, unsigned int position = 0, int indent_letf = 0, int indent_top = 0) : Window(_width, _height, position, indent_letf, indent_top) 
	{ name[0] = '\0'; }
	Message(const char* _name, unsigned int _width, unsigned int _height, unsigned int position, int indent_letf = 0, int indent_top = 0) : Window(_width, _height, position, indent_letf, indent_top)
	{ SetName(_name); }
	void SetMsgParam(const char* _name, unsigned int _width, unsigned int _height, unsigned int position, int indent_letf = 0, int indent_top = 0)
	{
		SetName(_name);
		SetWinParam(_width, _height, position, indent_letf, indent_top);
	}
	void SetIndents(int indent_letf, int indent_top) { Window::SetIndents(indent_letf, indent_top); }
	void SetName(const char* _name) { strcpy(name, _name); }
	void DrawActiveMsg(int indent_letf = 0, int indent_top = 0)
	{
		Window::DrawFrame();
		Window::FillLine(name, indent_letf, indent_top);
	}
	void DrawMessage(int indent_letf = 0, int indent_top = 0) { Window::DrawFrame(name, indent_letf, indent_top); }
	void WriteMessage(int indent_letf = 0, int indent_top = 0) { Window::WriteLine(name, indent_letf, indent_top); }
	void FillMessage(int indent_letf = 0, int indent_top = 0) {	Window::FillLine(name, indent_letf, indent_top); }
};

template <class type>
void DrawSomething(const type& something, bool frame = false, unsigned int _width = 17, unsigned int _height = 3, unsigned int position = CenterTop, int indent_letf = 10, int indent_top = 12)
{
	cls();
	Window msg(_width, _height, position, indent_letf, indent_top);
	if (frame) msg.DrawFrame(something);
	else msg.WriteLine(something);
	_getch();
	cls();
}

