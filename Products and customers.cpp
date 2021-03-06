#include "Products and customers.h"

Product::Product(int _id, const char* _name, int _amount, double _price, double _purchase_price)
{
	id = _id;
	strcpy(name, _name);
	amount = _amount;
	purchase_price = _purchase_price;
	price = _price;

}
Product::Product(const Product& product)
{
	id = product.id;
	strcpy(name, product.name);
	amount = product.amount;
	purchase_price = product.purchase_price;
	price = product.price;
}
void Product::SetName(char* _name)
{
	if(_name[0])
		strcpy(name, _name);

}
void Product::ChangeAmount(int _amount)
{
	amount += _amount;
	if (amount < 0)amount = 0;
}
void Product::SetAmount(int _amount)
{
	if (_amount > 0)
		amount = _amount;

}
void Product::SetPrice(double _price)
{
	if (_price > 0)
		price = _price;
}
void Product::SetPurchasePrice(double _purchase_price)
{
	if (_purchase_price > 0)
		purchase_price = _purchase_price;
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
	if (_name[0])
		strcpy(name, _name);
}
void Customer::SetProdName(char* _prod_name)
{
	if (_prod_name[0])
		strcpy(prod_name, _prod_name);

}
void Customer::SetAmount(int _amount)
{
	if (_amount > 0)
		amount = _amount;

}
void Customer::SetPrice(double _price)
{
	if (_price > 0)
		price = _price;
}
