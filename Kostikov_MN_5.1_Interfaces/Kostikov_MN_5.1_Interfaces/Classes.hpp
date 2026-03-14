#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <cstring>
#include <cstdlib>
#include "Classes.h"

template<typename T>
ArrayIterator<T>::ArrayIterator(T* array, int size) : array(array), size(size) {}

template<typename T>
bool ArrayIterator<T>::hasNext() {
	return pos < size;
}

template<typename T>
T& ArrayIterator<T>::next() {
	T& item = array[pos];
	pos++;
	return item;
}

template<typename T>
MyArray<T>::~MyArray() {
	delete[] this->array;
}

template<typename T>
IIterator<T>& MyArray<T>::iterator() {
	return *(new ArrayIterator<T>(array, size));
}

template<typename T>
void MyArray<T>::generate(int size, int max) {
	if (this->array != nullptr)
		delete[] this->array;
	this->array = new T[size];
	this->size = size;
	for (int i = 0; i < size; i++)
		this->array[i] = rand() % max;
}

template<typename T>
MyStack<T>::MyStack() {}

template<typename T>
T* MyStack<T>::top() {
	if (this->array == nullptr)
		return nullptr;
	else
		return &(this->array[0]);
}

template<typename T>
void MyStack<T>::push(T& val) {
	T* new_array = new T[this->size + 1];
	if (this->array != nullptr) {
		memcpy(new_array + 1, this->array, this->size * sizeof(T));
		delete[] this->array;
	}
	this->array = new_array;
	this->array[0] = val;
	this->size++;
}

template<typename T>
void MyStack<T>::pop() {
	if (this->array != nullptr) {
		T* new_array;
		if (this->size > 1) {
			new_array = new T[this->size - 1];
			memcpy(new_array, this->array + 1, (this->size - 1) * sizeof(T));
		}
		else
			new_array = nullptr;
		delete[] this->array;
		this->array = new_array;
		this->size--;
	}
}

template<typename T>
IIterator<T>& MyStack<T>::iterator() {
	return *(new StackIterator<T>(&(MyArray<T>::array), MyArray<T>::size));
}

template<typename T>
StackIterator<T>::StackIterator(T** array, int size) : array(*array), size(size), originalArray(array) {}

template<typename T>
bool StackIterator<T>::ArrayChanged() {
	if (array != *originalArray)
		return true;
	return false;
}

template<typename T>
bool StackIterator<T>::hasNext() {
	if (this->ArrayChanged()) {
		std::cout << std::endl <<  "Critical error, stack was changed" << std::endl;
		return false;
	}
	
	return pos < size;
}

template<typename T>
T& StackIterator<T>::next() {
	T& item = array[pos];
	pos++;
	return item;
}

template<typename T>
T* MyQueue<T>::front() {
	if (this->array == nullptr)
		return nullptr;
	else
		return &(this->array[0]);
}

template<typename T>
T* MyQueue<T>::back() {
	if (this->array == nullptr)
		return nullptr;
	else
		return &(this->array[this->size-1]);
}

template<typename T>
void MyQueue<T>::push(T& val) {
	T* new_array = new T[this->size + 1];
	if (this->array != nullptr) {
		memcpy(new_array, this->array, this->size * sizeof(T));
		delete[] this->array;
	}
	this->array = new_array;
	this->array[this->size] = val;
	this->size++;
}

template<typename T>
void MyQueue<T>::pop() {
	if (this->size > 1) {
		--this->size;
		T* new_array = new T[this->size];
		if (this->array != nullptr) {
			memcpy(new_array, this->array + 1, this->size * sizeof(T));
			delete[] this->array;
		}
		this->array = new_array;
	}
	else {
		this->size = 0;
		this->array = nullptr;
	}
}

template<typename T>
MyListItem<T>::MyListItem(T value, IListItem<T>* prev, IListItem<T>* next) : value(value), prev(prev), next(next) {}

template<typename T>
T MyListItem<T>::getValue() {
	return this->value;
}

template<typename T>
void MyListItem<T>::setValue(T new_value) {
	this->value = new_value;
}

template<typename T>
IListItem<T>* MyListItem<T>::getNext() {
	return this->next;
}

template<typename T>
void MyListItem<T>::setNext(IListItem<T>* new_next) {
	this->next = new_next;
}

template<typename T>
void MyListItem<T>::setPrev(IListItem<T>* new_prev) {
	this->prev = new_prev;
}

template<typename T>
IListItem<T>* MyListItem<T>::getPrev() {
	return this->prev;
}

template<typename T>
void MyList<T>::addToEnd(T value) {
	if (this->size == 0) {
		IListItem<T>* item = new MyListItem<T>(value, nullptr, nullptr);
		this->begin = item;
		this->end = item;
	}
	else {
		IListItem<T>* item = new MyListItem<T>(value, this->end, nullptr);
		this->end->setNext(item);
		this->end = item;
	}

	this->size++;
}

template<typename T>
void MyList<T>::addToBegin(T value) {
	if (this->size == 0) {
		IListItem<T>* item = new MyListItem<T>(value, nullptr, nullptr);
		this->begin = item;
		this->end = item;
	}
	else {
		IListItem<T>* item = new MyListItem<T>(value, nullptr, this->begin);
		this->begin->setPrev(item);
		this->begin = item;
	}

	this->size++;
}

template<typename T>
void MyList<T>::extractFromEnd() {
	if (this->size > 0) {
		IListItem<T>* new_end = this->end->getPrev();
		new_end->setNext(nullptr);

		delete this->end;

		this->end = new_end;

		this->size--;
	}
}

template<typename T>
void MyList<T>::extractFromBegin() {
	if (this->size > 0) {
		IListItem<T>* new_begin = this->begin->getNext();
		new_begin->setPrev(nullptr);

		delete this->begin;

		this->begin = new_begin;

		this->size--;
	}
}

template<typename T>
void MyList<T>::insert(int n, T value) {
	n--;

	if (n < size) {
		IListItem<T>* current = this->begin;

		for (int i = 0; i < n; i++)
			current = current->getNext();

		IListItem<T>* item = new MyListItem<T>(value, current->getPrev(), current);
		current->getPrev()->setNext(item);
		current->setPrev(item);

		this->size++;
	}
	else if (n == this->size) {
		this->addToEnd(n);
	}
}

template<typename T>
void MyList<T>::remove(int n) {
	n--;

	if (0 < n < this->size-1) {
		IListItem<T>* current = this->begin;

		for (int i = 0; i < n; i++)
			current = current->getNext();

		current->getPrev()->setNext(current->getNext());
		current->getNext()->setPrev(current->getPrev());

		delete current;

		size--;
	}
	else if (n == 0) {
		this->extractFromBegin();
	}
	else if (n == this->size - 1) {
		this->extractFromEnd();
	}
}

template<typename T>
void MyList<T>::printItem(int n) {
	n--;

	if (n < this->size) {
		IListItem<T>* current = this->begin;

		for (int i = 0; i < n; i++) {
			current = current->getNext();
		}

		std::cout << current->getValue() << ' ';
	}
}

template<typename T>
MyList<T>::~MyList() {
	for (int i = 0; i < this->size; i++) {
		extractFromBegin();
	}
}


#endif