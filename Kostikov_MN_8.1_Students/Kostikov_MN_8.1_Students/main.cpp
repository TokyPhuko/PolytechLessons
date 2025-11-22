//1. Найти утечку памяти и устранить её;
//2. Сделать так, что женский пол был при 0, мужской при 1;
//3. Ввести обработку случаев пола undefined;
//4. Ввести в структуру метод формирования данных о случайном студенте и
//использовать его при заполнении массива;
//5. Хранить имя студента в структуре в виде динамического массива ровно той длины,
//которая требуется для хранения его имени;
//6. Рассортировать массив студентов на три массива, в каждом из которых будут
//храниться студенты только одного пола.Также сформировать итоговую строку с
//именами студентов каждого из массивов;


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // rand()
#include <string> // strcpy, strcat, strlen
enum GenderType { female, male, undefined };
const char* gender_str[3] = { "female", "male", "undefined" };
typedef unsigned int myuint;


const char* gender2String(GenderType gender);// Получаем строку для значения пола


struct Student {// Структура для хранения данных о студенте
	GenderType gender;//пол студента
	unsigned char age;//воздаст студентв
	char* name;//имя
	
	void print() {// Метод вывода информации о студенте на экран
		printf("Gender: %s; Age: %d; Name: %s\n", gender2String(gender), age, name);//функция вывода информации о студенте
	}

	void formingRandomStudent() {//функция формирования рандомного студента
		const char* female_names[] = { "Ann", "Kate", "Sara" };//массивы имен
		const char* male_names[] = { "John", "Tom", "Bob" };
		const char undefined_name[] = "Unknown";
		gender = (GenderType)(rand() % 3);
		age = (rand() % 6) + 18;
		const char** names = NULL;

		switch (gender) {
		case male:
			names = male_names;
			break;
		case female:
			names = female_names;
			break;
		}
		
		if (gender == undefined) {//обработка случая неизвестного пола
			name = new char[strlen(undefined_name) + 1];//+1 для символа конца строки
			strcpy(name, undefined_name);//копирование имени
		}
		else {
			int z = rand() % 3;
			name = new char[strlen(names[z]) + 1];//+1 для символа конца строки
			strcpy(name, names[z]);//копирование имени
		}
	}

	void copy(Student& student) {//функция для копирования студента
		gender = student.gender;
		age = student.age;
		name = student.name;//тут стоит отметить, что я передаю именно указатель на имя а не само имя, чтобы потом удобно можно было очистить дин. память
	}
};


void printStudents(Student* students, myuint n);
void cleanNames(Student* students, int n);


int main() {
	const myuint n = 5;
	
	Student students[n];
	for (myuint i = 0; i < n; i++) {// Заполняем массив студентов
		students[i].formingRandomStudent();
	}
	
	for (myuint i = 0; i < n; i++)// Вывод массива на экран
		students[i].print();

	printStudents(students, n);//вывод массива как строки

	Student students_male[n];//создаем массивы мужчин, женщин и неизвестного пола, из максимальная длина n
	Student students_female[n];
	Student students_undefined[n];
	myuint male_i = 0;
	myuint female_i = 0;
	myuint undefined_i = 0;

	for (myuint i = 0; i < n; i++) {//распределим студентов по массивам в зависимости от пола
		switch (students[i].gender) {
		case male:
			students_male[male_i].copy(students[i]);
			male_i++;
			break;
		case female:
			students_female[female_i].copy(students[i]);
			female_i++;
			break;
		default:
			students_undefined[undefined_i].copy(students[i]);
			undefined_i++;
		}
	}

	if (male_i > 0) {//выведем соответствующие массивы
		printf("\nMale gender:");
		printStudents(students_male, male_i);
	}
	if (undefined_i > 0) {
		printf("\nUndefined gender:");
		printStudents(students_undefined, undefined_i);
	}
	if (female_i > 0) {
		printf("\nFemale gender:");
		printStudents(students_female, female_i);
	}
	
	cleanNames(students, n);//очистим динамическую память
	system("pause");
	return 0;
}


const char* gender2String(GenderType gender) {//преобразование пола в строку
	switch (gender) {
	case female:
		return gender_str[0];
	case male:
		return gender_str[1];
	default:
		return gender_str[2];
	}
	return NULL;
}

void cleanNames(Student* students, int n) {//функция очистки имен из массивы типа Student, тк name являются динамическим массивом
	for (myuint i = 0; i < n; i++)
		delete[] students[i].name;
}

void printStudents(Student* students, myuint n) {//Объединим все имена в одну строку
	myuint total_len = 0;// Считаем новую длину строки

	for (myuint i = 0; i < n; i++)
		total_len += strlen(students[i].name);
	
	total_len += n - 1;// Учитываем пробелы между именами
	total_len += 1;// Учёт символа конца строки

	printf("\nTotal length: %d\n", total_len);
	
	char* total_str = new char[total_len];
	total_str[0] = 0;
	
	for (myuint i = 0; i < n; i++) {// Копирование имён
		if (i != 0)
			strcat(total_str, " ");
		strcat(total_str, students[i].name);
	}

	printf("Total string: %s (%d)\n", total_str, strlen(total_str));//вывод строки

	delete[] total_str;
}

//немного изменил структуру программы для удобства работы с ней