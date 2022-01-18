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
		///*AdminProducts product("products.txt");
		//product.Show();*/
		//AdminCustomers product("customers.txt");
		//product.DrawAdding();

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
