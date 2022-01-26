#pragma once
#include "Window.h"
#include "FileManager.h"


template <class type>
class Admin : public FileManager<type>, public Table
{
public:
	Admin(const char* _filename, unsigned int _limit, int _width, int _cols, unsigned int position = 0);
	~Admin();
	bool Show();
	void DrawDeleting();
	int SeekElement(List<type>& list, unsigned int id);
	virtual int DrawSearching() = 0;
	virtual int DrawSorting() = 0;
	virtual void DrawAdding() = 0;
	void SetLimit(unsigned int _limit);
	int GetLimit() { return limit; }
	List<type>& GetSortedList() { return sorted; }

protected:
	List <type> sorted;
	unsigned int limit;
	Message* pag_left,
		* current_page,
		* pag_right,
		* sort,
		* search,
		* back;

	int SetTableParam(List<type>& list, int& page);
	int DoTable(List<type>& list, int& page);
	void DrawData(List<type>& list);
	void DrawActiveCell(List<type>& list, int row, int col, int x, int y);
	virtual void DrawElement(List<type>& list, int row, int col, int x, int y) = 0;

	void SetPaginationParam(int& page);
	void DrawPagination();
	bool DoPagination(int& page);

	void SetButtonsParam();
	void DrawButtons();
	int DoButtons();


	void CheckXY(int& x, int& y);
	bool DoDeleting(List<type> list, int& page);

	virtual bool ChangeData(int index, int whom) = 0;
	bool Edit(int id, int col);
	void Synchronization(int index);
};

template <class type>
Admin<type>::Admin(const char* _filename, unsigned int _limit, int _width, int _cols, unsigned int position) : FileManager<type>(_filename), Table(_width, 0, position, _cols, 0)
{
	limit = _limit;
	pag_left = new Message("<<", 5, 3, LeftTop);
	current_page = new Message("0", 5, 3, LeftTop);
	pag_right = new Message(">>", 5, 3, LeftTop);
	sort = new Message("Sort", 10, 3, RightTop);
	search = new Message("Search", 10, 3, RightTop);
	back = new Message("Back", 10, 3, RightTop);
	this->Read();
}

template <class type>
Admin<type>::~Admin()
{
	delete pag_left;
	delete current_page;
	delete pag_right;
	delete sort;
	delete search;
	delete back;
}


template <class type>
bool Admin<type>::Show()
{
	if(!this->GetCount())throw exception((string(this->filename)+" is empty!").c_str());
	sorted = this->file_data;
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
int Admin<type>::SetTableParam(List<type>& list, int& page)
{
	if (!list.GetCount())throw exception("List is empty!");
	cls();
	SetWinParam(width, list.GetCount() * 2 + 1, LeftTop, 5, 2);
	SetRows(list.GetCount());
	return DoTable(list, page);
}

template <class type>
int Admin<type>::DoTable(List<type>& list, int& page)
{
	if (!size_col)throw exception("size_col can't be zero!");
	if (!size_row)throw exception("size_row can't be zero!");
	char key = 0;
	int x = 0, y = 0,
		 row, col, result=1;
	SetButtonsParam();
	SetPaginationParam(page);
	while (true)
	{		
		DrawData(list);
		DrawButtons();
		DrawPagination();
		row = y / size_row;
		col = x / size_col;
		DrawActiveCell(list, row, col, x, y);
		Move(key, x, y, size_col, size_row);
		if (key == 27)return false;
		if (key == 13)
		{
			if(Edit(list[row].GetId(), col))return true;
		}
		if (x >= size_col * cols)
		{
			x -= size_col;
			DrawData(list);
			if ((result = DoButtons()) != -1)return result;
		}	
		if (y >= size_row * rows)
		{
			y -= size_row;
			DrawData(list);
			if (DoPagination(page))return true;
		}
		CheckXY(x, y);
	}
	return true;

}

template <class type>
void Admin<type>::DrawData(List<type>& list)
{
	if(headlines.GetCount())DrawHeadlines();
	DrawTable();
	int pos_y = 0;
	int pos_x = 0;
	for (int i = 0; i < rows; i++)
	{
		pos_x = 0;
		for (int j = 0; j < cols; j++)
		{
			DrawElement(list, i, j, pos_x, pos_y);
			pos_x += size_col;
		}
		pos_y += size_row;
	}

}

template <class type>
void Admin<type>::DrawActiveCell(List<type>& list, int row, int col, int x, int y)
{
	SetColor(activeTxcolor, activeBgcolor);
	FillLine(x, y);
	DrawElement(list, row, col, x, y);
	SetColor(txcolor, bgcolor);
}


template <class type>
void Admin<type>::SetButtonsParam()
{
	sort->SetIndents(19, 2 + rows / 3);
	search->SetIndents(19, 5 + rows / 3 * 2);
	back->SetIndents(19, 8 + rows / 3 * 3);
}

template <class type>
void Admin<type>::DrawButtons()
{
	sort->DrawMessage();
	search->DrawMessage();
	back->DrawMessage();
}

template <class type>
int Admin<type>::DoButtons()
{
	int x = 0, y = 0;
	char key;
	while (true)
	{
		switch (y)
		{
		case 0:
			DrawButtons();
			sort->DrawActiveMsg();
			break;
		case 1:
			DrawButtons();
			search->DrawActiveMsg();
			break;
		case 2:
			DrawButtons();
			back->DrawActiveMsg();
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
void Admin<type>::SetPaginationParam(int &page)
{
	current_page->SetName(IntToChar(page));
	pag_left->SetIndents(width / 2 - 4, size_row * rows + 3);
	current_page->SetIndents(width / 2 + 3, size_row * rows + 3);
	pag_right->SetIndents(width / 2 + 10, size_row * rows + 3);
}

template <class type>
void Admin<type>::DrawPagination()
{
	pag_left->DrawMessage();
	current_page->DrawMessage(1);
	pag_right->DrawMessage(1);
}

template <class type>
bool Admin<type>::DoPagination(int& page)
{
	int x = 0, y = 0;
	char key;
	while (true)
	{
		switch (x)
		{
		case 0:
			pag_left->DrawMessage();
			pag_right->DrawActiveMsg();
			break;
		case 1:
			pag_right->DrawMessage();
			pag_left->DrawActiveMsg();
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
void Admin<type>::CheckXY(int& x, int& y)
{
	if (y < 0)y = size_row * (rows - 1);
	if (y >= size_row * rows)y = 0;
	if (x >= size_col * cols)x = 0;
	if (x < 0)x = size_col * (cols - 1);
}

template <class type>
void Admin<type>::SetLimit(unsigned int _limit)
{
	if (_limit == 0)throw exception("Limit can't be zero!");
	limit = _limit;
}

template <class type>
void Admin<type>::DrawDeleting()
{
	if (!this->GetCount())throw exception("File is empty!");
	int index,
		page = 0,
		number_pages = 0;
	while (true)
	{
		cls();
		number_pages = ceil(this->file_data.GetCount() / (limit * 1.0));
		if (number_pages <= page)page = 0;
		if (0 > page)page = number_pages - 1;
		List<type> l;
		for (int i = page * limit, j = 0; i < this->file_data.GetCount(); i++, j++)
		{
			if (j >= limit)break;
			l << this->file_data[i];
		}		
		SetWinParam(width, l.GetCount() * 2 + 1, LeftTop, 5, 2);
		SetRows(l.GetCount());
		if (!DoDeleting(l, page))return;
	}
}

template <class type>
bool Admin<type>::DoDeleting(List<type> list, int &page)
{
	if (!size_col)throw exception("size_col can't be zero!");
	if (!size_row)throw exception("size_row can't be zero!");
	char key;
	int x = 0, y = 0,
		row, col;
	SetPaginationParam(page);
	back->SetIndents(19, 2);
	while (true)
	{
		DrawData(list);
		DrawPagination();
		back->DrawMessage();
		row = y / size_row;
		col = x / size_col;
		for (int i = 0; i < cols; i++)
		{
			x = size_col * i;
			DrawActiveCell(list, y / size_row, x / size_col, x, y);
		}
		Move(key, x, y, size_col, size_row);
		if (key == 27)return false;
		if (key == 13)
		{
			this->file_data.RemoveAt(SeekElement(this->file_data, list[row].GetId()));
			return true;
		}
		if (x >= size_col * cols)
		{
			DrawData(list);
			back->DrawActiveMsg();
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
			DrawData(list);
			if (DoPagination(page))return -2;
		}
		CheckXY(x, y);
	}
}


template <class type>
bool Admin<type>::Edit(int id, int col)
{
	if (!col)return false;
	int index = SeekElement(this->file_data, id);
	bool result = ChangeData(index, col);
	if(result)Synchronization(index);
	return result;
}

template <class type>
void Admin<type>::Synchronization(int index)
{
	for (int i = 0; i < sorted.GetCount(); i++)
	{
		if (this->file_data[index].GetId() == sorted[i].GetId())
		{
			sorted[i] = this->file_data[index];
			break;
		}
	}
}

template <class type>
int Admin<type>::SeekElement(List<type>& list, unsigned int id)
{
	for (int i = 0; i < list.GetCount(); i++)
	{
		if (id == list[i].GetId())
		{
			return i;
		}
	}
	return -1;
}

