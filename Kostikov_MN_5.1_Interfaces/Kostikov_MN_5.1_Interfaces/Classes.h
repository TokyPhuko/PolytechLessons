#ifndef CLASSES_H
#define CLASSES_H

#include "Interfaces.h"


template<typename T>
class ArrayIterator : public IIterator<T> {
protected:
	T* array;
	int size;
	int pos = 0;
public:
	ArrayIterator(T* array, int size);
	bool hasNext();
	T& next();
};

template<typename T>
class MyArray : public IEnumerable<T> {
protected:
	T* array = nullptr;
	int size = 0;
public:
	IIterator<T>& iterator();

	~MyArray();

	void generate(int size, int max);
};

template<typename T>
class MyStack : public MyArray<T>, public IStack<T> {
public:
	MyStack();

	T* top();
	void push(T& val);
	void pop();
	IIterator<T>& iterator();
};

template<typename T>
class StackIterator : public IIterator<T> {
protected:
	T** originalArray;
	T* array;
	int size;
	int pos = 0;

	bool ArrayChanged();
public:
	StackIterator(T** array, int size);
	bool hasNext();
	T& next();
};

template<typename T>
class MyQueue : public MyArray<T>, public IQueue<T> {
public:
	T* front();
	T* back();
	void push(T& val);
	void pop();
};

template<typename T>
class MyListItem : public IListItem<T> {
private:
	T value;
	IListItem<T>* next;
	IListItem<T>* prev;
public:
	MyListItem(T value, IListItem<T>* prev, IListItem<T>* next);
	T getValue();
	void setValue(T new_value);
	IListItem<T>* getNext();
	void setNext(IListItem<T>* new_next);
	IListItem<T>* getPrev();
	void setPrev(IListItem<T>* new_prev);
};

template<typename T>
class MyList : public IDoublyLinkedList<T> {
private:
	IListItem<T>* begin = nullptr;
	IListItem<T>* end = nullptr;
	int size = 0;
public:
	void addToEnd(T value);
	void addToBegin(T value);
	void extractFromEnd();
	void extractFromBegin();
	void insert(int n, T value);
	void remove(int n);
	void printItem(int n);

	~MyList();
};


#endif