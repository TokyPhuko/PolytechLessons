#include "list.h"
#include "listitem.hpp"
template<typename T>
ListItem<T>* List<T>::find_item(int index) {
	ListItem<T>* current;
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
template<typename T>
List<T>::List() {
	begin = NULL;
	end = NULL;
	length = 0;
	printf("Empty list was created\n");
}
template<typename T>
List<T>::List(List& m) {//Конструктор копирования
	begin = NULL;
	end = NULL;
	length = 0;

	for (int i = 0; i < m.length; i++)//копируем последовательно
		this->addToEnd(m[i]);
}
template<typename T>
List<T>::~List() {//деструктор
	while (length > 0) {
		extractFromBegin();
	}
	this->show();
}
template<typename T>
void List<T>::addToEnd(T value) {
	ListItem<T>* newItem = new ListItem<T>(value, end, NULL);
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
	printf("A value %f is saved\n", value);
}
template<typename T>
void List<T>::addToBegin(T value) {
	ListItem<T>* newItem = new ListItem<T>(value, NULL, begin);
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
template<typename T>
void List<T>::extractFromBegin() {
	if (begin == NULL)
		printf("The list is empty\n");
	else {
		ListItem<T>* deleteItem = begin;
		T value = begin->value;
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
		printf("A value %f is extracted\n", value);
	}
}
template<typename T>
void List<T>::extractFromEnd() {//удаляем элемент из конца списка
	if (end == NULL)
		printf("The list is empty\n");
	else {
		ListItem<T>* deleteItem = end;
		T value = end->value;
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
		printf("A value %f is extracted\n", value);
	}
}
template<typename T>
void List<T>::insert(T value, int index) {
	ListItem<T>* newItem, * current = find_item(index);
	if (current == NULL)printf("The index %d is incorrect\n", index);
	else {
		newItem = new ListItem<T>(value, current, current->next);
		current->next = newItem;
		if (current == end)
			end = newItem;
		else
			current->next->prev = newItem;
		length++;
		printf("A value %d was inserted after item with value %d\n", value, current->value);
	}
}
template<typename T>
void List<T>::remove(int index) {
	ListItem<T>* deleteItem = find_item(index);
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
template<typename T>
void List<T>::show() {
	ListItem<T>* current = begin;
	int i = 1;
	printf("\nList contains %d items\n", length);
	while (current != NULL) {
		printf("Item %d: %f\n", i - 1, current->value);
		current = current->next;
		i++;
	}
	printf("\n");
}
template<typename T>
void List<T>::showReverse() {//выводим в обратном порядке
	ListItem<T>* current = end;
	int i = length;
	printf("\nList contains %d items\n", length);
	while (current != NULL) {
		printf("Item %d: %d\n", i - 1, current->value);
		current = current->prev;
		i--;
	}
	printf("\n");
}
template<typename T>
T& List<T>::operator[](int index) {
	ListItem<T>* found = find_item(index);
	if (found == NULL)
		return *(new T(0));
	else
		return found->value;
}
template<typename T>
List<T>& List<T>::operator+=(T Val) {
	addToEnd(Val);
	return *this;
}
template<typename T>
List<T>& List<T>::operator=(List& other) {//оператор присваивания
	if (&other == this) {
		return *this;
	}
	while (length > 0) {//очищаем если что то было
		extractFromBegin();
	}

	for (int i = 0; i < other.length; i++)//копируем последовательно
		this->addToEnd(other[i]);
	return *this;
}
template<typename T>
List<T>& List<T>::operator+(List<T>& other) {//сложение
	for (int i = 0; i < other.length; i++)
		addToEnd(other[i]);
	return *this;
}
template<typename T>
List<T>& List<T>::operator-(List<T>& other) {//вычитание
	if (length < other.length) {
		printf("error");
		return *this;
	}
	ListItem<T>* current = begin;
	int i = 0;
	while (current != NULL) {
		current->value -= other[i];
		current = current->next;
		i++;
	}
	return *this;
}
template<typename T>
List<T>& List<T>::operator>>(int n) {
	n = n % length;//рассчитаем реальный коэффицент сдвига, он должен быть < length

	if ((length == 1) || n == 0)
		return *this;

	ListItem<T>* new_begin = find_item(length-n);//сдвигаемся на n от конца (новое начало)
	ListItem<T>* new_end = find_item(length - n - 1);//новый конец

	begin->prev = end;//соединяем текущие начало и конец
	end->next = begin;
	new_begin->prev = NULL;//создаем новое начал и новый конец
	new_end->next = NULL;

	begin = new_begin;
	end = new_end;

	return *this;
}
template<typename T>
List<T>& List<T>::operator<<(int n) {
	n = n % length;//рассчитаем реальный коэффицент сдвига, он должен быть < length

	if ((length == 1) || n == 0)
		return *this;

	ListItem<T>* new_begin = find_item(n);
	ListItem<T>* new_end = find_item(n-1);

	begin->prev = end;
	end->next = begin;
	new_begin->prev = NULL;
	new_end->next = NULL;

	begin = new_begin;
	end = new_end;

	return *this;
}

