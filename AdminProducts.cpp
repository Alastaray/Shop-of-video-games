#include "AdminProducts.h"





void AdminProducts::DrawAdding()
{
	cls();
	const char* phrases[5] = {
		"Enter the name: ",
		"Enter the amount: ",
		"Enter the price: ",
		"Enter the puchase_price: ",
		"Purchase price can't be bigger than price"
	};
	char name[16];
	int amount = 0;
	double price = 0, purchase_price = 0;
	Window win(35, 5, CenterTop, 0, 7);
	Input Cin;
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		win.DrawFrame(phrases[i], 2, 1);
		switch (i)
		{
		case 0:
			strcpy(name, Cin.GetData(15, 3));
			if (!Cin.Success())return;
			break;
		case 1:
			amount = Cin.GetInt(4, 1);
			if (!Cin.Success())return;
			break;
		case 2:
			price = Cin.GetDouble(8, 1);
			if (!Cin.Success())return;
			break;
		case 3:
			x = GetCurrentX();
			y = GetCurrentY();
			while (true)
			{
				purchase_price = Cin.GetDouble(8, 1);
				if (!Cin.Success())return;
				if (price < purchase_price)break;
				win.WriteLine(phrases[4], 2, 3);
				GotoXY(x, y);
				cout << "        ";
				GotoXY(x, y);
			}
			break;
		}
	}
	Add(name, amount, price, purchase_price);
	DrawSomething("Product was added!");
}
void AdminProducts::Add(const char* name, int amount, double purchase_price, double puchase_price)
{
	static int id = number_st ? file_data[file_data.GetCount() - 1].GetId() + 1 : 0;
	file_data << Product(id, name, amount, purchase_price, puchase_price);
	id++;
}
int AdminProducts::Sort(int amount, double purchase_price, double price, bool low_to_high)
{
	sorted.RemoveAll();
	if (amount && purchase_price && price)
	{
		for (int i = 0; i < file_data.GetCount(); i++)
		{
			if (amount >= file_data[i].GetAmount() &&
				purchase_price >= file_data[i].GetPurchasePrice() &&
				price == file_data[i].GetPrice())
			{
				if (low_to_high)sorted.AddTail(file_data[i]);
				else sorted.AddHead(file_data[i]);
			}
		}
	}
	else if (purchase_price && price)
	{
		for (int i = 0; i < file_data.GetCount(); i++)
		{
			if (purchase_price >= file_data[i].GetPurchasePrice() &&
				price >= file_data[i].GetPrice())
			{
				if (low_to_high)sorted.AddTail(file_data[i]);
				else sorted.AddHead(file_data[i]);
			}
		}
	}
	else if (amount && purchase_price)
	{
		for (int i = 0; i < file_data.GetCount(); i++)
		{
			if (purchase_price && purchase_price >= file_data[i].GetPurchasePrice() &&
				amount && amount >= file_data[i].GetAmount())
			{
				if (low_to_high)sorted.AddTail(file_data[i]);
				else sorted.AddHead(file_data[i]);
			}
		}
	}
	else if (amount && price)
	{
		for (int i = 0; i < file_data.GetCount(); i++)
		{
			if (amount >= file_data[i].GetAmount() &&
				price >= file_data[i].GetPrice())
			{
				if (low_to_high)sorted.AddTail(file_data[i]);
				else sorted.AddHead(file_data[i]);
			}
		}
	}
	else if (amount || purchase_price || price)
	{
		for (int i = 0; i < file_data.GetCount(); i++)
		{
			if (amount >= file_data[i].GetAmount() ||
				purchase_price >= file_data[i].GetPurchasePrice() ||
				price >= file_data[i].GetPrice())
			{
				if (low_to_high)sorted.AddTail(file_data[i]);
				else sorted.AddHead(file_data[i]);
			}
		}
	}
	else if (!amount && !purchase_price && !price)
	{
		for (int i = 0; i < file_data.GetCount(); i++)
		{
			if (low_to_high)sorted.AddTail(file_data[i]);
			else sorted.AddHead(file_data[i]);
		}
	}
	if (sorted.GetCount())return 2;
	else
	{
		DrawSomething("Page not found!");
		sorted = file_data;
		return true;
	}
}
int AdminProducts::Search(const char* val)
{
	sorted.RemoveAll();
	if (val)
	{
		for (int i = 0; i < file_data.GetCount(); i++)
		{
			if (CompareStr(val, file_data[i].GetName()) ||
				atoi(val) == file_data[i].GetAmount() ||
				atof(val) == file_data[i].GetPurchasePrice() ||
				atof(val) == file_data[i].GetPrice())
				sorted << file_data[i];
		}
	}
	if (sorted.GetCount())return 2;
	else
	{
		DrawSomething("Page not found!");
		sorted = file_data;
		return true;
	}
}
void AdminProducts::DrawElement(List<Product>& list, int row, int col, int x, int y)
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
int AdminProducts::DrawSorting()
{
	cls();
	char key = 0;
	int y = 0;
	int amount = 0;
	double purchase_price = 0, puchase_price = 0;
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
		enter_amount.WriteMessage();
		enter_price.WriteMessage();
		enter_pur_price.WriteMessage();
		sort.DrawMessage();
		High_to_low.DrawMessage();
		Low_to_high.DrawMessage();
		switch (y)
		{
		case 0:
			enter_amount.FillMessage();
			if (key == 13)amount = Cin.GetInt(5, 0, 0, 0, 1);
			break;
		case 1:
			enter_price.FillMessage();
			if (key == 13)purchase_price = Cin.GetDouble(5, 0, 0, 0, 1);
			break;
		case 2:
			enter_pur_price.FillMessage();
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
			if (key == 13)return Sort(amount, purchase_price, puchase_price, low_to_high);
			break;
		}
		Move(key, y, y, 1, 1);
		if (key == 27)break;
		if (y < 0)y = 5;
		if (y > 5)y = 0;
	}


	return Sort(amount, purchase_price, puchase_price, low_to_high);
}
int AdminProducts::DrawSearching()
{
	cls();
	char str[20];
	Window win(35, 3, LeftTop, 30, 5);
	Input Cin;
	win.DrawFrame();
	win.WriteLine("Enter: ", 2);
	strcpy(str, Cin.GetData(20));
	return Search(str);
}
bool AdminProducts::ChangeData(int index, int whom)
{
	if (index < 0)throw exception("Index can't be the negative!");
	Input Cin;
	switch (whom)
	{
	case 1:
		file_data[index].SetName(Cin.GetData(GetWidth() / cols, 3, GetX() + size_col * whom));
		break;
	case 2:
		file_data[index].SetAmount(Cin.GetInt(GetWidth() / cols, 1, GetX() + size_col * whom));
		break;
	case 3:
		file_data[index].SetPurchasePrice(Cin.GetDouble(GetWidth() / cols, 1, GetX() + size_col * whom));
		break;
	case 4:
		file_data[index].SetPrice(Cin.GetDouble(GetWidth() / cols, 1, GetX() + size_col * whom));
		break;
	}
	return Cin.Success();
}
