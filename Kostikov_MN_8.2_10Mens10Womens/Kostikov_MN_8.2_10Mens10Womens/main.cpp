//7. Написать отдельную программу, где будет задан массивы из 10 мужских и 10
//женских имен.Программа просит пользователя выбрать имена(произвольное
//	количество), формирует массив студентов с указанными именами и выводит его на
//	экран.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // rand()
#include <string> // strcpy, strcat, strlen

int main() {
	int n;
	const char* mens[] = { "Nikita", "Sergei", "Matvey", "Artem", "Aleksey" };//заводим массивы имен
	const char* womens[] = { "Sasha", "Dasha", "Masha", "Natasha", "Ksusha" };
	char** peoples;

	printf("Enter the number of names ");
	scanf("%d", &n);

	int count_girls = rand() % (n+1);//возьмем рандомное число женщин
	peoples = new char*[n];

	for (int i = 0; i < count_girls; i++) {//запишем в общий массив всех женщин
		int z = rand() % 5;//рандомный индекс для массива женщин
		peoples[i] = new char[strlen(womens[z])+1];//выделяем память
		strcpy(peoples[i], womens[z]);//копируем
	}
		
	for (int i = count_girls; i < n; i++) {//запишем в общий массив всех мужчин
		int z = rand() % 5;//рандомный индекс для массива мужчин
		peoples[i] = new char[strlen(mens[z])+1];//выделяем память
		strcpy(peoples[i], mens[z]);//копируем
	}

	for (int i = 0; i < n; i++)//выводим массив
		printf("\n%s", peoples[i]);

	for (int i = 0; i < n; i++) {//чистим память
		delete[] peoples[i];
	}

	delete[] peoples;
	system("pause");
	return 0;
}