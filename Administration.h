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
	virtual int DrawSearching();
	virtual int DrawSorting();
	virtual void ChangeData(int id, int whom);
	int Search(const char* val = 0);
	int Sort(int amount = 0, double price = 0, double purchase_price = 0, bool low_to_high = true);
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
	virtual int DrawSearching();
	virtual int DrawSorting();
	virtual void ChangeData(int id, int whom);
	int ChooseProduct(AdminProducts& product);
	int ShowProducts(AdminProducts& product, List<Product>& _list, int& page);
	virtual void DrawElement(List<Customer>& _list, int row, int col, int x, int y);
	void Add(const char* name, const char* prod_name, int amount, double price);
	int Search(const char* val = 0);
	int Sort(int amount = 0, double price = 0, bool low_to_high = true);

};
