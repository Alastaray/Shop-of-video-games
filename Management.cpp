#include "Management.h"



void AdminProducts::Create()
{
	Window win(45, 5, CenterTop);
	const char* phrases[5] = {
		"Enter the name: ",
		"Enter the amount: ",
		"Enter the price: ",
		"Enter the puchase_price: ",
		"Price can't be less than puchase_price"
	};
	ShowCaret(true);
	Input Cin;
	char name[25];
	int amount = 0;
	double price = 0, puchase_price = 0;
	for (int i = 0; i < 4; i++)
	{
		win.DrawBox();
		win.WriteLine(phrases[i], 0, 0, 2, 2);

		switch (i)
		{
		case 0:
			strcpy(name, Cin.GetStr(25));
			break;
		case 1:
			amount = Cin.GetInt(4);
			break;
		case 2:
			price = Cin.GetDouble(8);
			break;
		case 3:
			int x = GetCurrentX();
			int y = GetCurrentY();
			while (true)
			{
				puchase_price = Cin.GetDouble(8);
				if (price > puchase_price)break;
				win.WriteLine(phrases[4], 0, 0, 2, 3);
				GotoXY(x, y);
				cout << "        ";
				GotoXY(x, y);
			}
			break;
		}
	}
	Add(name, amount, price, puchase_price);

}
void AdminProducts::Add(const char* name, int amount, double price, double puchase_price)
{
	static int id = number_st;
	list << Product(id, name, amount, price, puchase_price);
	id++;
}
void AdminProducts::Sort(const char* name, int amount, double price, double purchase_price, bool ascending)
{
	List<Product> sort;
	if (name || amount || price || purchase_price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{

			if ((name && CompareStr(name, list[i].GetName())) &&
				(amount && amount == list[i].GetAmount()) &&
				(price && price == list[i].GetPrice()) &&
				(purchase_price && purchase_price == list[i].GetPurchasePrice()))
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}
			else if ((name && CompareStr(name, list[i].GetName())) &&
				(amount && amount == list[i].GetAmount()) &&
				(price && price == list[i].GetPrice())
				||
				(amount && amount == list[i].GetAmount()) &&
				(price && price == list[i].GetPrice()) &&
				(purchase_price && purchase_price == list[i].GetPurchasePrice())
				||
				(name && CompareStr(name, list[i].GetName())) &&
				(amount && amount == list[i].GetAmount()) &&
				(purchase_price && purchase_price == list[i].GetPurchasePrice()))
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}
			else if ((name && CompareStr(name, list[i].GetName())) &&
				(amount && amount == list[i].GetAmount())
				||
				(name && CompareStr(name, list[i].GetName())) &&
				(price && price == list[i].GetPrice())
				||
				(name && CompareStr(name, list[i].GetName())) &&
				(purchase_price && purchase_price == list[i].GetPurchasePrice())
				||
				(price && price == list[i].GetPrice()) &&
				(purchase_price && purchase_price == list[i].GetPurchasePrice())
				||
				(price && price == list[i].GetPrice()) &&
				(amount && amount == list[i].GetAmount())
				||
				(amount && amount == list[i].GetAmount()) &&
				(purchase_price && purchase_price == list[i].GetPurchasePrice()))
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}
			else if ((name && CompareStr(name, list[i].GetName())) ||
				(amount && amount == list[i].GetAmount()) ||
				(price && price == list[i].GetPrice()) ||
				(purchase_price && purchase_price == list[i].GetPurchasePrice()))
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}
		}
	}
	else if (!ascending)
	{
		for (int i = 0; i < list.GetCount(); i++)
			sort.AddHead(list[i]);
	}
	if (sort.GetCount())Show(sort);
	else Show();
}
void AdminProducts::Search(const char* val, bool ascending)
{
	List<Product> sort;
	if (val)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (CompareStr(val, list[i].GetName()) ||
				atoi(val) == list[i].GetAmount() ||
				atof(val) == list[i].GetPrice() ||
				atof(val) == list[i].GetPurchasePrice())
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}
		}
		
	}
	else if (!ascending)
	{
		for (int i = 0; i < list.GetCount(); i++)
			sort.AddHead(list[i]);
	}
	Show(sort);
	
}


//void AdminCustomers::Create()
//{
//	AdminProducts prod;
//	prod.Read();
//}
void AdminCustomers::Add(const char* name, const char* prod_name, int amount, double price)
{
	static int id = number_st;
	list << Customer(id, name, prod_name, amount, price);
	id++;
}
void AdminCustomers::Sort(const char* name, const char* prod_name, int amount, double price, bool ascending)
{
	List<Customer> sort;
	if (name || amount || price || prod_name)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{

			if ((name && CompareStr(name, list[i].GetName())) &&
				(amount && amount == list[i].GetAmount()) &&
				(price && price == list[i].GetPrice()) &&
				(prod_name && CompareStr(prod_name, list[i].GetProdName())))
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}


			else if ((name && CompareStr(name, list[i].GetName())) &&
				(amount && amount == list[i].GetAmount()) &&
				(price && price == list[i].GetPrice())
				||
				(amount && amount == list[i].GetAmount()) &&
				(price && price == list[i].GetPrice()) &&
				(prod_name && CompareStr(prod_name, list[i].GetProdName()))
				||
				(name && CompareStr(name, list[i].GetName())) &&
				(amount && amount == list[i].GetAmount()) &&
				(prod_name && CompareStr(prod_name, list[i].GetProdName())))
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}

			else if ((name && CompareStr(name, list[i].GetName())) &&
				(amount && amount == list[i].GetAmount())
				||
				(name && CompareStr(name, list[i].GetName())) &&
				(price && price == list[i].GetPrice())
				||
				(name && CompareStr(name, list[i].GetName())) &&
				(prod_name && CompareStr(prod_name, list[i].GetProdName()))
				||
				(price && price == list[i].GetPrice()) &&
				(prod_name && CompareStr(prod_name, list[i].GetProdName()))
				||
				(price && price == list[i].GetPrice()) &&
				(amount && amount == list[i].GetAmount())
				||
				(amount && amount == list[i].GetAmount()) &&
				(prod_name && CompareStr(prod_name, list[i].GetProdName())))
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}

			else if ((name && CompareStr(name, list[i].GetName())) ||
				(amount && amount == list[i].GetAmount()) ||
				(price && price == list[i].GetPrice()) ||
				(prod_name && CompareStr(prod_name, list[i].GetProdName())))
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}
			
		}
	}
	else if (!ascending)
	{
		for (int i = 0; i < list.GetCount(); i++)
			sort.AddHead(list[i]);
	}		
	if (sort.GetCount())Show(sort);
	else Show();
}
void AdminCustomers::Search(const char* val, bool ascending)
{
	List<Customer> sort;
	if (val)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (CompareStr(val, list[i].GetName()) ||
				atoi(val) == list[i].GetAmount() ||
				atof(val) == list[i].GetPrice() ||
				CompareStr(val, list[i].GetProdName()))
			{
				if (ascending)sort << list[i];
				else sort.AddHead(list[i]);
			}
		}

	}
	else if (!ascending)
	{
		for (int i = 0; i < list.GetCount(); i++)
			sort.AddHead(list[i]);
	}
	Show(sort);

}
