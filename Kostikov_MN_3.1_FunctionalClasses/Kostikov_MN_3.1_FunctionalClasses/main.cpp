#include <iostream>
#include "Generator.hpp"
#include "Filter.hpp"
#include "Iterator.hpp"
// Test array
int array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
// General functions
template<typename T>
void print(T fun) {
	for (int i = -10; i < 10; i++)
		std::cout << "x = " << i << "; fun(x) = " << fun(i) << std::endl;
}
template<typename T>
void iterate(T iter) {
	for (int i = 0; i < 10; i++)
		std::cout << "x = " << i << "; iter(x) = " << iter(i) << std::endl;
}
// Examples of function
int quadpoly(int x) {
	return 1 * x * x + 2 * x + 0;
}
bool rangetest(int x) {
	return (x > -10) && (x < 0);
}
int simpleiterator(int i) {
	return array[i];
}
int main() {
	// Проверка шаблона "Генератор"
	std::cout << "--- Test generators ---" << std::endl;
	QuadPoly<int> p1(1, 2, 0), p2(2, 0, 1);
	std::cout << "quadpoly" << std::endl;
	print(quadpoly);
	std::cout << "p1" << std::endl;
	print(p1);
	std::cout << "p2" << std::endl;
	print(p2);
	// Проверка шаблона "Фильтр"
	std::cout << std::endl << "--- Test filters ---" << std::endl;
	RangeTest<int> f1(-5, 1, Both), f2(3, Lower), f3(0, Upper);
	std::cout << "rangetest" << std::endl;
	print(rangetest);
	std::cout << "f1" << std::endl;
	print(f1);
	std::cout << "f2" << std::endl;
	print(f2);
	std::cout << "f3" << std::endl;
	print(f3);
	// Проверка шаблона "Итератор"
	std::cout << std::endl << "--- Test iterators ---" << std::endl;
	ArrayIterator<int> i1(array, 10, Forward), i2(array, 10, Reverse), i3(array, 10, 3, RingReverse);
	std::cout << "simpleiterator" << std::endl;
	iterate(simpleiterator);
	std::cout << "i1" << std::endl;
	iterate(i1);
	std::cout << "i2" << std::endl;
	iterate(i2);
	std::cout << "i3" << std::endl;
	iterate(i3);
	return 0;
}