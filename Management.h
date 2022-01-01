#pragma once
#include <iostream>
#include "Window.h"
#include "List.h"
#include "Products and customers.h"
using namespace std;




template <class type>
class Management: protected Table
{
public:

	Management(const char* _filename, unsigned int _width = 0, unsigned int _height = 0, int position = 0, int _cols = 0, int _rows = 0, int indent_letf = 0, int indent_top = 0) : Table(_width, _height, position, _cols, _rows, indent_letf, indent_top)
	{
		filename = _filename;
		number_st = 0;
	}
	~Management()
	{
		if (filename)Write();
		else cls();
	}
	List<type>& GetList() { return list; }
	void Write();
	int Read();
	void RemoveAt(int ind) { list.RemoveAt(ind); }
	void RemoveAll() { list.RemoveAll(); }
	int GetCount() { return list.GetCount(); }
	int GetNumberSt() { return number_st; }
	void FileDelete();
	type& operator[](int ind) { return list[ind]; }
	void operator<<(const type& val) { list << val; }
	
protected:
	void DoTable();
	void DoTable(List<type>& l);
	void DrawData();
	void DrawData(List<type>& l);			
	void Show();
	void Show(List<type>& l);
	void DrawActiveCell(int row, int col, int x, int y);
	void DrawActiveCell(List<type>& l, int row, int col, int x, int y);
	virtual void DrawElement(List<type>& l, int row, int col, int x, int y) = 0;
	virtual void DrawElement(int row, int col, int x, int y) = 0;
	virtual bool DrawButtons(Button& sort, Button& search, Button& exit, int& x, int& y)=0;

	List<type> list;
	const char* filename;
	int number_st;
	const char* headlines[5];
};

template <class type>
void Management<type>::DoTable()
{
	int x = 0, y = 0;
	Button sort("Sorting", 10, 3, RightTop, 0, 2);
	Button search("Search", 10, 3, RightTop, 0, 8);
	Button exit("Exit", 10, 3, RightBot);
	while (true)
	{
		DrawData();
		sort.DrawButton();
		search.DrawButton();
		exit.DrawButton();
		if (!size_cols || !size_rows)break;
		DrawActiveCell(y / size_rows, x / size_cols, x, y);
		Move(key, x, y, size_rows, size_cols);
		if (key == 27)break;
		if (key == 13)return;
		if(!DrawButtons(sort, search, exit,x,y))return;
		if (y >= size_rows * rows)y = 0;
		if (y < 0)y = size_rows * (rows - 1);
		if (x >= size_cols * cols)x = 0;
		if (x < 0)x = size_cols * (cols - 1);
	}

}

template <class type>
void Management<type>::DoTable(List<type>& l)
{
	int x = 0, y = 0;
	Button sort("Sorting", 10, 3, RightTop, 0, 2);
	Button search("Search", 10, 3, RightTop, 0, 8);
	Button exit("Exit", 10, 3, RightBot);
	while (true)
	{
		DrawData(l);
		sort.DrawButton();
		search.DrawButton();
		exit.DrawButton();
		if (!size_cols || !size_rows)break;
		DrawActiveCell(y / size_rows, x / size_cols, x, y);
		Move(key, x, y, size_rows, size_cols);
		if (key == 27)break;
		if (key == 13)return;
		if (!DrawButtons(sort, search, exit, x, y))return;
		if (y >= size_rows * rows)y = 0;
		if (y < 0)y = size_rows * (rows - 1);
		if (x >= size_cols * cols)x = 0;
		if (x < 0)x = size_cols * (cols - 1);
	}

}

template <class type>
void Management<type>::DrawData(List<type>& l)
{
	DrawTable();
	int pos_y = 0;
	int pos_x = 0;
	for (int i = 0; i < rows; i++)
	{
		pos_x = 0;
		for (int j = 0; j < cols; j++)
		{
			DrawElement(l, i, j, pos_x, pos_y);
			pos_x += size_cols;
		}
		pos_y += size_rows;
	}

}

template <class type>
void Management<type>::DrawActiveCell(List<type>& l, int row, int col, int x, int y)
{
	SetColor(activeTxcolor, activeBgcolor);
	FillRow(x, y);
	DrawElement(l, row, col, x, y);
	SetColor(txcolor, bgcolor);
}

template <class type>
void Management<type>::DrawData()
{
	DrawTable();
	int pos_y = 0;
	int pos_x = 0;
	for (int i = 0; i < rows; i++)
	{
		pos_x = 0;
		for (int j = 0; j < cols; j++)
		{
			DrawElement(i, j, pos_x, pos_y);
			pos_x += size_cols;
		}
		pos_y += size_rows;
	}

}

template <class type>
void Management<type>::DrawActiveCell(int row, int col, int x, int y)
{
	SetColor(activeTxcolor, activeBgcolor);
	FillRow(x, y);
	DrawElement(row, col, x, y);
	SetColor(txcolor, bgcolor);
}

template <class type>
void Management<type>::Show()
{
	cls();
	if (headlines)
	{
		Table hl(75, 4, LeftTop, 5);
		hl.DrawHeadlines(headlines);
	}
	SetWinParam(75, GetCount() * 2 + 1, LeftTop, 0, 2);
	SetCols(5);
	SetRows(GetCount());
	DoTable();
}

template <class type>
void Management<type>::Show(List<type>& l)
{
	cls();
	if (headlines)
	{
		Table hl(75, 4, LeftTop, 5);
		hl.DrawHeadlines(headlines);
	}
	SetWinParam(75, l.GetCount() * 2 + 1, LeftTop, 0, 2);
	SetCols(5);
	SetRows(l.GetCount());
	DoTable(l);
}

template <class type>
void Management<type>::FileDelete()
{
	fstream file;
	file.open(filename, ios::out | ios::in | ios::trunc);
	file.close();
}

template <class type>
int Management<type>::Read()
{
	type st;
	fstream file;
	file.open(filename, ios::out | ios::in | ios::binary | ios::app);
	file.seekg(0, ios::end);
	number_st = file.tellg() / sizeof(st);
	if (number_st)
	{
		file.seekg(0, ios::beg);
		for (int i = 0; i < number_st; i++)
		{
			file.read((char*)&st, sizeof(st));
			list << st;
		}
		return 1;
	}
	else
	{
		return 0;
	}
	file.close();
}

template <class type>
void Management<type>::Write()
{	
	if (number_st == list.GetCount())return;
	FileDelete();
	fstream file;
	type st;
	file.open(filename, ios::out | ios::in | ios::binary | ios::app);
	file.clear();
	file.seekg(ios::beg);
	for (int i = 0; i < list.GetCount(); i++)
	{
		file.write((char*)&list[i], sizeof(list[i]));
	}
	file.close();
}



