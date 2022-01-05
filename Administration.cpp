#include "Administration.h"


void AdminProducts::Create()
{
	const char* phrases[5] = {
		"Enter the name: ",
		"Enter the amount: ",
		"Enter the price: ",
		"Enter the puchase_price: ",
		"Price can't be less than puchase price"
	};
	char name[25];
	int amount = 0;
	double price = 0, puchase_price = 0;
	Window win(45, 5, CenterTop);
	Input Cin;
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		win.DrawBox(phrases[i], 2, 2);
		switch (i)
		{
		case 0:
			strcpy(name, Cin.GetStr(25, 3));
			break;
		case 1:
			amount = Cin.GetInt(4, 1);
			break;
		case 2:
			price = Cin.GetDouble(8, 1);
			break;
		case 3:
			x = GetCurrentX();
			y = GetCurrentY();
			while (true)
			{
				puchase_price = Cin.GetDouble(8, 1);
				if (price > puchase_price)break;
				win.WriteLine(phrases[4],2, 3);
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
bool AdminProducts::Sort(const char* name, int amount, double price, double purchase_price, bool low_to_high)
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
				if (low_to_high)sort << list[i];
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
				if (low_to_high)sort << list[i];
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
				if (low_to_high)sort << list[i];
				else sort.AddHead(list[i]);
			}
			else if ((name && CompareStr(name, list[i].GetName())) ||
				(amount && amount == list[i].GetAmount()) ||
				(price && price == list[i].GetPrice()) ||
				(purchase_price && purchase_price == list[i].GetPurchasePrice()))
			{
				if (low_to_high)sort << list[i];
				else sort.AddHead(list[i]);
			}
		}
	}
	else if (!low_to_high)
	{
		for (int i = 0; i < list.GetCount(); i++)
			sort.AddHead(list[i]);
	}
	if (sort.GetCount())return Show(sort);
	else return Show();
}
bool AdminProducts::Search(const char* val)
{
	List<Product> search;
	if (val)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (CompareStr(val, list[i].GetName()) ||
				atoi(val) == list[i].GetAmount() ||
				atof(val) == list[i].GetPrice() ||
				atof(val) == list[i].GetPurchasePrice())
				search << list[i];
				
		}

	}

	return Show(search);

}
void AdminProducts::DrawElement(List<Product>& l, int row, int col, int x, int y)
{
	switch (col)
	{
	case 0:
		WriteLine(l[row].GetId(), x, y);
		break;
	case 1:
		WriteLine(l[row].GetName(), x, y);
		break;
	case 2:
		WriteLine(l[row].GetAmount(), x, y);
		break;
	case 3:
		WriteLine(l[row].GetPrice(), x, y);
		break;
	case 4:
		WriteLine(l[row].GetPurchasePrice(), x, y);
		break;
	}
}
void AdminProducts::DrawElement(int row, int col, int x, int y)
{
	switch (col)
	{
	case 0:
		WriteLine(list[row].GetId(), x, y);
		break;
	case 1:
		WriteLine(list[row].GetName(), x, y);
		break;
	case 2:
		WriteLine(list[row].GetAmount(), x, y);
		break;
	case 3:
		WriteLine(list[row].GetPrice(), x, y);
		break;
	case 4:
		WriteLine(list[row].GetPurchasePrice(), x, y);
		break;
	}
}
bool AdminProducts::DoSorting()
{
	int x=0, y=0;
	Button sort("Sort", 6, 3, CenterBot, 12, -4);
	Button enter_name("Enter the name: ", 35, 3, LeftTop, 10, 5);
	Button enter_amount("Enter the amount: ", 35, 3, RightTop, -10, 5);
	Button enter_price("Enter the price: ", 35, 3, RightBot, -10, 5);
	Button enter_pur_price("Enter the puchase price: ", 35, 3, LeftBot, 10, 5);
	while (true)
	{
		enter_name.DrawButton(2);
		enter_amount.DrawButton(2);
		enter_price.DrawButton(2);
		enter_pur_price.DrawButton(2);
		sort.DrawButton();
		switch (y)
		{
		case 0:
			enter_name.DrawActiveBut(2);
			break;
		case 1:
			enter_amount.DrawActiveBut(2);
			break;
		case 2:
			enter_price.DrawActiveBut(2);
			break;
		case 3:
			enter_pur_price.DrawActiveBut(2);
			break;
		case 4:
			sort.DrawActiveBut();
			break;
		}
		Move(key, x, y, 0, 1);
		if (y < 0)y = 4;
		if (y > 4)y = 0;
	}
	
	
	//return Sort(name,amount,price,puchase_price,ascending);
	return true;
}
bool AdminProducts::DoSearching()
{
	cls();
	char str[38];	
	Window win(47, 3, LeftTop,30,5);
	Input Cin;
	win.DrawBox();
	win.WriteLine("Enter: ", 2);
	strcpy(str, Cin.Get(37));
	return Search(str);
}





















//void AdminCustomers::Create()
//{
//	AdminProducts prod;
//	prod.Read();
//}
//void AdminCustomers::Add(const char* name, const char* prod_name, int amount, double price)
//{
//	static int id = number_st;
//	list << Customer(id, name, prod_name, amount, price);
//	id++;
//}
//void AdminCustomers::Sort(const char* name, const char* prod_name, int amount, double price, bool ascending)
//{
//	List<Customer> sort;
//	if (name || amount || price || prod_name)
//	{
//		for (int i = 0; i < list.GetCount(); i++)
//		{
//
//			if ((name && CompareStr(name, list[i].GetName())) &&
//				(amount && amount == list[i].GetAmount()) &&
//				(price && price == list[i].GetPrice()) &&
//				(prod_name && CompareStr(prod_name, list[i].GetProdName())))
//			{
//				if (ascending)sort << list[i];
//				else sort.AddHead(list[i]);
//			}
//
//
//			else if ((name && CompareStr(name, list[i].GetName())) &&
//				(amount && amount == list[i].GetAmount()) &&
//				(price && price == list[i].GetPrice())
//				||
//				(amount && amount == list[i].GetAmount()) &&
//				(price && price == list[i].GetPrice()) &&
//				(prod_name && CompareStr(prod_name, list[i].GetProdName()))
//				||
//				(name && CompareStr(name, list[i].GetName())) &&
//				(amount && amount == list[i].GetAmount()) &&
//				(prod_name && CompareStr(prod_name, list[i].GetProdName())))
//			{
//				if (ascending)sort << list[i];
//				else sort.AddHead(list[i]);
//			}
//
//			else if ((name && CompareStr(name, list[i].GetName())) &&
//				(amount && amount == list[i].GetAmount())
//				||
//				(name && CompareStr(name, list[i].GetName())) &&
//				(price && price == list[i].GetPrice())
//				||
//				(name && CompareStr(name, list[i].GetName())) &&
//				(prod_name && CompareStr(prod_name, list[i].GetProdName()))
//				||
//				(price && price == list[i].GetPrice()) &&
//				(prod_name && CompareStr(prod_name, list[i].GetProdName()))
//				||
//				(price && price == list[i].GetPrice()) &&
//				(amount && amount == list[i].GetAmount())
//				||
//				(amount && amount == list[i].GetAmount()) &&
//				(prod_name && CompareStr(prod_name, list[i].GetProdName())))
//			{
//				if (ascending)sort << list[i];
//				else sort.AddHead(list[i]);
//			}
//
//			else if ((name && CompareStr(name, list[i].GetName())) ||
//				(amount && amount == list[i].GetAmount()) ||
//				(price && price == list[i].GetPrice()) ||
//				(prod_name && CompareStr(prod_name, list[i].GetProdName())))
//			{
//				if (ascending)sort << list[i];
//				else sort.AddHead(list[i]);
//			}
//
//		}
//	}
//	else if (!ascending)
//	{
//		for (int i = 0; i < list.GetCount(); i++)
//			sort.AddHead(list[i]);
//	}
//	if (sort.GetCount())Show(sort);
//	else Show();
//}
//void AdminCustomers::Search(const char* val, bool ascending)
//{
//	List<Customer> sort;
//	if (val)
//	{
//		for (int i = 0; i < list.GetCount(); i++)
//		{
//			if (CompareStr(val, list[i].GetName()) ||
//				atoi(val) == list[i].GetAmount() ||
//				atof(val) == list[i].GetPrice() ||
//				CompareStr(val, list[i].GetProdName()))
//			{
//				if (ascending)sort << list[i];
//				else sort.AddHead(list[i]);
//			}
//		}
//
//	}
//	else if (!ascending)
//	{
//		for (int i = 0; i < list.GetCount(); i++)
//			sort.AddHead(list[i]);
//	}
//	Show(sort);
//
//}
//void AdminCustomers::DrawElement(List<Customer>& l, int row, int col, int x, int y)
//{
//
//	switch (col)
//	{
//	case 0:
//		WriteLine(list[row].GetId(), x, y);
//		break;
//	case 1:
//		WriteLine(list[row].GetName(), x, y);
//		break;
//	case 2:
//		WriteLine(list[row].GetProdName(), x, y);
//		break;
//	case 3:
//		WriteLine(list[row].GetAmount(), x, y);
//		break;
//	case 4:
//		WriteLine(list[row].GetPrice(), x, y);
//		break;
//	}
//}
//void AdminCustomers::DrawElement(int row, int col, int x, int y)
//{
//	switch (col)
//	{
//	case 0:
//		WriteLine(list[row].GetId(), x, y);
//		break;
//	case 1:
//		WriteLine(list[row].GetName(), x, y);
//		break;
//	case 2:
//		WriteLine(list[row].GetProdName(), x, y);
//		break;
//	case 3:
//		WriteLine(list[row].GetAmount(), x, y);
//		break;
//	case 4:
//		WriteLine(list[row].GetPrice(), x, y);
//		break;
//	}
//}
