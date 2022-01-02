#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include "fun_console.h"
#include "Window.h"
#include "List.h"
#include "Admin.h"
#include "Administration.h"
#include "Products and customers.h"
using namespace std;
#pragma warning(disable: 4996)


void ManagProducts()
{
	
	try
	{
		AdminProducts prod("products.txt");
		prod.Read();
		//prod.Add("dada", 4, 4, 4);
		//prod.RemoveAt(0);
		prod.Show();

	}
	catch (const char*er)
	{
		cls();
		cout << er;
	}
	
	
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
