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
	void DrawHeadlines();
	bool DoTable();
	bool DoTable(List<type>& l);
	void DrawData();
	void DrawData(List<type>& l);
	bool Show();
	bool Show(List<type>& l);
	void DrawActiveCell(int row, int col, int x, int y);
	void DrawActiveCell(List<type>& l, int row, int col, int x, int y);
	bool DrawButtons(Button& sort, Button& search, Button& exit);
	bool DrawButtons(List<type>& l, Button& sort, Button& search, Button& exit);
	virtual void DrawElement(List<type>& l, int row, int col, int x, int y) = 0;
	virtual void DrawElement(int row, int col, int x, int y) = 0;
	virtual bool DoSearching() = 0;
	virtual bool DoSorting() = 0;
	virtual void Editing(int row, int col) = 0;
protected:
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
bool Admin<type>::DoTable()
{
	int x = 0, y = 0,
		row, col;
	Button sort("Sort", 10, 3, RightTop, 8, 2);
	Button search("Search", 10, 3, RightTop, 8, 8);
	Button exit("Exit", 10, 3, RightBot,8);
	while (true)
	{		
		DrawData();
		sort.DrawButton();
		search.DrawButton();
		exit.DrawButton();
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
			if (!DrawButtons(sort, search, exit))return false;
			x -= size_cols;
		}		
		if (y >= size_rows * rows)y = 0;
		if (y < 0)y = size_rows * (rows - 1);
		if (x >= size_cols * cols)x = 0;
		if (x < 0)x = size_cols * (cols - 1);
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
	FillRow(x, y);
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
bool Admin<type>::DrawButtons(Button& sort, Button& search, Button& exit)
{
	int x=0,y=0;
	char _key;
	sort.DrawButton();
	search.DrawButton();
	exit.DrawButton();
	while (true)
	{
		switch (y)
		{
		case 0:
			DrawData();
			search.DrawButton();
			exit.DrawButton();
			sort.DrawActiveBut();
			break;
		case 1:
			DrawData();
			sort.DrawButton();
			exit.DrawButton();
			search.DrawActiveBut();
			break;
		case 2:
			DrawData();
			sort.DrawButton();
			search.DrawButton();
			exit.DrawActiveBut();
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
		if (_key == 80 || _key == 'a' || _key == 'A'|| _key == 72 || _key == 'd' || _key == 'D') 
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
	Button sort("Sort", 10, 3, RightTop, 8, 2);
	Button search("Search", 10, 3, RightTop, 8, 8);
	Button exit("Exit", 10, 3, RightBot, 8);
	while (true)
	{
		DrawData(l);
		sort.DrawButton();
		search.DrawButton();
		exit.DrawButton();
		if (!size_cols || !size_rows)break;
		row = y / size_rows;
		col = x / size_cols;
		DrawActiveCell(l,row, col, x, y);
		Move(key, x, y, size_cols, size_rows);
		if (key == 27)break;
		if (key == 13)Editing(row, col);
		if (x >= size_cols * cols)
		{
			if (!DrawButtons(l, sort, search, exit))return false;
			x -= size_cols;
		}

		if (y >= size_rows * rows)y = 0;
		if (y < 0)y = size_rows * (rows - 1);
		if (x >= size_cols * cols)x = 0;
		if (x < 0)x = size_cols * (cols - 1);
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
	FillRow(x, y);
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
bool Admin<type>::DrawButtons(List<type>& l, Button& sort, Button& search, Button& exit)
{
	int x = 0, y = 0;
	char _key;
	while (true)
	{
		switch (y)
		{
		case 0:
			DrawData(l);
			search.DrawButton();
			exit.DrawButton();
			sort.DrawActiveBut();
			break;
		case 1:
			DrawData(l);
			sort.DrawButton();
			exit.DrawButton();
			search.DrawActiveBut();
			break;
		case 2:
			DrawData(l);
			sort.DrawButton();
			search.DrawButton();
			exit.DrawActiveBut();
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
		if (_key == 80 || _key == 'a' || _key == 'A' || _key == 72 || _key == 'd' || _key == 'D')
			break;
		if (y >= 3)y = 0;
		if (y < 0)y = 2;
	}
	return true;
}

