#pragma once
template <class type>
class List
{

public:
	class Node
	{
	public:
		Node(const type& _value, Node* _prev = 0, Node* _next = 0)
		{
			prev = _prev;
			next = _next;
			value = _value;
		}
		type value;
		Node* prev, * next;
	};
	List()
	{
		head = tail = 0;
		count = current = 0;
	}
	~List() { RemoveAll(); }
	void RemoveAll()
	{
		if (count)
		{
			Node* st = tail;
			Node* buff;
			while (st)
			{
				buff = st->prev;
				delete st;
				st = buff;
			}
			count = 0;
		}

	}
	void RemoveAt(int ind)
	{
		Node* st = (*this).GetCertain(ind);
		if (st)
		{
			if (st->prev) st->prev->next = st->next;
			if (st->next) st->next->prev = st->prev;
			if (st == head) head = st->next;
			if (st == tail) tail = st->prev;
			delete st;
		}
		count--;
	}
	Node* GetHead() { return head; }
	Node* GetTail() { return tail; }
	Node* GetCertain(int ind)
	{
		if (ind >= count)throw ind;
		Node* st = head;
		int pos = 0;
		while (st)
		{
			if (pos == ind)return st;
			st = st->next;
			pos++;
		}
		return 0;
	}
	int GetCount() { return count; }
	List& AddTail(const type& val)
	{
		Node* st = new Node(val, tail, 0);
		if (tail)
		{
			tail->next = st;
			tail = st;
		}
		else
		{
			head = tail = st;
		}
		count++;
		return *this;
	}
	List& AddHead(const type& val)
	{
		Node* st = new Node(val, 0, head);
		if (head)
		{
			head->prev = st;
			head = st;
		}
		else
		{
			head = tail = st;
		}
		count++;
		return *this;
	}
	List& Insert(int ind, const type& val)
	{
		Node* st = (*this).GetCertain(ind);
		Node* new_st = new Node(val, st, st->next);
		if (st != tail)st->next->prev = new_st;
		else tail = new_st;
		st->next = new_st;
		count++;
		return (*this);
	}
	List& operator<<(const type& val)
	{
		AddTail(val);
		return (*this);
	}

	type& operator[](int ind)
	{
		Node* st = (*this).GetCertain(ind);
		return st->value;
	}
	
	void operator=(List& l)
	{
		for (int i = 0; i < l.GetCount(); i++)
		{
			*this << l[i];
		}
	}
	List& operator>>(type& val)
	{
		if (current >= count)current = 0;
		val = (*this)[current];
		current++;
		return (*this);
	}
	
private:
	int count, current;
	Node* head, * tail;
};
