#include "AdminCustomers.h"

template <class type>
void DoAdministation(Admin<type>* admin, int _case)
{
	if (admin)
	{
		switch (_case)
		{
		case 0:
			admin->Show();
			break;
		case 1:
			admin->DrawAdding();
			break;
		case 2:
			admin->DrawDeleting();
		}
		delete admin;
	}
	else throw exception("Pointer to admin is null!");
}

void main()
{
	const char products[] = "products.txt";
	const char customers[] = "customers.txt";
	Menu menu(CenterTop);
	menu << "Show products"
		<< "Add product"
		<< "Delete product"
		<< "Show customers"
		<< "Add customer"
		<< "Delete customer"
		<< "Show income"
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
				DoAdministation(new AdminProducts(products), item);
				break;
			case 3:
			case 4:
			case 5:
				DoAdministation(new AdminCustomers(customers), item - 3);
				break;
			case 6:
			{		
				AdminCustomers admin_cust(customers);
				admin_cust.ShowIncome(products);
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
			getch();
			cls();
		}
		catch (exception& error)
		{
			cls();
			DrawSomething(error.what());
		}
	}
}