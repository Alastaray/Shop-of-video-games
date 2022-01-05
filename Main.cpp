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
		//prod.Add("Sacred", 4, 30.2, 34.5);
		//prod.RemoveAt(0);
		prod.Show();
		prod.DoSorting();
		getch();
	}
	catch (const char* er)
	{
		cls();
		cout << er;
	}

};
