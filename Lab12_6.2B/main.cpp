#include <iostream>
using namespace std;

struct Elem
{
	Elem* link;
	int info;
};

void enqueue(Elem*& first, Elem*& last, int info)
{
	Elem* tmp = new Elem;
	tmp->info = info;
	tmp->link = nullptr;
	if (last != nullptr)
		last->link = tmp;
	last = tmp;
	if (first == nullptr)
		first = tmp;
}

int dequeue(Elem*& first, Elem*& last)
{
	Elem* tmp = first->link;
	int info = first->info;
	delete first;
	first = tmp;
	if (first == nullptr)
		last = nullptr;
	return info;
}

void copy_queue(const Elem* first, Elem*& new_first, Elem*& new_last)
{
	if (first != nullptr)
	{
		enqueue(new_first, new_last, first->info);
		copy_queue(first->link, new_first, new_last);
	}
}

void remove(Elem*& first, Elem*& last, int &i, int pos)
{
	if (pos == 0) {
		dequeue(first, last);
		return;
	}

	if (first != nullptr)
	{
		if (i == pos - 1)
		{
			Elem* next_link = first->link->link;
			delete first->link;
			first->link = first;
		}

		i++;
		remove(first, last, i, pos);
	}
}

int count(const Elem* L)
{
	if (L != nullptr)
		return 1 + count(L->link);
	else
		return 0;
}

void print(const Elem* first)
{
	if (first == nullptr)
		cout << endl;
	else
	{
		cout << first->info << " ";
		print(first->link);
	}
}


void deletefl(Elem*& first, Elem*& last, int k)
{
	if (k == -1)
		return;
	else {
		dequeue(first, last);
		deletefl(first, last, k - 1);
	}
}

void delete_memory(Elem*& first1, Elem*&last1, Elem*&first2, Elem*&last2)
{
	int k = count(first1);
	deletefl(first1, last1, k - 1);
	k = count(first2);
	deletefl(first2, last2, k - 1);
}

void check1(Elem*nav1, Elem*&nav2, Elem*&first, Elem*&last, bool &is_there, int &i)
{
	if (nav2 != nullptr)
	{
		if (nav1->info == nav2->info)
		{
			is_there = true;
			int i1 = 0;
			remove(first, last, i1, i);
			nav2 = first;
			return;
		}
		i++;
		check1(nav1, nav2->link, first, last, is_there, i);
	}
}

void check2(Elem*& nav1, Elem*& nav2, Elem*& first1, Elem*& last1, Elem*& first2, Elem*& last2, bool &is_there)
{
	if (nav1 != nullptr)
	{

		int i = 0;
		check1(nav1, nav2, first2, last2, is_there, i);
		if (!is_there)
		{
			delete_memory(first1, last1, first2, last2);
			return;
		}
		check2(nav1->link, nav2, first1, last1, first2, last2, is_there);
	}
}

bool check(const Elem* l1, const Elem* l2)
{
	Elem* first1 = nullptr, * last1 = nullptr;
	Elem* first2 = nullptr, * last2 = nullptr;
	copy_queue(l1, first1, last1);
	copy_queue(l1, first2, last2);

	Elem* nav1 = first1;
	Elem* nav2 = first2;

	if (count(l2) < count(l1))
		return false;

	bool is_there = false;
	check2(nav1, nav2, first1, last1, first2, last2, is_there);

	delete_memory(first1, last1, first2, last2);
	return is_there;
}

int main()
{
	Elem* first = nullptr, * last = nullptr;
	Elem* first1 = nullptr, * last1 = nullptr;

	enqueue(first, last, 0);
	enqueue(first, last, 4);
	enqueue(first, last, 4);
	enqueue(first, last, 5);

	for (size_t i = 0; i < 10; i++)
		enqueue(first1, last1, i);

	print(first);
	print(first1);
	

	cout << check(first, first1) << endl;

	int k = count(first);
	cout << k << endl;
	for (size_t i = 0; i < k; i++)
		dequeue(first, last);
	k = count(first1);
	for (size_t i = 0; i < k; i++)
		dequeue(first1, last1);

	return 0;
}