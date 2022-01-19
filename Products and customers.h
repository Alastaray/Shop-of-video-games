#pragma once
#include <iostream>
using namespace std;
#pragma warning(disable: 4996)

class Product
{
public:
	Product() {}
	Product(int _id, const char* _name, int _amount, double _price, double _purchase_price);
	Product(const Product& product);

	int GetId() { return id; }

	void SetName(char* _name);
	char* GetName() { return name; }

	void SetPrice(double _purchase_price);
	double GetPrice() { return price; }

	void SetPurchasePrice(double _price);
	double GetPurchasePrice() { return purchase_price; }

	void ChangeAmount(int _amount);
	void SetAmount(int _amount);
	int GetAmount() { return amount; }


private:
	
	int id;
	char name[15];
	int amount;
	double purchase_price;
	double price;
};
class Customer
{
public:
	Customer() {}
	Customer(int _id, const char* _name, const char* _prod_name, int _amount, double _price);
	Customer(const Customer& t);

	int GetId() { return id; }

	void SetName(char* _name);
	char* GetName() { return name; }

	void SetProdName(char* _prod_name);
	char* GetProdName() { return prod_name; }

	void SetAmount(int _amount);
	int GetAmount() { return amount; }

	void SetPrice(double _price);
	double GetPrice() { return price; }

	


private:

	int id;
	char name[15];
	char prod_name[15];
	int amount;
	double price;
};
