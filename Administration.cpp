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
	char name[16];
	int amount = 0;
	double price = 0, puchase_price = 0;
	Window win(35, 5, CenterTop);
	Input Cin;
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		win.DrawBox(phrases[i], 2, 2);
		switch (i)
		{
		case 0:
			strcpy(name, Cin.GetStr(15, 3));
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
	if ((name && name[0]) || amount || price || purchase_price)
	{

		for (int i = 0; i < list.GetCount(); i++)
		{
			if ((name && (name[0] && CompareStr(name, list[i].GetName()))) &&
				(amount && amount == list[i].GetAmount()) &&
				(price && price == list[i].GetPrice()) &&
				(purchase_price && purchase_price == list[i].GetPurchasePrice()))
			{
				if (low_to_high)sort << list[i];
				else sort.AddHead(list[i]);
			}
			else if ((name && (name[0] && CompareStr(name, list[i].GetName()))) &&
				(amount && amount >= list[i].GetAmount()) &&
				(price && price >= list[i].GetPrice())
				||
				(amount && amount >= list[i].GetAmount()) &&
				(price && price >= list[i].GetPrice()) &&
				(purchase_price && purchase_price >= list[i].GetPurchasePrice())
				||
				(name && (name[0] && CompareStr(name, list[i].GetName()))) &&
				(amount && amount >= list[i].GetAmount()) &&
				(purchase_price && purchase_price >= list[i].GetPurchasePrice()))
			{
				if (low_to_high)sort << list[i];
				else sort.AddHead(list[i]);
			}
			else if ((name && (name[0] && CompareStr(name, list[i].GetName()))) &&
				(amount && amount >= list[i].GetAmount())
				||
				(name && (name[0] && CompareStr(name, list[i].GetName()))) &&
				(price && price >= list[i].GetPrice())
				||
				(name && (name[0] && CompareStr(name, list[i].GetName()))) &&
				(purchase_price && purchase_price >= list[i].GetPurchasePrice())
				||
				(price && price >= list[i].GetPrice()) &&
				(purchase_price && purchase_price >= list[i].GetPurchasePrice())
				||
				(price && price >= list[i].GetPrice()) &&
				(amount && amount >= list[i].GetAmount())
				||
				(amount && amount >= list[i].GetAmount()) &&
				(purchase_price && purchase_price >= list[i].GetPurchasePrice()))
			{
				
				if (low_to_high)sort << list[i];
				else sort.AddHead(list[i]);
			}
			else if ((name && (name[0] && CompareStr(name, list[i].GetName()))) ||
				(amount && amount >= list[i].GetAmount()) ||
				(price && price >= list[i].GetPrice()) ||
				(purchase_price && purchase_price >= list[i].GetPurchasePrice()))
			{
				if (low_to_high)sort << list[i];
				else sort.AddHead(list[i]);
			}
		}
	}
	else if (!low_to_high &&!sort.GetCount())
	{
		for (int i = 0; i < list.GetCount(); i++)
			sort.AddHead(list[i]);
	}
	if (sort.GetCount())return Show(sort);
	else
	{
		cls();
		Button error("Page not found!", 17, 3, CenterTop,0,10);
		error.DrawName();
		_getch();
		return true;
	}
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
	if (search.GetCount())return Show(search);
	else
	{
		cls();
		Button error("Page not found!", 17, 3, CenterTop, 0, 10);
		error.DrawName();
		_getch();
		return true;
	}
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
	cls();
	int y=0;
	char name[20];
	int amount = 0;
	double price = 0, puchase_price = 0;
	bool low_to_high = true;
	Input Cin;
	Button enter_name("Enter the name:", 16, 3, CenterTop, 0, 2);
	Button enter_amount("Enter the amount:", 18, 3, CenterTop, 0, 4);
	Button enter_price("Enter the price:", 17, 3, CenterTop, 0, 6);
	Button enter_pur_price("Enter the puchase price:", 25, 3, CenterTop, 0, 8);
	Button High_to_low("High-to-low", 13, 3, CenterTop, 3, 11);
	Button Low_to_high("Low-to-high", 13, 3, CenterTop, 3, 14);
	Button sort("Sort", 6, 3, CenterTop, 6, 17);
	while (true)
	{		
		enter_name.DrawName();
		enter_amount.DrawName();
		enter_price.DrawName();
		enter_pur_price.DrawName();
		sort.DrawButton();
		High_to_low.DrawButton();
		Low_to_high.DrawButton();
		switch (y)
		{
		case 0:
			enter_name.FillRow();
			if(key==13)strcpy(name, Cin.Get(21, 3, 0, 0, 1));
			break;
		case 1:
			enter_amount.FillRow();
			if (key == 13)amount = Cin.GetInt(5,0,0,0,1);
			break;
		case 2:
			enter_price.FillRow();
			if (key == 13)price = Cin.GetDouble(5, 0, 0, 0, 1);
			break;
		case 3:
			enter_pur_price.FillRow();
			if (key == 13)puchase_price = Cin.GetDouble(5, 0, 0, 0, 1);
			break;
		case 4:
			High_to_low.DrawActiveBut();
			if (key == 13)low_to_high = true;
			break;
		case 5:			
			Low_to_high.DrawActiveBut();
			if (key == 13)low_to_high = false;
			break;
		case 6:
			sort.DrawActiveBut();
			if (key == 13)return Sort(name, amount, price, puchase_price, low_to_high);
			break;	
		}
		Move(key, y, y, 1, 1);
		if (key == 27)break;
		if (y < 0)y = 6;
		if (y > 6)y = 0;
	}
	
	
	return Sort(name,amount,price,puchase_price,low_to_high);
}
bool AdminProducts::DoSearching()
{
	cls();
	char str[20];	
	Window win(35, 3, LeftTop,30,5);
	Input Cin;
	win.DrawBox();
	win.WriteLine("Enter: ", 2);
	strcpy(str, Cin.Get(20));
	return Search(str);
}
void AdminProducts::Editing(int row, int col)
{
	Input Cin;
	switch (col)
	{
	case 0:
		return;
	case 1:
		list[row].SetName(Cin.Get(15, 3, size_cols * col+1));
		break;
	case 2:
		list[row].SetAmount(Cin.GetInt(5, 0, size_cols * col+1));
		break;
	case 3:
		list[row].SetPrice(Cin.GetDouble(5, 0, size_cols * col+1));
		break;
	case 4:
		list[row].SetPurchasePrice(Cin.GetDouble(5, 0, size_cols * col+1));
		break;
	}
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
