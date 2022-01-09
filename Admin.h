#pragma once
#include <iostream>
#include "Window.h"
#include "Management.h"
#include "List.h"

using namespace std;




template <class type>
class Admin : public Management<type>, public Table
{
public:

	Admin(const char* _filename, unsigned int _width = 0, unsigned int _height = 0, int position = 0, int _cols = 0, int _rows = 0, int indent_letf = 0, int indent_top = 0) : Management<type>(_filename), Table(_width, _height, position, _cols, _rows, indent_letf, indent_top)
	{}
	void DoDeleting();	
	bool DoTable();
	bool DoTable(List<type>& l);
	bool Show();
	bool Show(List<type>& l);
	virtual void DrawElement(List<type>& l, int row, int col, int x, int y) = 0;
	virtual void DrawElement(int row, int col, int x, int y) = 0;
	virtual bool DoSearching() = 0;
	virtual bool DoSorting() = 0;
	virtual void Editing(int row, int col) = 0;
protected:
	void DrawHeadlines();
	void DrawData();
	void DrawData(List<type>& l);
	void DrawActiveCell(int row, int col, int x, int y);
	void DrawActiveCell(List<type>& l, int row, int col, int x, int y);
	bool DrawButtons(Message& sort, Message& search, Message& back);
	bool DrawButtons(List<type>& l, Message& sort, Message& search, Message& back);
	bool Delete();
	void CheckXY(int& x, int& y);

	const char* headlines[5];

};







template <class type>
void Admin<type>::DrawHeadlines()
{
	if (headlines)
	{
		Table hl(85, 4, LeftTop, 5);
		hl.DrawHeadlines(headlines);
	}
}

template <class type>
void Admin<type>::CheckXY(int &x, int &y)
{
	if (y >= size_rows * rows)y = 0;
	if (y < 0)y = size_rows * (rows - 1);
	if (x >= size_cols * cols)x = 0;
	if (x < 0)x = size_cols * (cols - 1);
}

template <class type>
void Admin<type>::DoDeleting()
{	
	while (true)
	{
		cls();
		SetWinParam(85, this->GetCount() * 2 + 1, LeftTop, 0, 2);
		SetCols(5);
		SetRows(this->GetCount());
		if (!Delete())return;
	}
}

template <class type>
bool Admin<type>::Delete()
{
	int x = 0, y = 0,
		row, col;
	Message back("Back", 10, 3, RightTop, 8,2);
	while (true)
	{
		DrawData();
		back.DrawBox();
		if (!size_cols || !size_rows)break;
		row = y / size_rows;
		col = x / size_cols;
		for (int i = 0; i < cols; i++)
		{
			x = size_cols * i;
			DrawActiveCell(y / size_rows, x / size_cols, x, y);
		}
		Move(key, x, y, size_cols, size_rows);
		if (key == 27)return false;
		if (key == 13)
		{
			Management<type>::RemoveAt(row);
			return true;
		}
		if (x >= size_cols * cols)
		{
			DrawData();
			back.DrawActiveMsg();
			Move(key, x, y, size_cols, size_rows);
			if (key == 13)return false;
			if (key == 72 || key == 'w' || key == 'W')
				y += size_rows;
			if ( key == 80 || key == 's' || key == 'S')
				y -= size_rows;
		}
		CheckXY(x, y);
	}
}


template <class type>
bool Admin<type>::DoTable()
{
	int x = 0, y = 0,
		row, col;
	Message sort("Sort", 10, 3, RightTop, 8, 2);
	Message search("Search", 10, 3, RightTop, 8, 8);
	Message back("Back", 10, 3, RightBot,8);
	while (true)
	{		
		DrawData();
		sort.DrawBox();
		search.DrawBox();
		back.DrawBox();
		if (!size_cols || !size_rows)break;
		row = y / size_rows;
		col = x / size_cols;
		/*for (int i = 0; i < cols; i++)
		{
			x = size_cols * i;
			DrawActiveCell(y / size_rows, x / size_cols, x, y);		
		}*/
		DrawActiveCell(row, col, x, y);
		Move(key, x, y, size_cols, size_rows);
		if (key == 27)break;
		if (key == 13)Editing(row,col);
		if (x >= size_cols * cols)
		{
			if (!DrawButtons(sort, search, back))return false;
			x -= size_cols;
		}		
		CheckXY(x, y);
	}
	return true;

}

template <class type>
void Admin<type>::DrawData()
{
	DrawHeadlines();
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
void Admin<type>::DrawActiveCell(int row, int col, int x, int y)
{
	SetColor(activeTxcolor, activeBgcolor);
	FillLine(x, y);
	DrawElement(row, col, x, y);
	SetColor(txcolor, bgcolor);
}

template <class type>
bool Admin<type>::Show()
{
	cls();
	SetWinParam(85, this->GetCount() * 2 + 1, LeftTop, 0, 2);
	SetCols(5);
	SetRows(this->GetCount());
	return DoTable();
}

template <class type>
bool Admin<type>::DrawButtons(Message& sort, Message& search, Message& back)
{
	int x=0,y=0;
	char _key;
	sort.DrawBox();
	search.DrawBox();
	back.DrawBox();
	while (true)
	{
		switch (y)
		{
		case 0:
			DrawData();
			search.DrawBox();
			back.DrawBox();
			sort.DrawActiveMsg();
			break;
		case 1:
			DrawData();
			sort.DrawBox();
			back.DrawBox();
			search.DrawActiveMsg();
			break;
		case 2:
			DrawData();
			sort.DrawBox();
			search.DrawBox();
			back.DrawActiveMsg();
			break;
		}
		Move(_key, x, y, 0,1);
		if (_key == 13)
		{
			switch (y)
			{
			case 0:
				if (!DoSorting())return false;
				break;
			case 1:
				if (!DoSearching())return false;
				break;
			case 2:
				return false;
			}
		}
		if (_key == 75 || _key == 'a' || _key == 'A'|| _key == 77 || _key == 'd' || _key == 'D') 
			break;
		if (y >= 3)y = 0;
		if (y < 0)y = 2;
	}
	return true;
}



template <class type>
bool Admin<type>::DoTable(List<type>& l)
{
	int x = 0, y = 0,
		row,col;
	Message sort("Sort", 10, 3, RightTop, 8, 2);
	Message search("Search", 10, 3, RightTop, 8, 8);
	Message back("Back", 10, 3, RightBot, 8);
	while (true)
	{
		DrawData(l);
		sort.DrawBox();
		search.DrawBox();
		back.DrawBox();
		if (!size_cols || !size_rows)break;
		row = y / size_rows;
		col = x / size_cols;
		DrawActiveCell(l,row, col, x, y);
		Move(key, x, y, size_cols, size_rows);
		if (key == 27)break;
		if (key == 13)Editing(row, col);
		if (x >= size_cols * cols)
		{
			if (!DrawButtons(l, sort, search, back))return false;
			x -= size_cols;
		}
		CheckXY(x, y);
	}
	return true;
}

template <class type>
void Admin<type>::DrawData(List<type>& l)
{
	DrawHeadlines();
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
void Admin<type>::DrawActiveCell(List<type>& l, int row, int col, int x, int y)
{
	SetColor(activeTxcolor, activeBgcolor);
	FillLine(x, y);
	DrawElement(l, row, col, x, y);
	SetColor(txcolor, bgcolor);
}

template <class type>
bool Admin<type>::Show(List<type>& l)
{
	cls();
	SetWinParam(85, l.GetCount() * 2 + 1, LeftTop, 0, 2);
	SetCols(5);
	SetRows(l.GetCount());
	return DoTable(l);
}

template <class type>
bool Admin<type>::DrawButtons(List<type>& l, Message& sort, Message& search, Message& back)
{
	int x = 0, y = 0;
	char _key;
	while (true)
	{
		switch (y)
		{
		case 0:
			DrawData(l);
			search.DrawBox();
			back.DrawBox();
			sort.DrawActiveMsg();
			break;
		case 1:
			DrawData(l);
			sort.DrawBox();
			back.DrawBox();
			search.DrawActiveMsg();
			break;
		case 2:
			DrawData(l);
			sort.DrawBox();
			search.DrawBox();
			back.DrawActiveMsg();
			break;
		}
		Move(_key, x, y, 0, 1);
		if (_key == 13)
		{
			switch (y)
			{
			case 0:
				if (!DoSorting())return false;
				break;
			case 1:
				if (!DoSearching())return false;
				break;
			case 2:
				return false;
			}
		}
		if (_key == 75 || _key == 'a' || _key == 'A' || _key == 77 || _key == 'd' || _key == 'D')
			break;
		if (y >= 3)y = 0;
		if (y < 0)y = 2;
	}
	return true;
}

