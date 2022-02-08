#pragma once
#include "Admin.h"
#include "Products and customers.h"

class AdminProducts :public Admin<Product>
{
public:
	AdminProducts(const char* _filename, int _limit = 10, int _width = 90) :Admin(_filename, _limit, _width, 5)
	{
		AddHeadline("Id");
		AddHeadline("Name");
		AddHeadline("Amount");
		AddHeadline("Price");
		AddHeadline("Purchase Price");
	}
	virtual void DrawAdding();
	void Add(const char* name, int amount, double purchase_price, double puchase_price);
protected:
	virtual void DrawElement(List<Product>&, int row, int col, int x, int y);
	virtual int DrawSearching();
	virtual int DrawSorting();
	virtual bool ChangeData(int index, int col);
	int Search(const char* val = 0);
	int Sort(int amount = 0, double purchase_price = 0, double price = 0, bool low_to_high = true);
	
	friend class AdminCustomers;
};
