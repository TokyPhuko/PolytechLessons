#pragma once
#include "Iterator.h"
// Конструктор для случаев Forward и Reverse
template<typename T>
ArrayIterator<T>::ArrayIterator(T* array, int size, IteratorType iterator_type) : array(array),
size(size), iterator_type(iterator_type) {
}
// Конструктор для случая Ring
template<typename T>
ArrayIterator<T>::ArrayIterator(T* array, int size, int shift, IteratorType iterator_type) : array(array), size(size),
iterator_type(iterator_type), shift(shift) {
}
// Оператор возращает элемент по индексу в зависимости от типа итератора
template<typename T>
T& ArrayIterator<T>::operator()(int i) {
	switch (iterator_type) {
	case Forward:
		return array[i];
	case Reverse:
		return array[size - 1 - i];
	case RingForward:
		return array[(i + shift) % size];
	case RingReverse:
		return array[size - ((i + shift) % size)];
	}
}