//1. Выделить реализацию класса ListItem в отдельный файл;
//2. Добавить конструктор копирования(копирует хранящиеся значения из одного
//	списка в другой) и оператор присваивания(операнд справа – другой список);
//3. Добавить деструктор, который удаляет все элементы списка;
//4. Добавить методы для добавления элемента в начало и изъятия элемента из конца;
//5. Добавить метод вывода списка в обратном порядке;


#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "list_int.hpp"
int main() {
	List_int* a = new List_int();
	a->show();
	for (int i = 0; i < 10; i++)
		a->addToEnd(i);
	a->show();
	List_int* b = new List_int(*a);//проверка кончтруктора копирования
	printf("\nTest copy constructor");
	b->show();
	List_int* c = new List_int();//проверка оператора присваивания
	*c = *b;
	printf("\nTest = operator");
	c->show();
	printf("\nTest addToBegin 100 to c ");
	c->addToBegin(100);
	c->show();
	printf("\nTest extractFromEnd for c ");
	c->extractFromEnd();
	c->show();
	printf("\nTest reverse show for c ");
	c->showReverse();
	for (int i = 0; i < 15; i++)
		a->extractFromBegin();
	a->show();
	for (int i = 0; i < 10; i++)
		a->addToEnd(i);
	printf("Test operators:\n(*a) += 10\n");
	(*a) += 10;
	int k = rand() % a->length;
	printf("(*a)[%d] = %d\n", k, a->operator[](k));
	a->insert(-1, 1);
	a->insert(-5, 15);
	a->remove(4);
	a->remove(-7);
	a->show();
	delete a;
	delete b;
	delete c;
	system("pause");
	return 0;
}