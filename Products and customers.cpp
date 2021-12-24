#include "Products and customers.h"

Product::Product(int _id, const char* _name, int _amount, double _price, double _purchase_price)
{
	id = _id;
	strcpy(name, _name);
	amount = _amount;
	price = _price;
	purchase_price = _purchase_price;

}
Product::Product(const Product& prod)
{
	id = prod.id;
	strcpy(name, prod.name);
	amount = prod.amount;
	price = prod.price;
	purchase_price = prod.purchase_price;
}
void Product::SetName(char* _name)
{
	strcpy(name, _name);

}
void Product::SetAmount(int _amount)
{
	if (_amount >= 0)
		amount = _amount;

}
void Product::SetPurchasePrice(double _purchase_price)
{
	if (_purchase_price > 0)
		purchase_price = _purchase_price;
}
void Product::SetPrice(double _price)
{
	if (_price > 0)
		price = _price;
}


Customer::Customer(int _id, const char* _name, const char* _prod_name, int _amount, double _price)
{
	id = _id;
	strcpy(name, _name);
	strcpy(prod_name, _prod_name);
	amount = _amount;
	price = _price;
	

}
Customer::Customer(const Customer& cust)
{
	id = cust.id;
	strcpy(name, cust.name);
	strcpy(prod_name, cust.prod_name);
	amount = cust.amount;
	price = cust.price;
	
}
void Customer::SetName(char* _name)
{
	strcpy(name, _name);

}
void Customer::SetProdName(char* _prod_name)
{
	strcpy(prod_name, _prod_name);

}
void Customer::SetAmount(int _amount)
{
	if (_amount >= 0)
		amount = _amount;

}
void Customer::SetPrice(double _price)
{
	if (_price > 0)
		price = _price;
}
