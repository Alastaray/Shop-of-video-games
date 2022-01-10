#pragma once
#include <iostream>
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
		sizeof_st = sizeof(type);
		QuiryNumberSt();
	}
	~Management()
	{
		if (filename)Write();
		else cls();
	}
	int Read(int amount = 0, int offset = 0);
	void FileDelete();
	void Write();
	void QuiryNumberSt();
	List<type>& GetList() { return list; }
	void RemoveAt(int ind) { list.RemoveAt(ind); }
	void RemoveAll() { list.RemoveAll(); }
	int GetCount() { return list.GetCount(); }
	int GetNumberSt() { return number_st; }
	type& operator[](int ind) { return list[ind]; }
	void operator<<(const type& val) { list << val; }
protected:
	List<type> list;
	const char* filename;
	long number_st, sizeof_st;
};

template <class type>
void Management<type>::QuiryNumberSt()
{
	fstream file;
	file.open(filename, ios::out | ios::in | ios::binary | ios::app);
	file.seekg(0, ios::end);
	number_st = file.tellg() / sizeof_st;
	file.close();
}
template <class type>
void Management<type>::FileDelete()
{
	fstream file;
	file.open(filename, ios::out | ios::in | ios::trunc);
	file.close();
}

template <class type>
int Management<type>::Read(int amount, int offset)
{
	if (number_st && offset < number_st)
	{	
		type st;
		fstream file;
		file.open(filename, ios::out | ios::in | ios::binary | ios::app);
		if (!amount || amount > number_st)amount = number_st;
		if (offset + amount >= number_st)
		{
			amount = number_st - offset;
		}
		file.seekg(offset * sizeof_st, ios::beg);
		for (int i = 0; i < amount; i++)
		{
			file.read((char*)&st, sizeof_st);
			list << st;
		}
		file.close();
		return 1;
	}
	else
	{
		return 0;
	}

}

template <class type>
void Management<type>::Write()
{	
	FileDelete();
	fstream file;
	type st;
	file.open(filename, ios::out | ios::in | ios::binary | ios::app);
	file.seekg(ios::beg);
	for (int i = 0; i < list.GetCount(); i++)
	{
		file.write((char*)&list[i], sizeof_st);
	}
	file.close();
}



