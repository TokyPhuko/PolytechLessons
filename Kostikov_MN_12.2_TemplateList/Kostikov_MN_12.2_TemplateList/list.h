#include <stdio.h>
#include "listitem.h"
#ifndef LIST_H
#define LIST_H
template<typename T>
struct List {
	// Поля
	ListItem<T>* begin, * end;
	int length;
	// Методы
	ListItem<T>* find_item(int index);
	// Конструктор пустого списка
	List();
	List<T>(List<T>&);//конструтор копирования
	~List<T>();
	// Добавление/удаление элементов
	void addToEnd(T value);
	void addToBegin(T value);//добавление элемента в начало
	void extractFromBegin();
	void extractFromEnd();//удаление элементв из конца
	// Изменение списка по индексу
	void insert(T value, int index);
	void remove(int index);
	void show();
	void showReverse();
	// Операторы
	T& operator[](int i);
	List<T>& operator+=(T newVal);
	List<T>& operator>>(int n);
	List<T>& operator<<(int n);
	List<T>& operator=(List<T>& other);
	List<T>& operator+(List<T>& other);
	List<T>& operator-(List<T>& other);
};
#endif LIST_H