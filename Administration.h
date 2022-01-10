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
	AdminProducts(const char* _filename) :Admin(_filename)
	{
		headlines[0] = "Id";
		headlines[1] = "Name";
		headlines[2] = "Amount";
		headlines[3] = "Price";
		headlines[4] = "Purchase Price";
		filename = _filename;
	}	
	virtual void DrawAdding();

protected:
	virtual void DrawElement(List<Product>& _list, int row, int col, int x, int y);
	virtual bool DrawSearching();
	virtual bool DrawSorting();
	virtual void Edit(int id, int col);
	bool Search(const char* val = 0);
	bool Sort(int amount = 0, double price = 0, double purchase_price = 0, bool low_to_high = true);
	void Add(const char* name, int amount, double price, double puchase_price);
	friend class AdminCustomers;
};


class AdminCustomers :public Admin<Customer>
{
public:
	AdminCustomers(const char* _filename) :Admin(_filename)
	{
		headlines[0] = "Id";
		headlines[1] = "Name";
		headlines[2] = "Product Name";
		headlines[3] = "Amount";
		headlines[4] = "Price";
		filename = _filename;
	}	
	virtual void DrawAdding();
protected:
	virtual bool DrawSearching();
	virtual bool DrawSorting();
	virtual void Edit(int id, int col);
	int ShowProducts(AdminProducts& product);
	virtual void DrawElement(List<Customer>& _list, int row, int col, int x, int y);
	void Add(const char* name, const char* prod_name, int amount, double price);
	bool Search(const char* val = 0);
	bool Sort(int amount = 0, double price = 0, bool low_to_high = true);
};
