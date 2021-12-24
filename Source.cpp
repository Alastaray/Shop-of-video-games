#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include "fun_console.h"
#include "Window.h"
#include "List.h"
#include "Management.h"
#include "Products and customers.h"
using namespace std;
#pragma warning(disable: 4996)





void main()
{
	AdminProducts cust;
	
	cust.Read();
	cust.Show();

};
