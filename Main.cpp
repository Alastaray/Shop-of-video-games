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
		AdminProducts prod("products.txt");
		prod.Read();
		//prod.Show();
		prod.DoDeleting();
		/*AdminCustomers prod("customers.txt");
		prod.Read();
		prod.Show();*/
	}
	catch (ListException& error)
	{
		cls();
		cout << error.what()<<endl
			<<"index = "<<error.GetValue() << endl
			<< "count = " << error.GetCount() << endl;
	}

};
