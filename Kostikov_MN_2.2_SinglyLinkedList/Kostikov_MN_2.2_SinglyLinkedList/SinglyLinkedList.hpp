#pragma once
#include"SinglyLinkedList.h"
#include<iostream>

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(int length) {
	for (int i = 0; i < length; i++) {
		this->Add(0, i);
	}
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
	for (int i = 0; i < other.Size(); i++) {
		this->Add(other[i], i);
	}
}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
	int real_length = this->length;
	for (int i = 0; i < real_length; i++) {
		this->Delete(0);
	}
}

template<typename T>
void SinglyLinkedList<T>::Add(int n, int pos) {
	if (this->length == 0) {
		this->head = new SinglyListItem<T>;
		this->head->ChangeNext(this->head);
		this->head->ChangeData(n);
		this->length = 1;
	}
	else {
		SinglyListItem<T>* new_item = new SinglyListItem<T>;
		new_item->ChangeData(n);
		SinglyListItem<T>* current_item = this->head;
		
		for (int i = 0; i < pos; i++) {
			current_item = current_item->GetNext();
		}

		SinglyListItem<T>* last_item = this->head;
		while (last_item->GetNext() != current_item) {
			last_item = last_item->GetNext();
		}

		new_item->ChangeNext(last_item->GetNext());
		last_item->ChangeNext(new_item);

		this->length++;
		if (pos == 0) {
			this->head = new_item;
		}
	}
}

template<typename T>
void SinglyLinkedList<T>::Delete(int pos) {
	SinglyListItem<T>* current_item = this->head;

	for (int i = 0; i < pos; i++) {
		current_item = current_item->GetNext();
	}

	SinglyListItem<T>* last_item = this->head;
	while (last_item->GetNext() != current_item) {
		last_item = last_item->GetNext();
	}

	last_item->ChangeNext(current_item->GetNext());

	if (pos == 0) {
		this->head = last_item;
	}

	this->length--;
	delete current_item;
}

template<typename T>
int SinglyLinkedList<T>::FindItem(T n) {
	SinglyListItem<T>* current_item = this->head;
	int pos = 0;

	while (current_item->GetData() != n) {
		current_item = current_item->GetNext();
		pos++;
	}

	return pos;
}

template<typename T>
int SinglyLinkedList<T>::Size() const {
	return this->length;
}

template<typename T>
void SinglyLinkedList<T>::Print() {
	SinglyListItem<T>* current_item = this->head;

	while (current_item->GetNext() != this->head) {
		std::cout << current_item->GetData() << ' ';
		current_item = current_item->GetNext();
	}

	std::cout << current_item->GetData() << ' ';
	std::cout << std::endl;
}

template<typename T>
void SinglyLinkedList<T>::ReSize(int new_length) {
	if (this->length > new_length) {
		while (this->length > new_length) {
			this->Delete(this->length-1);
		}
	}
	else {
		while (this->length < new_length) {
			this->Add(0, this->length);
		}
	}
}

template<typename T>
T SinglyLinkedList<T>::operator[](int pos) const {
	SinglyListItem<T>* current_item = this->head;

	for (int i = 0; i < pos; i++) {
		current_item = current_item->GetNext();
	}

	return current_item->GetData();
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList& other) {
	int real_length = this->length;
	for (int i = 0; i < real_length; i++) {
		this->Delete(0);
	}

	for (int i = 0; i < other.Size(); i++) {
		this->Add(other[i], i);
	}

	return *this;
}

template<typename T>
void SinglyLinkedList<T>::operator<<(int n) {
	n = n % this->length;

	SinglyListItem<T>* current_item = this->head;
	int pos = 0;

	for (int i = 0; i < n; i++) {
		current_item = current_item->GetNext();
	}

	this->head = current_item;
}

template<typename T>
void SinglyLinkedList<T>::operator>>(int n) {
	n = n % this->length;
	n = this->length - n;

	SinglyListItem<T>* current_item = this->head;
	int pos = 0;

	for (int i = 0; i < n; i++) {
		current_item = current_item->GetNext();
	}

	this->head = current_item;
}

template<typename T>
SinglyLinkedList<T> SinglyLinkedList<T>::operator+(SinglyLinkedList& other) {
	for (int i = 0; i < other.Size(); i++) {
		this->Add(other[i], this->length);
	}

	return *this;
}