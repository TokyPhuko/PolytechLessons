//1. Перегрузить операторы доступ по индеску для получения цифры представления
//числа;
//2. Написать собственную реализацию функций itoa / atoi / strtol;
//3. Добавить перегрузку арифметических операторов;
//4. Сделать класс шаблонным в качестве типа для хранения числа;

#include "IntegerFormatter.h"

int main() {
	IntegerFormatter<int> a("12r1234");
	a.print();
	a.setRadix(10);
	a.print(); 
	IntegerFormatter<int> b(15, 16);
	b.print();
	b.set(30);
	b.print();
	std::cout << b[1] << std::endl;
	std::cin >> a;
	//a = b + b;
	std::cout << a.get() << std::endl << b.get();
}