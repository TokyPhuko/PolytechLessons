//Написать отдельную программу, в которой объявлена структура Computer,
//содержащая не менее 3 - х параметров различных типов, описаюващих
//характеристики компьютера.Программа считывает из файла массив записей,
//содержащих параметры структуры, записанные в текстовом виде и выводит его на
//экран.Использовать для разбора строки функцию sscanf(аналог scanf);.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

enum Model { Apple_MacBook_Air_M2, Honor_Magicbook_X16, Huawei_MateBook_D16, Asus_VivoBook_15, Lenovo_IdeaPad_Slim_3 };//перечисление моделей ноутбуков

struct Computer {
	char* owner;
	Model model;
	float price;

	Computer() : owner(nullptr), model(Apple_MacBook_Air_M2), price(84599.9) {}//конструктор по умолчанию

	~Computer() {//деструктор
		delete[] owner;
	}

	Model strToModel(const char* str) {//преобразуем текстове данные в модель
		if (strcmp(str, "Apple_MacBook_Air_M2") == 0) return Apple_MacBook_Air_M2;
		if (strcmp(str, "Honor_Magicbook_X16") == 0) return Honor_Magicbook_X16;
		if (strcmp(str, "Huawei_MateBook_D16") == 0) return Huawei_MateBook_D16;
		if (strcmp(str, "Asus_VivoBook_15") == 0) return Asus_VivoBook_15;
		if (strcmp(str, "Lenovo_IdeaPad_Slim_3") == 0) return Lenovo_IdeaPad_Slim_3;
		return Apple_MacBook_Air_M2;
	}

	const char* modelTownertr() {//преобразование модели в текст
		switch (model) {
			case Apple_MacBook_Air_M2: return "Apple MacBook Air M2";
			case Honor_Magicbook_X16: return "Honor Magicbook X16";
			case Huawei_MateBook_D16: return "Huawei MateBook D16";
			case Asus_VivoBook_15: return "Asus VivoBook 15";
			case Lenovo_IdeaPad_Slim_3: return "Lenovo IdeaPad Slim 3";
			default: return "Apple MacBook Air M2";
		}
	}

	void importFromStr(const char* str) {//парсим строку
		char str_model[50];
		char str_owner[50];
		sscanf(str, "%49[^;];%49[^;];%f", str_owner, str_model, &price);
		delete[] owner;
		owner = new char[strlen(str_owner)+1];
		strcpy(owner, str_owner);
		model = strToModel(str_model);
	}

	void print() {//вывод информации о компьютере
		printf("%s, %s, %f rub; \n", owner, modelTownertr(), price);
	}
};

int main() {
	{//создадим необходимый файл и заполним его рандомными данными
		FILE* file = fopen("text.txt", "w");
		const char* owners[] = {
			"Paul McCartney",
			"John Lennon",
			"George Harrison",
			"Ringo Starr",
			"Matvey Aleksandrov",
			"Redrik Shuhart",
			"Boris Nuraliev"
		};
		const char* computers[] = {
			"Apple MacBook Air M2",
			"Honor Magicbook X16",
			"Huawei MateBook D16",
			"Asus VivoBook 15",
			"Lenovo IdeaPad Slim 3"
		};
		for (int i = 0; i < 10; i++) {
			char buffer[200];
			sprintf(buffer, "%s;%s;%f;\n", owners[rand()%7], computers[rand()%5], rand()%999999/10.0+80000);//заполним файл данными
			fputs(buffer, file);
		}
		fclose(file);
	}

    FILE* file = fopen("text.txt", "r");//теперь сноваа откроем файл

    int lines_count = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file)) lines_count++;//посчитаем число строк

    Computer* computers = new Computer[lines_count];//создадим массив подходящего размера

    rewind(file);//вернемся в начало файла

    int current_line = 0;
    while (fgets(buffer, sizeof(buffer), file) && current_line < lines_count) {//заполним массив данными из файла
		computers[current_line].importFromStr(buffer);
		current_line++;
    }

    fclose(file);//закрываем файл

    for (int i = 0; i < lines_count; i++) {//выводим данные массива
        printf("%d: ", i + 1);
        computers[i].print();
    }

    delete[] computers;
	system("pause");
	return 0;
}