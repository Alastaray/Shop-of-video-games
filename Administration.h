#pragma once
#include <iostream>
#include "Window.h"
#include "List.h"
#include "Admin.h"
#include "Products and customers.h"
using namespace std;



class AdminProducts :public Admin<Product>
{
public:
	AdminProducts(const char* _filename, unsigned int _width = 0, unsigned int _height = 0, int position = 0, int _cols = 0, int _rows = 0, int indent_letf = 0, int indent_top = 0) :Admin(_filename, _width, _height, position, _cols, _rows, indent_letf, indent_top)
	{
		headlines[0] = "Id";
		headlines[1] = "Name";
		headlines[2] = "Amount";
		headlines[3] = "Price";
		headlines[4] = "Purchase Price";
		filename = _filename;
	}
	void Add(const char* name, int amount, double price, double puchase_price);
	void Create();
	bool Search(const char* val = 0);
	bool Sort(const char* name = 0, int amount = 0, double price = 0, double purchase_price = 0, bool low_to_high = true);
	virtual void DrawElement(List<Product>& l, int row, int col, int x, int y);
	virtual void DrawElement(int row, int col, int x, int y);
	virtual bool DoSearching();
	virtual bool DoSorting();

};


//class AdminCustomers :public Admin<Customer>
//{
//public:
//	AdminCustomers(const char* _filename, unsigned int _width = 0, unsigned int _height = 0, int position = 0, int _cols = 0, int _rows = 0, int indent_letf = 0, int indent_top = 0) :Admin(_filename, _width, _height, position, _cols, _rows, indent_letf, indent_top)
//	{
//		headlines[0] = "Id";
//		headlines[1] = "Name";
//		headlines[2] = "Product Name";
//		headlines[3] = "Amount";
//		headlines[4] = "Price";
//		filename = _filename;
//	}
//	void Add(const char* name, const char* prod_name, int amount, double price);
//	void Create();
//	void Search(const char* val = 0, bool ascending = true);
//	void Sort(const char* name = 0, const char* prod_name = 0, int amount = 0, double price = 0, bool ascending = true);
//	virtual void DrawElement(List<Customer>& l, int row, int col, int x, int y);
//	virtual void DrawElement(int row, int col, int x, int y);
//	virtual void DoSearching();
//	virtual void DoSorting();
//
//};
