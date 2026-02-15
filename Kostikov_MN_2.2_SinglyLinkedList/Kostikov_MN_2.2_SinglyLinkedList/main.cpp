//6. Написать отдельную программу с кольцевым односвязным списком аналогичной
//функциональности.

#include<iostream>
#include"SinglyListItem.hpp"
#include"SinglyLinkedList.hpp"

int main() {
	SinglyListItem<int>* a = new SinglyListItem<int>;
	std::cout << a->GetData() << ' ' << a->GetNext() << std::endl;
	SinglyListItem<int>* b = new SinglyListItem<int>;
	a->ChangeNext(b);
	std::cout << a->GetData() << ' ' << a->GetNext() << std::endl;

	SinglyLinkedList<int> z(3);
	z.Add(3, 0);
	z.Delete(1);
	int k = z.FindItem(0);
	z.Print();
	std::cout << k << std::endl << std::endl;

	SinglyLinkedList<int> h(z);
	h.Delete(2);
	z = h;
	z.Print();

	z << 3;
	z >> 3;
	z.Print();
	z.ReSize(4);
	z.Print();

	h + z;
	h.Print();

	delete a;
	delete b;
}