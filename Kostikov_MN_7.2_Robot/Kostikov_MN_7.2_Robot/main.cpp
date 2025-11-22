/*7. Написать отдельную программу, работающую со струкурой Robot. У каждого
робота должен быть номер, завод - изготовитель и указатель на фунцию вывода
информации о его назначении.Поле завода - изготовителя должно быть
перечисляемым типом.Объявить не менее трёх различных функций для
информирования о назначении робота.Текст с информацией о назначении робота
должен содержать информацию о номере и заводе.Продемонстрировать работу
программы на примере работы с динамическим массивом роботов.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// Вводим новые перечисляемые типы
enum Factory { CADB, Sugar, Brick, Tire };
// Вводим новое обозначение типа
typedef void (*Print_fun)(int);

// Вводим структуру
struct Robot {
	int Number;
	Factory factory;
	Print_fun print;
};
// Выбор завода для робота
Factory get_factory(int s) {
	switch (s) {
	case 0:
		return CADB;
	case 1:
		return Sugar;
	case 2:
		return Brick;
	case 3:
		return Tire;
	default:
		return Tire;
	}
}
// Функции представления робота
void print_CADB(int n) {
	printf("Factory CADB. I'm a robot numder: %d. My name is Marvin. People gave me an emotions chip, and now I have depression. I can help people with chemistry and vehicles.\n", n);
}
void print_Sugar(int n) {
	printf("Factory sugar. 'm a robot numder: %d. My name is Peter. I can taste sugar.\n", n);
}
void print_Brick(int n) {
	printf("Factory Brick. I'm a robot numder: %d. My name is Brad. Itasting bricks.\n", n);
}
void print_Tire(int n) {
	printf("Factory Tire. I'm a robot numder: %d. My name is Olivie Messian. I play music.\n", n);
}
//функция определиня функций представления для робота того или иного завода
Print_fun get_print_factory_fun(Factory factory) {
	switch (factory) {
	case CADB:
		return print_CADB;
	case Sugar:
		return print_Sugar;
	case Brick:
		return print_Brick;
	case Tire:
		return print_Tire;
	default:
		return print_Tire;
	}
}

int main() {
	int n;
	printf("Enter aaray size: ");
	scanf_s("%d", &n);
	// Создаём и заполняем массив
	Robot* arr = new Robot[n];
	for (int i = 0; i < n; i++) {
		arr[i].Number = rand(); //рандомный номер робота
		arr[i].factory = get_factory(rand() % 4); //рандомный завод
		arr[i].print = get_print_factory_fun(arr[i].factory);
	}
	//выводим массив
	for (int i = 0; i < n; i++) {
		arr[i].print(arr[i].Number);
	}

	delete[] arr;//очищаем память
	system("pause");
	return 0;
}//P.S. Назначение у меня привязано к типу завода, т.к. нигде в задаче строго не оговорено, что так нельзя. Просто уточняю на всякий случай.