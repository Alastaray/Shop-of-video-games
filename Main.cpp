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
		Menu menu(CenterTop);
		menu << "Show products"
			<< "Add product"
			<< "Delete product"			
			<< "Show customers"
			<< "Add customer"
			<< "Delete customer"
			<< "Create report of income"
			<< "Exit";
		menu.SetMenuParam(0,4);
		while (true)
		{
			int item = menu.DoMenu();
			switch (item)
			{
			case 0:
			case 1:
			case 2:
			{
				AdminProducts admin("products.txt");
				switch (item)
				{
				case 0:
					admin.Show();
					break;
				case 1:
					admin.DrawAdding();
					break;
				case 2:
					admin.DrawDeleting();
					break;
				}
				break;
			}
			case 3:
			case 4:
			case 5:
			{
				AdminCustomers admin("customers.txt");
				switch (item)
				{
				case 3:
					admin.Show();
					break;
				case 4:
					admin.DrawAdding();
					break;
				case 5:
					admin.DrawDeleting();
					break;
				}
				break;
			}
			case 6:
			case 7:
				cls();
				return;
				break;
			}
		}
	}
	catch (ListException& error)
	{
		cls();
		cout << error.what()<<endl
			<<"Index = "<<error.GetValue() << endl
			<< "Count = " << error.GetCount() << endl;
	}
	catch (exception& error)
	{
		cls();
		cout << error.what() << endl;
	}
};