#pragma once
#include <iostream>
#include <fstream>
#include "List.h"

#pragma warning(disable: 4996)
using namespace std;

class Product
{
public:
	Product() {}
	Product(int _id, const char* _name, int _amount, double _price, double _puchase_price);
	Product(const Product& prod);

	int GetId() { return id; }

	void SetName(char* _name);
	char* GetName() { return name; }

	void SetPurchasePrice(double _purchase_price);
	double GetPurchasePrice() { return purchase_price; }

	void SetPrice(double _price);
	double GetPrice() { return price; }

	void SetAmount(int _amount);
	int GetAmount() { return amount; }


private:
	
	int id;
	char name[50];
	int amount;
	double price;
	double purchase_price;
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
	char name[50];
	char prod_name[50];
	int amount;
	double price;
};
