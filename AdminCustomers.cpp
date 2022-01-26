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
	if (!product.GetCount())throw exception((string(product.filename) + " is empty!").c_str());
	cls();
	win.DrawFrame("Enter the name: ", 2, 1);
	strcpy(name, Cin.GetStr(15, 3));
	if (!Cin.Success())return;
	if ((id = ChooseProduct(product)) == -1)return;

	cls();
	win.DrawFrame("Enter the amount: ", 2, 1);
	amount = Cin.GetInt(5);
	index = product.SeekElement(product.GetFileData(), id);

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

	DrawSomething("Product was bought!");
}
int AdminCustomers::ChooseProduct(AdminProducts& admin_product)
{
	int index,
		page = 0,
		number_pages = ceil(admin_product.GetCount() / (limit * 1.0));
	while (true)
	{
		cls();
		List<Product> l;
		for (int i = page * limit, j = 0; i < admin_product.GetCount(); i++, j++)
		{
			if (j >= limit)break;
			l << admin_product[i];
		}
		admin_product.SetWinParam(width, l.GetCount() * 2 + 1, LeftTop, 5, 2);
		admin_product.SetRows(l.GetCount());
		index = ShowProducts(admin_product, l, page);
		if (index >= 0)return l[index].GetId();
		if (index == -1)return index;
		if (number_pages <= page)page = 0;
		if (0 > page)page = number_pages - 1;
	}
	return -1;
}
int AdminCustomers::ShowProducts(AdminProducts& admin_product, List<Product>& list, int& page)
{
	int prod_size_col = admin_product.GetSizeCol(),
		prod_size_row = admin_product.GetSizeRow(),
		prod_cols = admin_product.GetCols(),
		prod_rows = admin_product.GetRows();
	if (!prod_size_col)throw exception("prod_size_col can't be zero!");
	if (!prod_size_row)throw exception("prod_size_row can't be zero!");
	char key;
	int x = 0, y = 0,
		row, col;
	admin_product.back->SetIndents(19, 2);
	admin_product.SetPaginationParam(page);
	while (true)
	{
		admin_product.DrawData(list);
		admin_product.back->DrawMessage();
		admin_product.DrawPagination();
		row = y / prod_size_row;
		col = x / prod_size_col;
		for (int i = 0; i < prod_cols; i++)
		{
			x = prod_size_col * i;
			admin_product.DrawActiveCell(list, y / prod_size_row, x / prod_size_col, x, y);
		}
		Move(key, x, y, prod_size_col, prod_size_row);
		if (key == 27)return -1;
		if (key == 13)return row;
		if (x >= prod_size_col * prod_cols)
		{
			admin_product.DrawData(list);
			admin_product.back->DrawActiveMsg();
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
			admin_product.DrawData(list);
			if (admin_product.DoPagination(page))return -2;
		}
		admin_product.CheckXY(x, y);
	}
}
void AdminCustomers::Add(const char* name, const char* prod_name, int amount, double price)
{
	static int id = number_st ? file_data[file_data.GetCount() - 1].GetId() + 1: 0;
	file_data << Customer(id, name, prod_name, amount, price);
	id++;
}
int AdminCustomers::Sort(int amount, double price, bool low_to_high)
{
	sorted.RemoveAll();
	if (amount && price)
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
	else if (amount || price)
	{
		for (int i = 0; i < file_data.GetCount(); i++)
		{
			if (amount >= file_data[i].GetAmount() ||
				price >= file_data[i].GetPrice())
			{
				if (low_to_high)sorted.AddTail(file_data[i]);
				else sorted.AddHead(file_data[i]);
			}
		}
	}
	else if (!amount && !price)
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
int AdminCustomers::Search(const char* val)
{
	sorted.RemoveAll();
	if (val)
	{
		for (int i = 0; i < file_data.GetCount(); i++)
		{
			if (CompareStr(val, file_data[i].GetName()) ||
				atoi(val) == file_data[i].GetAmount() ||
				atof(val) == file_data[i].GetPrice() ||
				CompareStr(val, file_data[i].GetProdName()))
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
	win.DrawFrame();
	win.WriteLine("Enter: ", 2);
	strcpy(str, Cin.GetData(20));
	return Search(str);
}
void AdminCustomers::DrawElement(List<Customer>& list, int row, int col, int x, int y)
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
		WriteLine(list[row].GetProdName(), x, y);
		break;
	case 3:
		WriteLine(list[row].GetAmount(), x, y);
		break;
	case 4:
		WriteLine(list[row].GetPrice(), x, y);
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
		file_data[index].SetName(Cin.GetData(GetWidth() / cols, 3, GetX() + size_col * whom));
		break;
	case 2:
		file_data[index].SetProdName(Cin.GetData(GetWidth() / cols, 3, GetX() + size_col * whom));
		break;
	case 3:
		file_data[index].SetAmount(Cin.GetInt(GetWidth() / cols, 1, GetX() + size_col * whom));
		break;
	case 4:
		file_data[index].SetPrice(Cin.GetDouble(GetWidth() / cols, 1, GetX() + size_col * whom));
		break;
	}
	return Cin.Success();
}
void AdminCustomers::ShowIncome(const char* products)
{
	AdminProducts admin_prod(products);
	double costs = 0,
		profit = 0;
	char result[] = "Income is ";
	char buff[100];
	for (int i = 0; i < this->GetCount(); i++)
	{
		for (int j = 0; j < admin_prod.GetCount(); j++)
		{
			if (CompareStr(((*this)[i]).GetProdName(), admin_prod[j].GetName()))
			{
				
				costs += ((*this)[i]).GetAmount() * admin_prod[j].GetPurchasePrice();
				profit += ((*this)[i]).GetAmount() * admin_prod[j].GetPrice();
				break;
			}
		}
	}
	sprintf(buff, "%f", profit - costs);
	strcat(result, buff);
	DrawSomething(result);
}