//1. Перегрузить оператор присваивания;
//2. Перегрузить оператор доступ по индеску для получения значения;
//3. Перегрузить операторы сдвига;
//4. Добавить метод изменения размера буфера;
//5. Перегрузить оператор сложения для объединения буферов;

#include <iostream>
#include <string>
#include "RingBuffer.hpp"
int main()
{
	//RingBuffer<int> a;
	RingBuffer<int> a(5);
	a.Print();
	a.PrintAll();
	std::cout << "--- Push ---" << std::endl;
	for (int i = 0; i < 12; i++) {
		a.Push(i);
		a.Print();
		a.PrintAll();
	}
	std::cout << "--- Pop ---" << std::endl;
	for (int i = 0; i < 12; i++) {
		a.Pop();
		a.Print();
		a.PrintAll();
	}
	std::cout << "--- Push ---" << std::endl;
	for (int i = 0; i < 12; i++) {
		a.Push(i);
		a.Print();
		a.PrintAll();
	}
	RingBuffer<int> b(a);
	b.PrintAll();
	b + a;
	b.PrintAll();
	b.Print();
	return 0;
}