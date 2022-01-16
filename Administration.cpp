#include "Administration.h"


void AdminProducts::DrawAdding()
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
	Window win(35, 5, CenterTop,0,7);
	Input Cin;
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		win.DrawBox(phrases[i], 0, 0, 2, 2);
		switch (i)
		{
		case 0:
			strcpy(name, Cin.Get(15, 3));
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
				win.WriteLine(phrases[4], 0, 0, 2, 3);
				GotoXY(x, y);
				cout << "        ";
				GotoXY(x, y);
			}
			break;
		}
	}
	Add(name, amount, price, puchase_price);
	DrawMessage("Product was added!");
}
void AdminProducts::Add(const char* name, int amount, double price, double puchase_price)
{
	static int id = number_st;
	list << Product(id, name, amount, price, puchase_price);
	id++;
}
int AdminProducts::Sort(int amount, double price, double purchase_price, bool low_to_high)
{
	sorted.RemoveAll();
	if (amount && price && purchase_price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (amount >= list[i].GetAmount() &&
				price >= list[i].GetPrice() &&
				purchase_price == list[i].GetPurchasePrice())
			{
				if (low_to_high)sorted.AddTail(list[i]);
				else sorted.AddHead(list[i]);
			}
		}
	}
	else if (price && purchase_price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (price >= list[i].GetPrice() &&
				purchase_price >= list[i].GetPurchasePrice())
			{
				if (low_to_high)sorted.AddTail(list[i]);
				else sorted.AddHead(list[i]);
			}
		}
	}
	else if (amount && price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (price && price >= list[i].GetPrice() &&
				amount && amount >= list[i].GetAmount())
			{
				if (low_to_high)sorted.AddTail(list[i]);
				else sorted.AddHead(list[i]);
			}
		}
	}
	else if (amount && purchase_price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (amount >= list[i].GetAmount() &&
				purchase_price >= list[i].GetPurchasePrice())
			{
				if (low_to_high)sorted.AddTail(list[i]);
				else sorted.AddHead(list[i]);
			}
		}
	}
	else if (amount || price || purchase_price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (amount >= list[i].GetAmount() ||
				price >= list[i].GetPrice() ||
				purchase_price >= list[i].GetPurchasePrice())
			{
				if (low_to_high)sorted.AddTail(list[i]);
				else sorted.AddHead(list[i]);
			}
		}
	}
	else if (!amount && !price && !purchase_price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (low_to_high)sorted.AddTail(list[i]);
			else sorted.AddHead(list[i]);
		}
	}
	if (sorted.GetCount())return 2;
	else
	{
		DrawMessage("Page not found!");
		sorted = list;
		return true;
	}
}
int AdminProducts::Search(const char* val)
{
	sorted.RemoveAll();
	if (val)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (CompareStr(val, list[i].GetName()) ||
				atoi(val) == list[i].GetAmount() ||
				atof(val) == list[i].GetPrice() ||
				atof(val) == list[i].GetPurchasePrice())
				sorted << list[i];
		}
	}
	if (sorted.GetCount())return 2;
	else
	{
		DrawMessage("Page not found!");
		sorted = list;
		return true;
	}
}
void AdminProducts::DrawElement(List<Product>& _list, int row, int col, int x, int y)
{
	switch (col)
	{
	case 0:
		WriteLine(_list[row].GetId(), x, y);
		break;
	case 1:
		WriteLine(_list[row].GetName(), x, y);
		break;
	case 2:
		WriteLine(_list[row].GetAmount(), x, y);
		break;
	case 3:
		WriteLine(_list[row].GetPrice(), x, y);
		break;
	case 4:
		WriteLine(_list[row].GetPurchasePrice(), x, y);
		break;
	}
}
int AdminProducts::DrawSorting()
{
	cls();
	char key = 0;
	int y=0;
	int amount = 0;
	double price = 0, puchase_price = 0;
	bool low_to_high = true;
	Input Cin;
	Message enter_amount("Enter the amount:", 18, 3, CenterTop, 0, 4);
	Message enter_price("Enter the price:", 17, 3, CenterTop, 0, 6);
	Message enter_pur_price("Enter the puchase price:", 25, 3, CenterTop, 0, 8);
	Message High_to_low("High-to-low", 13, 3, CenterTop, 3, 11);
	Message Low_to_high("Low-to-high", 13, 3, CenterTop, 3, 14);
	Message sort("Sort", 6, 3, CenterTop, 6, 17);
	while (true)
	{		
		enter_amount.DoTable();
		enter_price.DoTable();
		enter_pur_price.DoTable();
		sort.DrawBox();
		High_to_low.DrawBox();
		Low_to_high.DrawBox();
		switch (y)
		{
		case 0:
			enter_amount.FillLine();
			if (key == 13)amount = Cin.GetInt(5,0,0,0,1);
			break;
		case 1:
			enter_price.FillLine();
			if (key == 13)price = Cin.GetDouble(5, 0, 0, 0, 1);
			break;
		case 2:
			enter_pur_price.FillLine();
			if (key == 13)puchase_price = Cin.GetDouble(5, 0, 0, 0, 1);
			break;
		case 3:
			High_to_low.DrawActiveMsg();
			if (key == 13)low_to_high = false;
			break;
		case 4:			
			Low_to_high.DrawActiveMsg();
			if (key == 13)low_to_high = true;
			break;
		case 5:
			sort.DrawActiveMsg();
			if (key == 13)return Sort(amount, price, puchase_price, low_to_high);
			break;	
		}
		Move(key, y, y, 1, 1);
		if (key == 27)break;
		if (y < 0)y = 5;
		if (y > 5)y = 0;
	}
	
	
	return Sort(amount,price,puchase_price,low_to_high);
}
int AdminProducts::DrawSearching()
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
void AdminProducts::ChangeData(int id, int whom)
{
	if (id < 0)throw "Id can't be the negative!";
	Input Cin;
	switch (whom)
	{
	case 1:
		list[id].SetName(Cin.Get(15, 3, size_cols * whom + 1));
		break;
	case 2:
		list[id].SetAmount(Cin.GetInt(5, 0, size_cols * whom + 1));
		break;
	case 3:
		list[id].SetPrice(Cin.GetDouble(5, 0, size_cols * whom + 1));
		break;
	case 4:
		list[id].SetPurchasePrice(Cin.GetDouble(5, 0, size_cols * whom + 1));
		break;
	}
}




void AdminCustomers::DrawAdding()
{
	cls();
	int index,
		amount;
	char name[16];
	Window win(35, 5, CenterTop, 0, 7);
	Input Cin;
	win.DrawBox("Enter the name: ", 0, 0, 2, 2);
	strcpy(name, Cin.GetStr(15, 3));

	AdminProducts product("products.txt");
	product.Read();
	this->SetWinParam(85, product.GetCount() * 2 + 1, LeftTop, 0, 2);
	this->SetCols(5);
	this->SetRows(product.GetCount());
	product.SetWinParam(85, product.GetCount() * 2 + 1, LeftTop, 0, 2);
	product.SetCols(5);
	product.SetRows(product.GetCount());
	index = ShowProducts(product);
	if (index == -1)return;
	cls();
	win.DrawBox("Enter the amount: ", 0, 0, 2, 2);
	amount = Cin.GetInt(5);
	if (amount >= product[index].GetAmount())
	{
		Add(name, product[index].GetName(), product[index].GetAmount(), product[index].GetPrice());
		product.RemoveAt(index);
	}
	else
	{
		product[index].ChangeAmount(-amount);
		Add(name, product[index].GetName(), amount, product[index].GetPrice());
	}
	
	DrawMessage("Product was bought!");
}
int AdminCustomers::ShowProducts(AdminProducts& product)
{
	char key;
	int x = 0, y = 0,
		row, col;
	Message back("Back", 10, 3, RightTop, 8, 2);
	while (true)
	{
		product.DrawData(product.GetList());
		back.DrawBox();
		if (!size_cols || !size_rows)break;
		row = y / size_rows;
		col = x / size_cols;
		for (int i = 0; i < cols; i++)
		{
			x = size_cols * i;
			product.DrawActiveCell(product.GetList(), y / size_rows, x / size_cols, x, y);
		}
		Move(key, x, y, size_cols, size_rows);
		if (key == 27)return -1;
		if (key == 13)return row;
		if (x >= size_cols * cols)
		{
			product.DrawData(product.GetList());
			back.DrawActiveMsg();
			Move(key, x, y, size_cols, size_rows);
			if (key == 13)return -1;
			if (key == 72 || key == 'w' || key == 'W')
				y += size_rows;
			if (key == 80 || key == 's' || key == 'S')
				y -= size_rows;
		}
		CheckXY(x, y);
	}
}
void AdminCustomers::Add(const char* name, const char* prod_name, int amount, double price)
{
	static int id = number_st;
	list << Customer(id, name, prod_name, amount, price);
	id++;
}
int AdminCustomers::Sort(int amount, double price, bool low_to_high)
{
	sorted.RemoveAll();
	if (amount && price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (amount >= list[i].GetAmount() &&
				price >= list[i].GetPrice())
			{
				if (low_to_high)sorted.AddTail(list[i]);
				else sorted.AddHead(list[i]);
			}
		}
	}
	else if (amount || price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (amount >= list[i].GetAmount() ||
				price >= list[i].GetPrice())
			{
				if (low_to_high)sorted.AddTail(list[i]);
				else sorted.AddHead(list[i]);
			}
		}
	}
	else if (!amount && !price)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (low_to_high)sorted.AddTail(list[i]);
			else sorted.AddHead(list[i]);
		}
	}
	if (sorted.GetCount())return 2;
	else
	{
		DrawMessage("Page not found!");
		sorted = list;
		return true;
	}
}
int AdminCustomers::Search(const char* val)
{
	sorted.RemoveAll();
	if (val)
	{
		for (int i = 0; i < list.GetCount(); i++)
		{
			if (CompareStr(val, list[i].GetName()) ||
				atoi(val) == list[i].GetAmount() ||
				atof(val) == list[i].GetPrice() ||
				CompareStr(val, list[i].GetProdName()))
				sorted << list[i];
		}
	}
	if (sorted.GetCount())return 2;
	else
	{
		DrawMessage("Page not found!");
		sorted = list;
		return true;
	}
}
int AdminCustomers::DrawSorting()
{
	cls();
	char key = 0;
	int y = 0;
	int amount = 0;
	double price = 0;
	bool low_to_high = true;
	Input Cin;
	Message enter_amount("Enter the amount:", 18, 3, CenterTop, 0, 6);
	Message enter_price("Enter the price:", 17, 3, CenterTop, 0, 8);
	Message High_to_low("High-to-low", 13, 3, CenterTop, 3, 11);
	Message Low_to_high("Low-to-high", 13, 3, CenterTop, 3, 14);
	Message sort("Sort", 6, 3, CenterTop, 6, 17);
	while (true)
	{
		enter_amount.DoTable();
		enter_price.DoTable();
		sort.DrawBox();
		High_to_low.DrawBox();
		Low_to_high.DrawBox();
		switch (y)
		{
		case 0:
			enter_amount.FillLine();
			if (key == 13)amount = Cin.GetInt(5, 0, 0, 0, 1);
			break;
		case 1:
			enter_price.FillLine();
			if (key == 13)price = Cin.GetDouble(5, 0, 0, 0, 1);
			break;
		
		case 2:
			High_to_low.DrawActiveMsg();
			if (key == 13)low_to_high = false;
			break;
		case 3:
			Low_to_high.DrawActiveMsg();
			if (key == 13)low_to_high = true;
			break;
		case 4:
			sort.DrawActiveMsg();
			if (key == 13)return Sort(amount, price, low_to_high);
			break;
		}
		Move(key, y, y, 1, 1);
		if (key == 27)break;
		if (y < 0)y = 4;
		if (y > 4)y = 0;
	}
	return Sort(amount, price, low_to_high);
}
int AdminCustomers::DrawSearching()
{
	cls();
	char str[20];
	Window win(35, 3, LeftTop, 30, 5);
	Input Cin;
	win.DrawBox();
	win.WriteLine("Enter: ", 2);
	strcpy(str, Cin.Get(20));
	return Search(str);
}
void AdminCustomers::DrawElement(List<Customer>& _list, int row, int col, int x, int y)
{

	switch (col)
	{
	case 0:
		WriteLine(_list[row].GetId(), x, y);
		break;
	case 1:
		WriteLine(_list[row].GetName(), x, y);
		break;
	case 2:
		WriteLine(_list[row].GetProdName(), x, y);
		break;
	case 3:
		WriteLine(_list[row].GetAmount(), x, y);
		break;
	case 4:
		WriteLine(_list[row].GetPrice(), x, y);
		break;
	}
}
void AdminCustomers::ChangeData(int id, int whom)
{
	if (id < 0)throw "Id can't be the negative!";
	Input Cin;
	switch (whom)
	{
	case 1:
		list[id].SetName(Cin.Get(15, 3, size_cols * whom + 1));
		break;
	case 2:
		list[id].SetProdName(Cin.Get(15, 3, size_cols * whom + 1));
		break;
	case 3:
		list[id].SetAmount(Cin.GetInt(5, 0, size_cols * whom + 1));
		break;
	case 4:
		list[id].SetPrice(Cin.GetDouble(5, 0, size_cols * whom + 1));
		break;
	}
}
