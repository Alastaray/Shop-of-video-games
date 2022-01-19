#pragma once
#include "Admin.h"
#include "Products and customers.h"

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
	void Add(const char*, int, double, double);
protected:
	virtual void DrawElement(List<Product>&, int, int, int, int);
	virtual int DrawSearching();
	virtual int DrawSorting();
	virtual bool ChangeData(int, int);
	int Search(const char* val = 0);
	int Sort(int amount = 0, double purchase_price = 0, double price = 0, bool low_to_high = true);
	
	friend class AdminCustomers;
};
