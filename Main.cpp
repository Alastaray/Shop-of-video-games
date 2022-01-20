#include <iostream>
#include <windows.h>
#include "AdminCustomers.h"
#include "AdminProducts.h"
using namespace std;
#pragma warning(disable: 4996)

		


void main()
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
	menu.SetMenuParam(5, 5);
	while (true)
	{
		try
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
			{
				AdminCustomers admin_cust("customers.txt");
				AdminProducts admin_prod("products.txt");				
				char result[20] = {"Income is "};
				strcat(result, IntToChar(CreateReport(admin_prod, admin_cust)));
				Message::WriteMessage(result);
				break;
			}
			case 7:
				cls();
				return;
				break;
			}
		}
		catch (ListException& error)
		{
			cls();
			cout << error.what() << endl
				<< "Index = " << error.GetValue() << endl
				<< "Count = " << error.GetCount() << endl;
		}
		catch (exception& error)
		{
			cls();
			Message::WriteMessage(error.what());
		}
	}
}