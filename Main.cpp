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
		/*AdminCustomers prod("customers.txt");
		prod.Read();
		prod.Show();*/
		AdminProducts prod("products.txt");
		prod.Read();
		//prod.Show();
		prod.Sort(0, 4, 31);
	}
	catch (const char* er)
	{
		cls();
		cout << er;
	}
	
};
