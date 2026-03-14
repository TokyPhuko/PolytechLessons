#include <stdlib.h>
#include <iostream>
#include "Classes.hpp"


template<typename T>
void print(IEnumerable<T>& collection) {
	IIterator<T>& it = collection.iterator();
	std::cout << "Print: ";
	while (it.hasNext())
		std::cout << it.next() << " ";
	std::cout << std::endl;
}

template<typename T>
void push_stack(IStack<T>& stack) {
	for (int i = 0; i < 5; i++) {
		stack.push(i);
		std::cout << "Push: " << i << "; Top: " << *stack.top() << std::endl;
	}
}

template<typename T>
void pop_stack(IStack<T>& stack) {
	for (int i = 0; i < 5; i++) {
		stack.pop();
		std::cout << "Pop;";
		if (stack.top() != nullptr)
			std::cout << " Top: " << *stack.top();
		std::cout << std::endl;
	}
}

int main() {
	/*int a = 0;
	int* p_a = &a;
	int** pp_a = &p_a;
	std::cout << p_a << " " << *pp_a;*/
	std::cout << "--- MyArray ---" << std::endl;
	MyArray<int> a;
	a.generate(10, 5);
	//IIterator<int>& it = a.iterator();
	//a.generate(3, 2);
	//it.next();
	//it.next();
	//it.next();
	//std::cout << it.next() << std::endl;
	print(a);

	std::cout << "--- MyStack ---" << std::endl;
	MyStack<int> s;
	push_stack(s);
	print(s);
	pop_stack(s);
	print(s);

	push_stack(s);
	IIterator<int>& it = s.iterator();
	std::cout << "Print: ";
	for (int i = 0; i < 3; i++) {
		if (it.hasNext()) 
			std::cout << it.next() << " ";
		
		if (i == 1)
			s.push(i);
	}

	MyQueue<int> q;
	for (int i = 0; i < 5; i++) {
		q.push(i);
	}
	std::cout << "Print and pop: ";
	for (int i = 0; i < 5; i++) {
		std::cout << *q.front() << " ";
		q.pop();
	}
	std::cout << std::endl;

	MyList<int> l;
	for (int i = 0; i < 10; i++) {
		l.addToEnd(i);
	}

	for (int i = 1; i < 11; i++) {
		l.printItem(i);
	}
	std::cout << std::endl;
	l.insert(7, 1000);

	for (int i = 1; i < 12; i++) {
		l.printItem(i);
	}
	std::cout << std::endl;
	l.remove(7);

	for (int i = 1; i < 11; i++) {
		l.printItem(i);
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}