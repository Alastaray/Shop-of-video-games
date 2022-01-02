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

	Management(const char* _filename)
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
	List<type> list;
	const char* filename;
	int number_st;
};



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



