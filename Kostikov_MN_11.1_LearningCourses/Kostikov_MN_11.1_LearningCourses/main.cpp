//1. Сделать вывод типа оценки в текстовом виде;
//2. Добавить в структуру конструктор по умолчанию, коструктор копирования и
//оператор присваивания, конструктор с параметрами и деструктор;
//3. Массив курсов сделать динамическим(размер вводит пользователь) и заполнять его
//случайным образом;
//4. Записывать в текстовом виде массив курсов, а не один курс;
//5. Добавить в структуру метод записи курса в файл в текстовом виде;

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
// Объявляем тип аттестации
enum MarkType { Credit, Diff_Credit, Exam };
// Структура для учебного курса
struct Course {
	char* name; // Название
	MarkType mark_type; // Тип аттестации
	unsigned char semester; // Семестр
	float average_grade; // Средний балл

	Course() : name(nullptr), mark_type(Credit), semester(0), average_grade(0) {}//конструктор по умолчанию

	Course(char* name, MarkType mark_type, unsigned char semester, float average_grade) : mark_type(mark_type), semester(semester), average_grade(average_grade) {//конструктор с параметрами
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

	Course(Course& course) : mark_type(course.mark_type), semester(course.semester), average_grade(course.average_grade) {//конструктор копирования
		if (course.name != nullptr) {
			name = new char[strlen(course.name) + 1];
			strcpy(this->name, course.name);
		}
		else {
			name = nullptr;
		}
	}

	Course& operator=(const Course& other) {//оператор присваивания
		delete[] name;
		if (other.name != nullptr) {
			name = new char[strlen(other.name) + 1];
			strcpy(this->name, other.name);
		}
		else {
			name = nullptr;
		}
		mark_type = other.mark_type;
		semester = other.semester;
		average_grade = other.average_grade;
		return *this;
	}

	~Course() {//деструктор
		delete[] name;
	}
	
	char* stringMarkType() {//преобразование типа оценки в текст
		switch (mark_type) {
			case Credit: return (char*)"Credit";
			case Diff_Credit: return (char*)"Diff credit";
			case Exam: return (char*)"Exam";
		}
	}
	// Вывод курса на экран
	void print() {
		printf("Name: %s; Mark type: %s, Semester: %d; Average grade: %f\n", name,
			stringMarkType(), semester, average_grade);
	}
	// Запись курса в двоичном виде
	void toFile(FILE* file) {
		fputs(name, file);
		// В случае успешного выполнения возвращается неотрицательно значение.
		// В случае ошибки – специальное значение EOF (end of file).
		fputc('\0', file);
		// В случае успешной записи возвращается код записанного в файл символа.
		// В случае ошибки – специальное значение EOF (end of file).
		fwrite(&mark_type, sizeof(MarkType), 1, file);
		// Функция возвращает число успешно записанных элементов
		fwrite(&semester, sizeof(semester), 1, file);
		fwrite(&average_grade, sizeof(average_grade), 1, file);
	}

	void toTextFile(FILE* file) {//преобразование в текст данных курса
		char buffer[200];
		// Создаём строку с данными по формату
		sprintf(buffer, "%s; %s; %d; %f\n", name, stringMarkType(), semester, average_grade);
		// Запись строки в файл
		fputs(buffer, file);
	}
	// Чтение курса в двоичном виде статическим методом
	static Course fromFile(FILE* file) {
		// Создаём экзамляр, куда будет рассортировывать данные
		Course course;
		// Создаём буфер для чтения названия
		const int buffer_size = 50;
		char* buffer = new char[buffer_size];
		// Чтение названия
		char ch;
		int i = 0;
		do {
			ch = fgetc(file);
			// В случае успеха функция возвращает код считанного из файл символа.
			// В случае ошибки или достижения конца файла – специальное значение EOF (end of file).
			buffer[i++] = ch;
		} while (ch != '\0'); // Пока не встретим символ конца строки
		// Копируем из буфера в поле структуры
		course.name = new char[strlen(buffer) + 1];
		strcpy(course.name, buffer);
		// Удаляем буфер
		delete[] buffer;
		// Читаем остальные поля
		fread(&course.mark_type, sizeof(MarkType), 1, file);
		// Функция возвращает число успешно считанных элементов.
		fread(&course.semester, sizeof(semester), 1, file);
		fread(&course.average_grade, sizeof(average_grade), 1, file);
		// Возвращаем заполненный курс
		return course;
	}
};

int main() {
	// Объявляем массив структур
	int n;
	Course* courses;
	printf("Enter the len of array: ");
	scanf("%d", &n);//вводим длину массива курсов
	courses = new Course[n];
	const char* subjects[] = { "Mathematics", "Informatics", "Physics" };
	for (int i = 0; i < n; i++) {//рандомно заполняем его
		courses[i] = Course((char*)(subjects[rand()%3]), (MarkType)(rand() % 3), (rand()%8)+1, (rand()%41)/10.0 + 1);
	}
	// Запись массива в двоичном виде
	{
		// Открытие файла
		FILE* file = fopen("bin.txt", "w");
		// Запись размера массива
		fwrite(&n, sizeof(n), 1, file);
		// Записываем курсы
		for (int i = 0; i < n; i++)
			courses[i].toFile(file);
		// Закрытие файла
		fclose(file);
	}
	// Чтение массива в двоичном виде
	{
		FILE* file = fopen("bin.txt", "r");
		// Чтение размера массива
		int n;
		fread(&n, sizeof(n), 1, file);
		Course* courses_new = new Course[n];
		// Чтение курсов
		for (int i = 0; i < n; i++)
			courses_new[i] = Course::fromFile(file);
		fclose(file);
		// Вывод прочитанных курсов на экран
		for (int i = 0; i < n; i++)
			courses_new[i].print();
		delete[] courses_new;
	}
	// Запись курса в текстовом виде (несколькиз курсов)
	{
		FILE* file = fopen("text.txt", "w");
		for (int i = 0; i < n; i++) {
			courses[i].toTextFile(file);
		}
		fclose(file);
	}
	// Чтение содержиомого файла
	{
		FILE* file = fopen("text.txt", "r");
		while (!feof(file)) // Пока не дойдём до конца файла
			putchar(fgetc(file)); // читаем символ и выводим его на экран
		fclose(file);
	}

	Course a;//проверка конструкторов
	Course b(a);
	Course c;
	c = a;

	delete[] courses;//чистим память
	system("pause");
	return 0;
}