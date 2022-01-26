#pragma once
#include <fstream>
#include "List.h"
#include "Products and customers.h"




template <class type>
class FileManager
{
public:

	FileManager(const char* _filename)
	{
		filename = new char[strlen(_filename)+1];
		strcpy(filename, _filename);
		sizeof_st = sizeof(type);
		number_st = 0;
		
	}
	~FileManager()
	{
		Write();
		delete[] filename;
	}
	bool Read(int amount = 0, int offset = 0);
	void FileDelete();
	void Write();
	void QuiryNumberSt();
	List<type>& GetFileData() { return file_data; }
	void RemoveAt(int ind) { file_data.RemoveAt(ind); }
	void RemoveAll() { file_data.RemoveAll(); }
	int GetCount() { return file_data.GetCount(); }
	int GetNumberSt() { return number_st; }
	type& operator[](int ind) { return file_data[ind]; }
protected:
	List<type> file_data;
	char* filename;
	long number_st, sizeof_st;
};

template <class type>
void FileManager<type>::QuiryNumberSt()
{
	fstream file;
	file.open(filename, ios::out | ios::in | ios::binary | ios::app);
	file.seekg(0, ios::end);
	number_st = file.tellg() / sizeof_st;
	file.close();
}
template <class type>
void FileManager<type>::FileDelete()
{
	fstream file;
	file.open(filename, ios::out | ios::in | ios::trunc);
	file.close();
}

template <class type>
bool FileManager<type>::Read(int amount, int offset)
{
	QuiryNumberSt();
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
			file_data << st;
		}
		file.close();
		return true;
	}
	else
	{
		return false;
	}

}

template <class type>
void FileManager<type>::Write()
{	
	FileDelete();
	fstream file;
	file.open(filename, ios::out | ios::in | ios::binary | ios::app);
	file.seekg(ios::beg);
	for (int i = 0; i < file_data.GetCount(); i++)
	{
		file.write((char*)&file_data[i], sizeof_st);
	}
	file.close();
}



