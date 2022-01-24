#pragma once
#include "Admin.h"
#include "Products and customers.h"
#include "AdminProducts.h"


class AdminCustomers :public Admin<Customer>
{
public:
	AdminCustomers(const char* _filename, int _limit = 10, int _width = 90) :Admin(_filename, _limit, _width, 5)
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
	virtual bool ChangeData(int, int);
	int ChooseProduct(AdminProducts&);
	int ShowProducts(AdminProducts&, List<Product>&, int&);
	virtual void DrawElement(List<Customer>&, int, int, int, int);
	void Add(const char*, const char*, int, double);
	int Search(const char* val = 0);
	int Sort(int amount = 0, double purchase_price = 0, bool low_to_high = true);

};
double CreateReport(AdminProducts& admin_prod, AdminCustomers& admin_cust);
