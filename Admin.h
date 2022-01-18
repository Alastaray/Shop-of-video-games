#pragma once
#include <iostream>
#include "Window.h"
#include "Management.h"
#include "List.h"
#include "cmath"
#include "Others.h"
using namespace std;



template <class type>
class Admin : public Management<type>, public Table
{
public:
	Admin(const char* _filename) : Management<type>(_filename)
	{
		headlines[0] = "0";
		limit = 10;
		width = 90;
		SetCols(5);
		if(!this->Read())throw exception("File wasn't found or can't be read!");
	}
	bool Show();
	void DrawDeleting();	
	int SeekElement(List<type>& _list, unsigned int id);
	virtual void DrawAdding() = 0;

	void SetLimit(unsigned int _limit)
	{
		if (_limit == 0)throw exception("Limit can't be zero!");
		limit = _limit;
	}
	int GetLimit() { return limit; }
	List<type>& GetSortedList() { return sorted; }
protected:
	const char* headlines[5];
	List <type> sorted;
	unsigned int limit;

	int SetTableParam(List<type>& _list, int &page);
	int DoTable(List<type>& _list, int& page);
	void DrawData(List<type>& _list);
	void DrawActiveCell(List<type>& _list, int row, int col, int x, int y);
	bool DrawPagination(Message& pag_left, Message& pag_right, int& page);
	int DrawButtons(Message& sort, Message& search, Message& back);
	virtual void DrawElement(List<type>& _list, int row, int col, int x, int y) = 0;

	void CheckXY(int& x, int& y);
	void DrawHeadlines();

	bool DoDeleting(List<type> _list, int& page);
	virtual int DrawSearching() = 0;
	virtual int DrawSorting() = 0;

	virtual bool ChangeData(int id, int whom) = 0;
	bool Edit(int id, int col);
	void Synchronization(int index);

};



template <class type>
bool Admin<type>::Show()
{
	sorted = this->list;
	int page = 0,
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
	if (!_list.GetCount())throw exception("List is empty!");
	cls();
	SetWinParam(width, _list.GetCount() * 2 + 1, LeftTop, 5, 2);
	SetRows(_list.GetCount());
	return DoTable(_list, page);
}

template <class type>
int Admin<type>::DoTable(List<type>& _list, int& page)
{
	if (!size_col)throw exception("size_col can't be zero!");
	if (!size_row)throw exception("size_row can't be zero!");
	char key = 0;
	int x = 0, y = 0,
		 row, col, result=1;
	Message pag_left("<<", 5, 3, LeftTop, width / 2 - 4, size_row * rows + 3);
	Message current_page(IntToChar(page), 5, 3, LeftTop, width / 2 + 3, size_row * rows + 3);
	Message pag_right(">>", 5, 3, LeftTop, width / 2 + 10, size_row * rows + 3);
	Message sort("Sort", 10, 3, RightTop, 19, 2 + rows / 3);
	Message search("Search", 10, 3, RightTop, 19, 5 + rows / 3 * 2);
	Message back("Back", 10, 3, RightTop, 19, 8 + rows / 3 * 3);
	while (true)
	{		
		DrawData(_list);
		sort.DrawMessage();
		search.DrawMessage();
		back.DrawMessage();
		pag_left.DrawMessage();
		current_page.DrawMessage(1);
		pag_right.DrawMessage();
		row = y / size_row;
		col = x / size_col;
		DrawActiveCell(_list, row, col, x, y);
		Move(key, x, y, size_col, size_row);
		if (key == 27)break;
		if (key == 13)
		{
			if(Edit(_list[row].GetId(), col))return true;
		}
		if (x >= size_col * cols)
		{
			x -= size_col;
			DrawData(_list);
			if ((result = DrawButtons(sort, search, back)) != -1)return result;
		}	
		if (y >= size_row * rows)
		{
			y -= size_row;
			DrawData(_list);
			if (DrawPagination(pag_left, pag_right, page))return true;
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
			pos_x += size_col;
		}
		pos_y += size_row;
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
			search.DrawMessage();
			back.DrawMessage();
			sort.DrawActiveMsg();
			break;
		case 1:
			sort.DrawMessage();
			back.DrawMessage();
			search.DrawActiveMsg();
			break;
		case 2:
			sort.DrawMessage();
			search.DrawMessage();
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
	return -1;
}

template <class type>
bool Admin<type>::DrawPagination(Message& pag_left, Message& pag_right, int& page)
{
	int x = 0, y = 0;
	char key;
	while (true)
	{
		switch (x)
		{
		case 0:
			pag_left.DrawMessage();
			pag_right.DrawActiveMsg();
			break;
		case 1:
			pag_right.DrawMessage();
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
	return false;
}


template <class type>
void Admin<type>::DrawHeadlines()
{
	if (!CompareStr(headlines[0], "0"))
	{
		Table hl(width, 4, LeftTop, 5,0,5);
		hl.DrawHeadlines(headlines);
	}
}

template <class type>
void Admin<type>::CheckXY(int& x, int& y)
{
	if (y < 0)y = size_row * (rows - 1);
	if (y >= size_row * rows)y = 0;
	if (x >= size_col * cols)x = 0;
	if (x < 0)x = size_col * (cols - 1);
}

template <class type>
void Admin<type>::DrawDeleting()
{
	int index,
		page = 0,
		number_pages = 0;
	while (true)
	{
		cls();
		number_pages = ceil(this->list.GetCount() / (limit * 1.0));
		if (number_pages <= page)page = 0;
		if (0 > page)page = number_pages - 1;
		List<type> l;
		for (int i = page * limit, j = 0; i < this->list.GetCount(); i++, j++)
		{
			if (j >= limit)break;
			l << this->list[i];
		}		
		SetWinParam(width, l.GetCount() * 2 + 1, LeftTop, 5, 2);
		SetRows(l.GetCount());
		if (!DoDeleting(l, page))return;
	}
}

template <class type>
bool Admin<type>::DoDeleting(List<type> _list, int &page)
{
	if (!size_col)throw exception("size_col can't be zero!");
	if (!size_row)throw exception("size_row can't be zero!");
	char key;
	int x = 0, y = 0,
		row, col;
	Message pag_left("<<", 5, 3, LeftTop, width / 2 - 4, size_row * rows + 3);
	Message current_page(IntToChar(page), 5, 3, LeftTop, width / 2 + 3, size_row * rows + 3);
	Message pag_right(">>", 5, 3, LeftTop, width / 2 + 10, size_row * rows + 3);
	Message back("Back", 10, 3, RightTop, 19, 2);
	while (true)
	{
		DrawData(_list);
		pag_left.DrawMessage();
		current_page.DrawMessage(1);
		pag_right.DrawMessage();
		back.DrawMessage();
		row = y / size_row;
		col = x / size_col;
		for (int i = 0; i < cols; i++)
		{
			x = size_col * i;
			DrawActiveCell(_list, y / size_row, x / size_col, x, y);
		}
		Move(key, x, y, size_col, size_row);
		if (key == 27)return false;
		if (key == 13)
		{
			this->list.RemoveAt(SeekElement(this->list, _list[row].GetId()));
			return true;
		}
		if (x >= size_col * cols)
		{
			DrawData(_list);
			back.DrawActiveMsg();
			Move(key, x, y, size_col, size_row);
			if (key == 13)return false;
			if (key == 72 || key == 'w' || key == 'W')
				y += size_row;
			if (key == 80 || key == 's' || key == 'S')
				y -= size_row;
		}
		if (y >= size_row * rows)
		{
			y -= size_row;
			DrawData(_list);
			if (DrawPagination(pag_left, pag_right, page))return -2;
		}
		CheckXY(x, y);
	}
}

template <class type>
bool Admin<type>::Edit(int id, int col)
{
	if (!col)return false;
	int index = SeekElement(this->list, id);
	bool result = ChangeData(index, col);
	if(result)Synchronization(index);
	return result;
}

template <class type>
void Admin<type>::Synchronization(int index)
{
	for (int i = 0; i < sorted.GetCount(); i++)
	{
		if (this->list[index].GetId() == sorted[i].GetId())
		{
			sorted[i] = this->list[index];
			break;
		}
	}
}

template <class type>
int Admin<type>::SeekElement(List<type>& _list, unsigned int id)
{
	for (int i = 0; i < _list.GetCount(); i++)
	{
		if (id == _list[i].GetId())
		{
			return i;
		}
	}
	return -1;
}
