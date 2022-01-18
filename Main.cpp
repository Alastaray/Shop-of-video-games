#include <iostream>
#include <windows.h>
#include <conio.h>
#include "fun_console.h"
#include "Window.h"
#include "Administration.h"

using namespace std;
#pragma warning(disable: 4996)

		


void main()
{
	try
	{
		/*Menu menu_items(CenterTop);
		menu_items << "Add product"
			<< "Show products"
			<< "Delete product"
			<< "Add customer"
			<< "Show customers"
			<< "Delete customer"
			<< "Create report of income"
			<< "Exit";
		menu_items.SetMenuParam(0,4);
		switch (menu_items.DoMenu())
		{

		default:
			break;
		}*/
		AdminProducts product("products.txt");
		product.Show();
		//AdminCustomers prod("customers.txt");
		//prod.DrawAdding();

	}
	catch (ListException& error)
	{
		cls();
		cout << error.what()<<endl
			<<"index = "<<error.GetValue() << endl
			<< "count = " << error.GetCount() << endl;
	}
	catch (exception& error)
	{
		cout << error.what() << endl;
	}
};
