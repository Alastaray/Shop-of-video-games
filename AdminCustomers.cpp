#include "AdminCustomers.h"





void AdminCustomers::DrawAdding()
{
	int id,
		index,
		amount;
	char name[16];
	Window win(35, 5, CenterTop, 0, 7);
	Input Cin;
	AdminProducts product("products.txt");

	cls();
	win.DrawFrame("Enter the name: ", 2, 1);
	strcpy(name, Cin.GetStr(15, 3));
	if (!Cin.Success())return;
	if ((id = ChooseProduct(product)) == -1)return;

	cls();
	win.DrawFrame("Enter the amount: ", 2, 1);
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

	Message::DrawMessage("Product was bought!");
}
int AdminCustomers::ChooseProduct(AdminProducts& product)
{
	int index,
		page = 0,
		number_pages = ceil(product.GetCount() / (limit * 1.0));
	while (true)
	{
		cls();
		List<Product> l;
		for (int i = page * limit, j = 0; i < product.GetCount(); i++, j++)
		{
			if (j >= limit)break;
			l << product[i];
		}
		product.SetWinParam(width, l.GetCount() * 2 + 1, LeftTop, 5, 2);
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
	if (!prod_size_col)throw exception("prod_size_col can't be zero!");
	if (!prod_size_row)throw exception("prod_size_row can't be zero!");
	if (!prod_size_col || !prod_size_row)return -1;
	char key;
	int x = 0, y = 0,
		row, col;
	Message back("Back", 10, 3, RightTop, 19, 2);
	Message pag_left("<<", 5, 3, LeftTop, product.GetWidth() / 2 - 3, prod_size_row * prod_rows + 3);
	Message current_page(IntToChar(page), 5, 3, LeftTop, product.GetWidth() / 2 + 4, prod_size_row * prod_rows + 3);
	Message pag_right(">>", 5, 3, LeftTop, product.GetWidth() / 2 + 11, prod_size_row * prod_rows + 3);

	while (true)
	{
		product.DrawData(_list);
		back.DrawMsgWithFrame();
		pag_left.DrawMsgWithFrame();
		current_page.DrawMsgWithFrame(1);
		pag_right.DrawMsgWithFrame();
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
			if (product.DrawPagination(pag_left, pag_right, page))return -2;
		}
		product.CheckXY(x, y);
	}
}
void AdminCustomers::Add(const char* name, const char* prod_name, int amount, double price)
{
	static int id = number_st? list[list.GetCount() - 1].GetId() + 1: 0;
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
		Message::DrawMessage("Page not found!");
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
		Message::DrawMessage("Page not found!");
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
		enter_amount.DrawMessage();
		enter_price.DrawMessage();
		sort.DrawMsgWithFrame();
		High_to_low.DrawMsgWithFrame();
		Low_to_high.DrawMsgWithFrame();
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
	win.DrawFrame();
	win.WriteLine("Enter: ", 2);
	strcpy(str, Cin.GetData(20));
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
bool AdminCustomers::ChangeData(int index, int whom)
{
	if (index < 0)throw exception("Index can't be the negative!");
	Input Cin;
	switch (whom)
	{
	case 1:
		list[index].SetName(Cin.GetData(GetWidth() / cols, 3, GetX() + size_col * whom));
		break;
	case 2:
		list[index].SetProdName(Cin.GetData(GetWidth() / cols, 3, GetX() + size_col * whom));
		break;
	case 3:
		list[index].SetAmount(Cin.GetInt(GetWidth() / cols, 1, GetX() + size_col * whom));
		break;
	case 4:
		list[index].SetPrice(Cin.GetDouble(GetWidth() / cols, 1, GetX() + size_col * whom));
		break;
	}
	return Cin.Success();
}


int CreateReport(AdminProducts& admin_prod, AdminCustomers& admin_cust)
{
	double costs = 0,
		profit = 0;
	for (int i = 0; i < admin_cust.GetCount(); i++)
	{
		for (int j = 0; j < admin_prod.GetCount(); j++)
		{
			if (CompareStr(admin_cust[i].GetProdName(), admin_prod[j].GetName()))
			{
				costs += admin_cust[i].GetAmount() * admin_prod[j].GetPurchasePrice();
				profit += admin_cust[i].GetAmount() * admin_prod[j].GetPrice();
				break;
			}
		}
	}
	return profit - costs;
}