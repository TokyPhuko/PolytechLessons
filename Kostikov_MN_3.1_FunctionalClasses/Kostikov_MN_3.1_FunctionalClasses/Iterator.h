#pragma once
// Вводим тип итератора
enum IteratorType {
	Forward, Reverse, RingForward, RingReverse
};
template<typename T>
class ArrayIterator {
private:
	T* array;
	int size;
	IteratorType iterator_type;
	int shift = 0;
	// Запрет создания экземпляров по умолчанию
	ArrayIterator();
public:
	// Конструктор для случаев Forward и Reverse
	ArrayIterator(T* array, int size, IteratorType iterator_type);
	// Конструктор для случая Ring
	ArrayIterator(T* array, int size, int shift, IteratorType iterator_type);
	// Оператор возращает элемент по индексу в зависимости от типа итератора
	T& operator()(int i);
};