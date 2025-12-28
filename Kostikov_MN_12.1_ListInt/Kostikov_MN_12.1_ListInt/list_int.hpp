#include "list_int.h"
#include "listitem.hpp"

ListItem<int>* List_int::find_item(int index) {
	ListItem<int>* current;
	if ((index >= 0) && (index < length)) {
		if (index < length / 2) {
			current = begin;
			for (int i = 0; i < index; i++)
				current = current->next;
		}
		else {
			current = end;
			for (int i = length - 1; i > index; i--)
				current = current->prev;
		}
		return current;
	}
	else
		return NULL;
}
List_int::List_int() {
	begin = NULL;
	end = NULL;
	length = 0;
	printf("Empty list was created\n");
}
List_int::List_int(List_int& m) {//Конструктор копирования
	begin = NULL;
	end = NULL;
	length = 0;

	for (int i = 0; i < m.length; i++)//копируем последовательно
		this->addToEnd(m[i]);
}
List_int::~List_int() {//деструктор
	while (length > 0) {
	    extractFromBegin();
	}
	this->show();
}
void List_int::addToEnd(int value) {
	ListItem<int>* newItem = new ListItem<int>(value, end, NULL);
	// Проверка на пустой список
	if (begin == NULL)
		// В пустом списке надо сформировать адрес начала
		begin = newItem;
	else
		// В непустом списке добавить элемент за последним
		end->next = newItem;
	// Смещаем конец на новый элемент
	end = newItem;
	length++;
	printf("A value %d is saved\n", value);
}
void List_int::addToBegin(int value) {
	ListItem<int>* newItem = new ListItem<int>(value, NULL, begin);
	// Проверка на пустой список
	if (end == NULL)
		// В пустом списке надо сформировать адрес конца
		end = newItem;
	else
		// В непустом списке добавить элемент перед первым
		begin->prev = newItem;
	// Смещаем начало на новый элемент
	begin = newItem;
	length++;
	printf("A value %d is saved\n", value);
}
void List_int::extractFromBegin() {
	if (begin == NULL)
		printf("The list is empty\n");
	else {
		ListItem<int>* deleteItem = begin;
		int value = begin->value;
		if (begin == end) {
			// Если в списке был всего 1 элемент
			begin = NULL;
			end = NULL;
		}
		else {
			begin = begin->next;
			begin->prev = NULL;
		}
		delete deleteItem;
		length--;
		printf("A value %d is extracted\n", value);
	}
}
void List_int::extractFromEnd() {//удаляем элемент из конца списка
	if (end == NULL)
		printf("The list is empty\n");
	else {
		ListItem<int>* deleteItem = end;
		int value = end->value;
		if (begin == end) {
			// Если в списке был всего 1 элемент
			begin = NULL;
			end = NULL;
		}
		else {
			end = end->prev;
			end->next = NULL;
		}
		delete deleteItem;
		length--;
		printf("A value %d is extracted\n", value);
	}
}
void List_int::insert(int value, int index) {
	ListItem<int>* newItem, * current = find_item(index);
	if (current == NULL)printf("The index %d is incorrect\n", index);
	else {
		newItem = new ListItem<int>(value, current, current->next);
		current->next = newItem;
		if (current == end)
			end = newItem;
		else
			current->next->prev = newItem;
		length++;
		printf("A value %d was inserted after item with value %d\n", value, current->value);
	}
}
void List_int::remove(int index) {
	ListItem<int>* deleteItem = find_item(index);
	if (deleteItem == NULL)
		printf("The index %d is incorrect\n", index);
	else {
		int value = deleteItem->value;
		if (begin == end) {
			// Если в списке был всего 1 элемент
			begin = NULL;
			end = NULL;
		}
		else {
			if (deleteItem == begin) {
				begin = begin->next;
				begin->prev = NULL;
			}
			else
				deleteItem->prev->next = deleteItem->next;
			if (deleteItem == end) {
				end = end->prev;
				end->next = NULL;
			}
			else
				deleteItem->next->prev = deleteItem->prev;
		}
		delete deleteItem;
		length--;
		printf("Item %d with value %d was removed\n", index, value);
	}
}
void List_int::show() {
	ListItem<int>* current = begin;
	int i = 1;
	printf("\nList contains %d items\n", length);
	while (current != NULL) {
		printf("Item %d: %d\n", i - 1, current->value);
		current = current->next;
		i++;
	}
	printf("\n");
}
void List_int::showReverse() {//выводим в обратном порядке
	ListItem<int>* current = end;
	int i = length;
	printf("\nList contains %d items\n", length);
	while (current != NULL) {
		printf("Item %d: %d\n", i - 1, current->value);
		current = current->prev;
		i--;
	}
	printf("\n");
}
int& List_int::operator[](int index) {
	ListItem<int>* found = find_item(index);
	if (found == NULL)
		return *(new int(0));
	else
		return found->value;
}

List_int& List_int::operator+=(int newVal) {
	addToEnd(newVal);
	return *this;
}

List_int& List_int::operator=(List_int& other) {//оператор присваивания
	while (length > 0) {//очищаем если что то было
		extractFromBegin();
	}

	for (int i = 0; i < other.length; i++)//копируем последовательно
		this->addToEnd(other[i]);
	return *this;
}