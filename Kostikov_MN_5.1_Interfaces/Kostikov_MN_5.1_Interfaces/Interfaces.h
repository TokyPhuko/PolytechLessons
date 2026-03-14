#ifndef INTERFACES_H
#define INTERFACES_H


template<typename T>
class IIterator {
public:
	virtual bool hasNext() = 0;
	virtual T& next() = 0;
};

template<typename T>
class IEnumerable {
public:
	virtual IIterator<T>& iterator() = 0;
};

template<typename T>
class IStack {
public:
	virtual T* top() = 0;
	virtual void push(T& val) = 0;
	virtual void pop() = 0;
};

template<typename T>
class IQueue {
public:
	virtual T* front() = 0;
	virtual T* back() = 0;
	virtual void push(T& val) = 0;
	virtual void pop() = 0;
};

template<typename T>
class IListItem {
public:
	virtual T getValue() = 0;
	virtual void setValue(T new_value) = 0;
	virtual IListItem<T>* getNext() = 0;
	virtual void setNext(IListItem<T>* new_next) = 0;
	virtual IListItem<T>* getPrev() = 0;
	virtual void setPrev(IListItem<T>* new_prev) = 0;
};

template<typename T>
class IDoublyLinkedList {
public:
	virtual void addToEnd(T value) = 0;
	virtual void addToBegin(T value) = 0;
	virtual void extractFromEnd() = 0;
	virtual void extractFromBegin() = 0;
	virtual void insert(int n, T value) = 0;
	virtual void remove(int n) = 0;
};


#endif