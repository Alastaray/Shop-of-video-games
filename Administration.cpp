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
			if (key == 13)amount = Cin.GetInt(5,0,0,0,1);
			break;
		case 1:
			enter_price.FillMessage();
			if (key == 13)price = Cin.GetDouble(5, 0, 0, 0, 1);
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
void AdminProducts::ChangeData(int index, int whom)
{
	if (index < 0)throw exception("Id can't be the negative!");
	Input Cin;
	switch (whom)
	{
	case 1:
		list[index].SetName(Cin.Get(15, 3, size_col * whom + 1));
		break;
	case 2:
		list[index].SetAmount(Cin.GetInt(5, 0, size_col * whom + 1));
		break;
	case 3:
		list[index].SetPrice(Cin.GetDouble(5, 0, size_col * whom + 1));
		break;
	case 4:
		list[index].SetPurchasePrice(Cin.GetDouble(5, 0, size_col * whom + 1));
		break;
	}
}




void AdminCustomers::DrawAdding()
{
	cls();
	int id,
		index,
		amount;
	char name[16];
	Window win(35, 5, CenterTop, 0, 7);
	Input Cin;
	win.DrawBox("Enter the name: ", 0, 0, 2, 2);
	strcpy(name, Cin.GetStr(15, 3));
	AdminProducts product("products.txt");
	if((id = ChooseProduct(product))==-1)throw exception("Incorrect returning from the func ChooseProduct!");
	cls();
	win.DrawBox("Enter the amount: ", 0, 0, 2, 2);
	amount = Cin.GetInt(5);
	index = product.SeekElement(product.GetList(), id);
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
int AdminCustomers::ChooseProduct(AdminProducts& product)
{
	int index,
		page=0,
		number_pages = ceil(product.GetCount() / (limit * 1.0));
	while (true)
	{
		cls();
		List<Product> l;
		for (int i = page * limit, j = 0; i < product.GetCount(); i++, j++)
		{
			if (j >= limit)break;
			l << product.GetList()[i];
		}
		product.SetWinParam(85, l.GetCount() * 2 + 1, LeftTop, 0, 2);
		product.SetCols(5);
		product.SetRows(l.GetCount());
		index = ShowProducts(product, l, page);
		if (index >= 0)return l[index].GetId();
		if (index == -1)return index;
		if (number_pages <= page)page = 0;
		if (0 > page)page = number_pages - 1;
	}
	return -1;
}
int AdminCustomers::ShowProducts(AdminProducts& product, List<Product>& _list, int& page)
{
	int prod_size_col = product.GetSizeCol(),
		prod_size_row = product.GetSizeRow(),
		prod_cols = product.GetCols(),
		prod_rows = product.GetRows();
	if (!prod_size_col || !prod_size_row)return -1;
	char key;
	int x = 0, y = 0,
		row, col;
	Message back("Back", 10, 3, RightTop, 8, 2);
	Message pag_left("<<", 5, 3, LeftTop, product.GetWidth() / 2 - 10, prod_size_row * prod_rows + 3);
	Message pag_right(">>", 5, 3, LeftTop, product.GetWidth() / 2 + 3, prod_size_row * prod_rows + 3);
	while (true)
	{
		product.DrawData(_list);
		back.DrawMessage();	
		pag_left.DrawMessage();
		pag_right.DrawMessage();
		row = y / prod_size_row;
		col = x / prod_size_col;
		for (int i = 0; i < prod_cols; i++)
		{
			x = prod_size_col * i;
			product.DrawActiveCell(_list, y / prod_size_row, x / prod_size_col, x, y);
		}
		Move(key, x, y, prod_size_col, prod_size_row);
		if (key == 27)return -1;
		if (key == 13)return row;
		if (x >= prod_size_col * prod_cols)
		{
			product.DrawData(_list);
			back.DrawActiveMsg();
			Move(key, x, y, prod_size_col, prod_size_row);
			if (key == 13)return -1;
			if (key == 72 || key == 'w' || key == 'W')
				y += prod_size_row;
			if (key == 80 || key == 's' || key == 'S')
				y -= prod_size_row;
		}
		if (y >= prod_size_row * prod_rows)
		{
			y -= prod_size_row;
			product.DrawData(_list);
			if(product.DrawPagination(pag_left, pag_right,page))return -2;
		}
		product.CheckXY(x, y);
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
		enter_amount.WriteMessage();
		enter_price.WriteMessage();
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
void AdminCustomers::ChangeData(int index, int whom)
{
	if (index < 0)throw exception("Id can't be the negative!");
	Input Cin;
	switch (whom)
	{
	case 1:
		list[index].SetName(Cin.Get(15, 3, size_col * whom + 1));
		break;
	case 2:
		list[index].SetProdName(Cin.Get(15, 3, size_col * whom + 1));
		break;
	case 3:
		list[index].SetAmount(Cin.GetInt(5, 0, size_col * whom + 1));
		break;
	case 4:
		list[index].SetPrice(Cin.GetDouble(5, 0, size_col * whom + 1));
		break;
	}
}
