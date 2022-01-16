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




void main()
{
	try
	{
		AdminProducts product("products.txt");
		product.Show();
		/*AdminCustomers product("customers.txt");
		product.Read();
		product.Show();*/

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
		cls();
		cout << error.what() << endl;
	}
};
