#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include "fun_console.h"
#include "Window.h"
#include "List.h"
#include "Management.h"
#include "Admin.h"
#include "Products and customers.h"
using namespace std;
#pragma warning(disable: 4996)


void ManagProducts()
{
	AdminProducts prod("products.txt");
	prod.Read();
	//prod.Show(prod.GetList());
	prod.Sort(0,3);
	
}
void ManagCustomers()
{
	AdminCustomers cust("customers.txt");
	cust.Read();
	cust.Show();
}



void main()
{
	ManagProducts();

};
