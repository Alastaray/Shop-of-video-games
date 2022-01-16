#pragma once
#include <iostream>
#include "Window.h"
#include "Management.h"
#include "List.h"
#include "cmath"
using namespace std;




template <class type>
class Admin : public Management<type>, public Table
{
public:

	Admin(const char* _filename) : Management<type>(_filename)
	{
	}
	void Show();
	bool DoPages(List<type>& _list);
	void DoDeleting();	
	virtual void DrawAdding() = 0;
protected:
	int SetTableParam(List<type>& _list, int &page);
	void DrawHeadlines();
	int DoTable(List<type>& _list, int& page);
	void DrawData(List<type>& _list);
	void DrawActiveCell(List<type>& _list, int row, int col, int x, int y);
	int DrawPagination(Message& pag_left, Message& pag_right, int& page);
	int DrawButtons(Message& sort, Message& search, Message& back);
	bool DrawDeleting();
	void CheckXY(int& x, int& y);
	virtual void DrawElement(List<type>& _list, int row, int col, int x, int y) = 0;
	virtual int DrawSearching() = 0;
	virtual int DrawSorting() = 0;
	virtual void ChangeData(int id, int whom) = 0;
	void Edit(int id, int col);
	void Synchronization(int id);
	const char* headlines[5];
	List <type> sorted;
};


template <class type>
void Admin<type>::Show()
{
	this->Read();
	DoPages(this->list);
}

template <class type>
bool Admin<type>::DoPages(List<type>& _list)
{
	sorted = _list;
	int a = 0;
	int page = 0,
		limit = 2,
		result = 1,
	number_pages = ceil(sorted.GetCount() / (limit*1.0));
	while (true)
	{
		List <type> l;	
		for (int i = page * limit, j = 0; i < sorted.GetCount(); i++, j++)
		{
			if (j >= limit)break;
			l << sorted[i];
		}	
		result = SetTableParam(l, page);
		if (!result)return false;
		if (result == 2)
		{
			page = 0;
			number_pages = ceil(sorted.GetCount() / (limit * 1.0));
		}
		if (number_pages <= page)page = 0;
		if (0 > page)page = number_pages - 1;
	}
	return true;
}


template <class type>
int Admin<type>::SetTableParam(List<type>& _list, int& page)
{
	if (!_list.GetCount())throw "List is empty!";
	cls();
	SetWinParam(85, _list.GetCount() * 2 + 1, LeftTop, 0, 2);
	SetCols(5);
	SetRows(_list.GetCount());
	return DoTable(_list, page);
}

template <class type>
int Admin<type>::DoTable(List<type>& _list, int& page)
{
	char key = 0;
	int x =0, y=0;
	if (!size_cols)throw "size_cols is empty!";
	if(!size_rows)throw "size_rows is empty!";
	int row, col, result=1;
	Message pag_left("<<", 5, 3, LeftBot, width / 2 - 8, 8);
	Message pag_right(">>", 5, 3, LeftBot, width / 2 + 5, 8);
	Message sort("Sort", 10, 3, RightTop, 8, 2);
	Message search("Search", 10, 3, RightTop, 8, 8);
	Message back("Back", 10, 3, RightBot,8);
	while (true)
	{		
		DrawData(_list);
		sort.DrawBox();
		search.DrawBox();
		back.DrawBox();
		pag_left.DrawBox();
		pag_right.DrawBox();
		row = y / size_rows;
		col = x / size_cols;
		DrawActiveCell(_list, row, col, x, y);
		Move(key, x, y, size_cols, size_rows);
		if (key == 27)break;
		if (key == 13)
		{
			Edit(_list[row].GetId(), col);
			return true;
		}
		if (x >= size_cols * cols)
		{
			x -= size_cols;
			DrawData(_list);
			if ((result = DrawButtons(sort, search, back)) != 3)return result;
		}	
		if (y >= size_rows * rows)
		{
			y -= size_rows; 
			DrawData(_list);
			if ((result = DrawPagination(pag_left, pag_right, page)) != 3)return result;
		}
		CheckXY(x, y);
	}
	return true;

}

template <class type>
void Admin<type>::DrawData(List<type>& _list)
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
			DrawElement(_list, i, j, pos_x, pos_y);
			pos_x += size_cols;
		}
		pos_y += size_rows;
	}

}

template <class type>
void Admin<type>::DrawActiveCell(List<type>& _list, int row, int col, int x, int y)
{
	SetColor(activeTxcolor, activeBgcolor);
	FillLine(x, y);
	DrawElement(_list, row, col, x, y);
	SetColor(txcolor, bgcolor);
}

template <class type>
int Admin<type>::DrawButtons(Message& sort, Message& search, Message& back)
{
	int x = 0, y = 0;
	char key;
	while (true)
	{
		switch (y)
		{
		case 0:
			search.DrawBox();
			back.DrawBox();
			sort.DrawActiveMsg();
			break;
		case 1:
			sort.DrawBox();
			back.DrawBox();
			search.DrawActiveMsg();
			break;
		case 2:
			sort.DrawBox();
			search.DrawBox();
			back.DrawActiveMsg();
			break;
		}
		Move(key, x, y, 0, 1);
		if (key == 13)
		{
			switch (y)
			{
			case 0:
				return DrawSorting();
			case 1:
				return DrawSearching();
			case 2:
				return false;
			}
		}
		if (key == 75 || key == 'a' || key == 'A' || key == 77 || key == 'd' || key == 'D')
			break;
		if (y >= 3)y = 0;
		if (y < 0)y = 2;
	}
	return 3;
}

template <class type>
int Admin<type>::DrawPagination(Message& pag_left, Message& pag_right, int& page)
{
	int x = 0, y = 0;
	char key;
	while (true)
	{
		switch (x)
		{
		case 0:
			pag_left.DrawBox();
			pag_right.DrawActiveMsg();
			break;
		case 1:
			pag_right.DrawBox();
			pag_left.DrawActiveMsg();
			break;
		}
		Move(key, x, y, 1, 0);
		if (key == 13)
		{
			switch (x)
			{
			case 0:	page++;	break;
			case 1:	page--;	break;
			}
			return true;
		}
		if (key == 72 || key == 'w' || key == 'W' || key == 80 || key == 's' || key == 'S')
			break;
		if (x >= 2)x = 0;
		if (x < 0)x = 1;
	}
	return 3;
}





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
void Admin<type>::CheckXY(int& x, int& y)
{
	if (y < 0)y = size_rows * (rows - 1);
	if (y >= size_rows * rows)y = 0;
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
		if (!DrawDeleting())return;
	}
}

template <class type>
bool Admin<type>::DrawDeleting()
{
	char key;
	int x = 0, y = 0,
		row, col;
	Message back("Back", 10, 3, RightTop, 8, 2);
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
			if (key == 80 || key == 's' || key == 'S')
				y -= size_rows;
		}
		CheckXY(x, y);
	}
}

template <class type>
void Admin<type>::Edit(int id, int col)
{
	if (!col)return;
	if (id < this->list.GetCount())
	{
		ChangeData(id, col);
		Synchronization(id);
	}
	else
	{
		for (int i = 0; i < this->list.GetCount(); i++)
		{
			if (id == this->list[i].GetId())
			{
				ChangeData(i, col);
				Synchronization(i);
				break;
			}
		}
	}
}
template <class type>
void Admin<type>::Synchronization(int id)
{
	for (int i = 0; i < sorted.GetCount(); i++)
	{
		if (id == sorted[i].GetId())
		{
			sorted[i] = this->list[id];
			break;
		}
	}
}

