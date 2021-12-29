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





void main()
{
	//Management<Product> manag("products.txt");
	AdminCustomers cust("customers.txt");
	cust.Read();
	cust.Show();

};
