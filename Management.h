#pragma once
#include <iostream>
#include "Window.h"
#include "List.h"
#include "Products and customers.h"
using namespace std;




template <class type>
class Management
{
public:

	Management(const char* _filename = 0);
	~Management();
	List<type>& GetList() { return list; }
	void Write();
	int Read();
	void RemoveAll();
	void RemoveAt(int ind);
	void Show(List<type>& l);
	void Show();
	int GetCount() { return list.GetCount(); }
	int GetNumberSt() { return number_st; }
	void FileDelete();
	type& operator[](int ind) { return list[ind]; }
	void operator<<(const type& val) { list << val; }
protected:
	List<type> list;
	const char* filename;
	fstream file;
	int number_st;
	const char* headlines[5];
};


class AdminProducts :public Management<Product>, public Table
{
public:	
	AdminProducts(unsigned int _width, unsigned int _height, int position, int _cols = 0, int _rows = 0, int indent_letf = 0, int indent_top = 0):Table(_width, _height, position,  _cols,  _rows, indent_letf, indent_top)
	{ 
		headlines[0] = "Id";
		headlines[1] = "Name";		
		headlines[2] = "Amount";
		headlines[3] = "Price";
		headlines[4] = "Purchase Price";
		filename = "products.txt"; 
	}
	void Add(const char* name, int amount, double price, double puchase_price);
	void Create();
	void Search(const char* val = 0, bool ascending = true);
	void Sort(const char* name = 0, int amount = 0, double price = 0, double purchase_price = 0, bool ascending = true);
	void DoTable();
	void DrawData();
	void DrawElement(int row, int col, int x, int y);
	void DrawActiveCell(int row, int col, int x, int y);
	void Show();
};

class AdminCustomers :public Management<Customer>
{
public:
	AdminCustomers() 
	{ 
		headlines[0] = "Id";
		headlines[1] = "Name";
		headlines[2] = "Product Name";
		headlines[3] = "Amount";
		headlines[4] = "Price";
		filename = "customers.txt"; 
	}
	void Add(const char* name, const char* prod_name, int amount, double price);
	void Create();
	void Search(const char* val = 0, bool ascending = true);
	void Sort(const char* name = 0, const char* prod_name = 0, int amount = 0, double price = 0, bool ascending = true);
};




template <class type>
Management<type>::Management(const char* _filename)
{
	filename = _filename;
	number_st = 0;
}

template <class type>
Management<type>::~Management()
{
	if(filename)Write();
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
	Table table(75, l.GetCount() * 2 + 1, LeftTop, 5, l.GetCount(),0,2);
	table.DoTable(l);
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
	Table table(75, GetCount() * 2 + 1, LeftTop, 5, GetCount(), 0, 2);
	table.DoTable(list);
}

template <class type>
void Management<type>::FileDelete()
{
	file.open(filename, ios::out | ios::in | ios::trunc | ios::binary);
	file.close();
}

template <class type>
int Management<type>::Read()
{
	type st;

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
	type st;

	file.open(filename, ios::out | ios::in | ios::binary | ios::app);
	file.clear();
	file.seekg(ios::beg);
	for (int i = number_st; i < list.GetCount(); i++)
	{
		file.write((char*)&list[i], sizeof(list[i]));
	}
	file.close();
}

template <class type>
void Management<type>::RemoveAt(int ind)
{
	list.RemoveAt(ind);
}

template <class type>
void Management<type>::RemoveAll()
{
	list.RemoveAll();
}


