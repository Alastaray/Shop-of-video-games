#pragma once
#include <iostream>
#include "Other.h"
using namespace std;


class ListException : public exception
{
public:
	ListException(const char* msg, int _value, int _count) :exception(msg)
	{
		value = _value;
		count = _count;
	}
	int GetValue() { return value; }
	int GetCount() { return count; }
private:
	int value, count;
};


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

	List();
	List(const List<type>& list);
	~List() { RemoveAll(); }
	void RemoveAll();
	void RemoveAt(int ind);
	Node* GetHead() { return head; }
	Node* GetTail() { return tail; }
	int GetCount()const { return count; }
	Node* GetCertain(int ind)const
	{
		if (ind >= count)throw ListException("Index can't be bigger then the count", ind, count);
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
	List& AddTail(const type& val);
	List& AddHead(const type& val);
	List& Insert(int ind, const type& val);
	List& operator<<(const type& val);
	List& operator>>(type& val);
	type& operator[](int ind)const;
	void operator=(const List& list);

private:
	int count, current;
	Node* head, * tail;
};

template <class type>
List<type>::List()
{
	head = tail = 0;
	count = current = 0;
}

template <class type>
List<type>::List(const List<type>& list)
{
	head = tail = 0;
	count = current = 0;
	*this = list;
}

template <class type>
void List<type>::RemoveAll()
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
		head = tail = 0;
		count = 0;
	}

}

template <class type>
void List<type>::RemoveAt(int ind)
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

template <class type>
List<type>& List<type>::AddTail(const type& val)
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

template <class type>
List<type>& List<type>::AddHead(const type& val)
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

template <class type>
List<type>& List<type>::Insert(int ind, const type& val)
{
	Node* st = (*this).GetCertain(ind);
	Node* new_st = new Node(val, st, st->next);
	if (st != tail)st->next->prev = new_st;
	else tail = new_st;
	st->next = new_st;
	count++;
	return (*this);
}

template <class type>
List<type>& List<type>::operator<<(const type& val)
{
	AddTail(val);
	return (*this);
}

template <class type>
List<type>& List<type>::operator>>(type& val)
{
	if (current >= count)current = 0;
	val = (*this)[current];
	current++;
	return (*this);
}

template <class type>
type& List<type>::operator[](int ind)const
{
	Node* st = (*this).GetCertain(ind);
	return st->value;
}

template <class type>
void List<type>::operator=(const List& list)
{
	for (int i = 0; i < list.GetCount(); i++)
	{
		*this << list[i];
	}
}