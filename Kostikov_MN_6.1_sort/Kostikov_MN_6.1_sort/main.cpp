/*1. Переделать программу под сортировку данных типа double;
2. Выделить вывод массива на экран и сортировку в отдельные функции. Обе функции
должны получать массив через свои аргументы;
3. Ввести обработку некорректного ввода пользователем элементов массива;*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// Функция получения от пользователя размера массива
// Используется передача по указателю, чтобы изменить переменную
// в области видмости функции main
void ask_user(int* n) {
	char debug; // Для отладки
	printf("Enter array size: ");
	while (scanf("%d", n) < 1) { // Проверка корректности ввода
		debug = getchar(); // Проглатываем некорректный символ
		printf("You've entered %c. Try one more time: ", debug);
	}
}

void printMas(int n, double* a) {
	for (int i = 0; i < n; i++)
		printf("%Lf ", a[i]);
}

void sortMas(int n, double* a) {
	for (int i = 0; i < n; i++) {
		int k = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[k])
				k = j;
		}
		//Выполняем перестановку элементов
		double temp = a[k];
		a[k] = a[i];
		a[i] = temp;
	}
}
int main() {
	int n; // Храним размер массива
	double* a; // Храним адрес массива
	// Получаем размер массива от пользователя
	ask_user(&n);
	// Создаём динамический массив
	a = new double[n];
	// Просим польльзователя ввести массив
	for (int i = 0; i < n; i++) {
		printf("Enter %d-th item: ", i);
		char debug; // Для отладки
		while (scanf("%Lf", &a[i]) < 1) { // Проверка корректности ввода
			debug = getchar(); // Проглатываем некорректный символ
			printf("You've entered %c. Try one more time: ", debug);
		}
	}
	// Выводим исходный массив
	printf("Initial array:\n");
	printMas(n, a);
	// Выполняем сортировку массива
	// Алгоритм: сортировка выбором
	sortMas(n, a);
	// Выводим отсортированный массив
	printf("\nSorted array:\n");
	printMas(n, a);
	printf("\n");
	// Освобождаем память
	delete[] a;
	system("pause");
	return 0;
}