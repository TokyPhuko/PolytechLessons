/*4. Написать отдельную программу, которая будет запрашивать у пользователя размер
массива и массив из чисел типа float и выполнять сортировку слиянием (см. лекции
по ОЦТ). Причём сортировка должна быть отдельной функцией, а выбор
напралвния определяется через один из её аргументов. Функция сортировки не
должна ничего выводить на экран или запрашивать у пользователя!*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
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

void printMas(int n, float* a) {
	for (int i = 0; i < n; i++)
		printf("%f ", a[i]);
}

typedef bool (*CMP_FUN)(float, float);//псевдоним указателя на функцию из лекции по информатике

void Merge(float* ArrLeft, float* ArrRight, int NLeft, int NRight, CMP_FUN cmpFun) {
	// Создаем временный массив для хранения результата слияния
	float* b = new float[NLeft + NRight];
	int i = 0, j = 0, k = 0;  // Индексы для левого, правого и результирующего массивов

	// Пока есть элементы хотя бы в одном из массивов
	while ((i < NLeft) || (j < NRight)) {
		// Если есть элементы в обоих массивах
		if ((i < NLeft) && (j < NRight)) {
			// Используем пользовательскую функцию сравнения для определения порядка
			if (cmpFun(ArrLeft[i], ArrRight[j]))
				b[k++] = ArrLeft[i++];  // Берем элемент из левого массива
			else
				b[k++] = ArrRight[j++]; // Берем элемент из правого массива
		}
		else {
			// Если один из массивов закончился, берем из оставшегося
			if (i == NLeft)
				b[k++] = ArrRight[j++]; // Левый массив пуст - берем из правого
			else
				b[k++] = ArrLeft[i++];  // Правый массив пуст - берем из левого
		}
	}

	// Копируем отсортированный результат обратно в исходный массив
	memcpy(ArrLeft, b, (NLeft + NRight) * sizeof(int));
	delete[] b;  // Освобождаем временную память
}

void MergeSort(float* Arr, int N, CMP_FUN cmpFun) {
	float* arr_left, * arr_right;  // Указатели на левую и правую части
	int n_left, n_right;           // Размеры левой и правой частей

	// Базовый случай рекурсии: если массив содержит больше одного элемента
	if (N > 1) {
		// Разделяем массив на две примерно равные части
		n_left = N / 2;
		n_right = N - n_left;
		arr_left = Arr;           // Левая часть начинается с начала массива
		arr_right = Arr + n_left; // Правая часть начинается после левой

		// Рекурсивно сортируем обе части
		MergeSort(arr_left, n_left, cmpFun);
		MergeSort(arr_right, n_right, cmpFun);

		// Сливаем отсортированные части
		Merge(arr_left, arr_right, n_left, n_right, cmpFun);
	}
}


int main() {
	int n; // Храним размер массива
	float* a; // Храним адрес массива
	// Получаем размер массива от пользователя
	ask_user(&n);
	// Создаём динамический массив
	a = new float[n];
	// Просим польльзователя ввести массив
	for (int i = 0; i < n; i++) {
		printf("Enter %d-th item: ", i);
		char debug; // Для отладки
		while (scanf("%f", &a[i]) < 1) { // Проверка корректности ввода
			debug = getchar(); // Проглатываем некорректный символ
			printf("You've entered %c. Try one more time: ", debug);
		}
	}
	// Выводим исходный массив
	printf("Initial array:\n");
	printMas(n, a);
	printf("\n");
	// Выполняем сортировку массива
	// Алгоритм: сортировка слиянием
	char order;
	printf("Do you want to sort in ascending order?(y/n)");
	getchar();
	scanf("%c", &order);
	if (order == 'y') {//определение порядка сортировки
		MergeSort(a, n, [](float A, float B) {return A < B;});//передача лямбда функции сравнения как параметра,
	} //удобно использовать лямбду как функцию сравнения. тк в зависимости от направления сортировки нам надо менять ровно одно выражение в коде
	else { 
		MergeSort(a, n, [](float A, float B) {return A > B;});//передача лямбда функции сравнения как параметра
	}//лямбда - ананонимная функция, используя ее можно без лишнего кода изменить необходимое нам выражениеб передав ее как параметр
	// Выводим отсортированный массив
	printf("\nSorted array:\n");
	printMas(n, a);
	printf("\n");
	// Освобождаем память
	delete[] a;
	system("pause");
	return 0;
}