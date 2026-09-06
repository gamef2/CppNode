#include<iostream>
#include<cassert>
using namespace std;

class List
{
	typedef struct Link
	{
		int data;
		struct Link *next;
		Link(int d = 0, struct Link *n = NULL) :data(d), next(n)
		{
		}
	} LINK, *PLINK;
public:
	List() :size(0), head(NULL)
	{
		head = new LINK;
		tail = head;
		head->next = head;
	}
	~List()
	{
		PLINK tmp = head->next;
		while (tmp != head)
		{
			head->next = tmp->next;
			delete tmp;
			tmp = head->next;
		}
		delete head;
	}

	void Push(int data)
	{
		PLINK link = new LINK(data);
		assert(NULL != link);
		link->next = tail->next;
		tail->next = link;
		tail = link;
		++size;
	}
	bool Empty()
	{
		return size == 0;
	}
	bool Pop(int *data)
	{
		if (Empty())
			return false;
		PLINK tmp = head->next;
		*data = head->next->data;
		head->next = head->next->next;
		delete tmp;
		--size;
		return true;
	}
	int length()
	{
		int len = 0;
		PLINK p = head->next;
		while (p != head)
		{
			++len;
			p = p->next;
		}
		return len;
	}

	bool insert(int pos, int data)
	{
		PLINK p = head;
		int i = 0;
		if (pos<1 || pos>size + 1)
			return false;
		for (int j = 1; j <= pos - 1; j++)
			p = p->next;

		PLINK pNew = new LINK(data);
		assert(NULL != pNew);
		pNew->next = p->next;
		p->next = pNew;
		++size;
		return true;
	}
	bool del(int pos, int *data)
	{
		PLINK p = head;
		int i = 0;
		while (i < pos - 1 && p->next != head)
		{
			i++;
			p = p->next;
		}
		if (i > pos - 1 || p->next == head)
			return false;
		PLINK t = p->next;
		*data = p->next->data;
		p->next = p->next->next;
		delete t;
		--size;
		return true;
	}
	void traverse_list()
	{
		PLINK p = head->next;
		cout << head << "\t";
		while (p != head)
		{
			cout << p << ":" << p->data << "\t";
			p = p->next;
		}
		cout << endl;
	}
private:
	int size;
	PLINK head, tail;
};

int main()
{
	List list;
	int i = 0;
	for (i = 3; i <= 6; ++i)
		list.Push(i);
	list.traverse_list();
	list.insert(0, 99);
	list.insert(1, 98);
	list.insert(list.length(), 97);
	list.insert(list.length() + 1, 96);
	list.traverse_list();
	list.del(0, &i);
	list.del(1, &i);
	list.del(list.length(), &i);
	list.del(list.length() + 1, &i);
	while (!list.Empty())
	{
		list.Pop(&i);
		cout << i << " ";
	}
}
