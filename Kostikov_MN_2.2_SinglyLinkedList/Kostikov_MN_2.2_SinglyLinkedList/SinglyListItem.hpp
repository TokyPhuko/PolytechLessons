#pragma once
#include"SinglyListItem.h"

template<typename T>
SinglyListItem<T>::SinglyListItem() {
	this->data = 0;
	this->next = this;
}

template<typename T>
SinglyListItem<T>::SinglyListItem(T data, SinglyListItem<T>* head) {
	this->data = data;
	this->next = head;
}

template<typename T>
void SinglyListItem<T>::ChangeData(T new_data) {
	this->data = new_data;
}

template<typename T>
void SinglyListItem<T>::ChangeNext(SinglyListItem<T>* new_next) {
	this->next = new_next;
}

template<typename T>
T SinglyListItem<T>::GetData() {
	return this->data;
}

template<typename T>
SinglyListItem<T>* SinglyListItem<T>::GetNext() {
	return this->next;
}