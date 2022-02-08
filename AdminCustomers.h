#pragma once
#include "Admin.h"
#include "Products and customers.h"
#include "AdminProducts.h"


class AdminCustomers :public Admin<Customer>
{
public:
	AdminCustomers(const char* _filename, int _limit = 10, int _width = 90) :Admin(_filename, _limit, _width, 5)
	{
		AddHeadline("Id");
		AddHeadline("Name");
		AddHeadline("Product Name");
		AddHeadline("Amount");
		AddHeadline("Price");
	}
	virtual void DrawAdding();
	void ShowIncome(const char* filename);
protected:
	virtual int DrawSearching();
	virtual int DrawSorting();
	virtual bool ChangeData(int index, int col);
	int ChooseProduct(AdminProducts& products);
	int ShowProducts(AdminProducts& products, List<Product>& list, int&);
	virtual void DrawElement(List<Customer>& list, int row, int col, int x, int y);
	void Add(const char* name, const char* prod_name, int amount, double price);
	int Search(const char* val = 0);
	int Sort(int amount = 0, double purchase_price = 0, bool low_to_high = true);	
};

