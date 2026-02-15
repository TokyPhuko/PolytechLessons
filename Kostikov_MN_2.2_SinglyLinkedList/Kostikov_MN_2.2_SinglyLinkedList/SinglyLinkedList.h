#pragma once
#include"SinglyListItem.hpp"

template<typename T>
class SinglyLinkedList {
private:
	SinglyListItem<T>* head = nullptr;
	int length = 0;

	SinglyLinkedList();
public:
	SinglyLinkedList(int length);
	SinglyLinkedList(const SinglyLinkedList& other);
	~SinglyLinkedList();

	void Add(int n, int pos);
	void Delete(int pos);
	int FindItem(T n);
	int Size() const;
	void Print();
	void ReSize(int new_length);

	T operator[](int pos) const;
	SinglyLinkedList<T>& operator=(SinglyLinkedList& other);
	void operator<<(int n);
	void operator>>(int n);
	SinglyLinkedList<T> operator+(SinglyLinkedList& other);
};