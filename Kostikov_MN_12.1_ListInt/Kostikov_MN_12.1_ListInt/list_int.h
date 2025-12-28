#include <stdio.h>
#include "listitem.h"
#ifndef LIST_INT_H
#define LIST_INT_H
struct List_int {
	// Поля
	ListItem<int>* begin, * end;
	int length;
	// Методы
	ListItem<int>* find_item(int index);
	// Конструктор пустого списка
	List_int();
	List_int(List_int&);//конструтор копирования
	~List_int();
	// Добавление/удаление элементов
	void addToEnd(int value);
	void addToBegin(int value);//добавление элемента в начало
	void extractFromBegin();
	void extractFromEnd();//удаление элементв из конца
	// Изменение списка по индексу
	void insert(int value, int index);
	void remove(int index);
	// Вывод на экран
	void show();
	void showReverse();
	// Операторы
	int& operator[](int i);
	List_int& operator+=(int newVal);
	List_int& operator=(List_int& other);
};
#endif LIST_INT_H