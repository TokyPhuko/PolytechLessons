/*1. Решить проблему того, что красный и синий цвета имеют одинаковое числовое
значение;
2. Решить проблему того, что квадрат никогда не выпадает;
3. Ввести в перечисляемые типы значения, которые будут присваиваться в секции
default. Продемонстировать обработку таких случаев;
4. Добавить в перечисляемые типы шестиугольник и жёлтый цвет;
5. Добавить функцию, которая будет перекрашивать фигуру в другой цвет и
продемонстирировать её работу;
6. Сделать вывод информации о цвете и типе фигуры в текстовом виде вместо
числового;*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// Вводим новые перечисляемые типы
enum Shape { Triangle, Square, Circle, Hexagon, Tomahawk };
enum Color { Red, Green, Blue, Yellow, Aquamarine };
// Вводим новое обозначение типа
typedef void (*Print_fun)();

// Вводим структуру
struct Figure {
	Shape shape;
	Color color;
	Print_fun print_shape;//сделаем отдельные функции для вывода формы и цвета
	Print_fun print_color;
	void change_color(Color c) {//сделаем функцию для изменения цвета
		color = c;
	};
};
// Выбор формы для фигуры
Shape get_shape(int s) {
	switch (s) {
	case 0:
		return Triangle;
	case 1:
		return Square;
	case 2:
		return Circle;
	case 3:
		return Hexagon;
	default:
		return Tomahawk;
	}
}
// Выбор цвета для фигуры
Color get_color(int s) {
	switch (s) {
	case 0:
		return Red;
	case 1:
		return Green;
	case 2:
		return Blue;
	case 3:
		return Yellow;
	default:
		return Aquamarine;
	}
}
// Функции представления фигуры
void print_triangle() {
	printf("I'm Triangle ");
}
void print_square() {
	printf("I'm Square ");
}
void print_circle() {
	printf("I'm Circle ");
}
void print_tomahawk() {
	printf("I'm Tomahawk ");
}
void print_hexagon() {
	printf("I'm Hexagon ");
}
// Функции цвета фигуры
void print_red() {
	printf("Red\n");
}
void print_green() {
	printf("Green\n");
}
void print_blue() {
	printf("Blue\n");
}
void print_yellow() {
	printf("Yellow\n");
}
void print_aquamarine() {
	printf("Aquamarine\n");
}
//функция выбора функции представления формы фигуры
Print_fun get_print_shape_fun(Shape shape) {
	switch (shape) {
	case Triangle:
		return print_triangle;
	case Square:
		return print_square;
	case Circle:
		return print_circle;
	case Hexagon:
		return print_hexagon;
	default:
		return print_tomahawk;
	}
}
//функция выбора функции представления цвета фигуры
Print_fun get_print_color_fun(Color color) {
	switch (color) {
	case Red:
		return print_red;
	case Green:
		return print_green;
	case Blue:
		return print_blue;
	case Yellow:
		return print_yellow;
	default:
		return print_aquamarine;
	}
}
int main() {
	// Смотрим, что чему равно
	printf("Test color values. Red - %d; green - %d; blue - %d; yellow - %d.\n", Red, Green, Blue, Yellow);
	printf("Test shape values. Triangle - %d; Square - %d; circle - %d; hexagon - %d.\n", Triangle, Square, Circle, Hexagon);
	// Получаем размер массива int n;
	int n;
	printf("Enter aaray size: ");
	scanf_s("%d", &n);
	// Создаём и заполняем массив
	Figure* arr = new Figure[n];
	for (int i = 0; i < n; i++) {
		arr[i].color = get_color(rand() % 4);//передаем число от 1 до 3, а не от 1 до 2
		arr[i].shape = get_shape(rand() % 4);
		arr[i].print_shape = get_print_shape_fun(arr[i].shape);//выберем функцию представления формы взависимости от формы
		arr[i].print_color = get_print_color_fun(arr[i].color);//без комметариев
	}
	// Вывод массива на экран
	for (int i = 0; i < n; i++) {
		printf("Figure %d: ", i);
		arr[i].print_shape();//выведем форму фигуры
		arr[i].print_color();//выведем цвет фигуры
	}
	printf("\nChange 0 figure color to Aquamarine\n\n");
	arr[0].change_color(Aquamarine);//вызрвем метод измения цвета для 0 элементя
	arr[0].print_color = get_print_color_fun(arr[0].color);//изменим функцию представления цвета,в связи со сменой цветаб заодно продемонстрируем присвоение из секции default
	// Вывод массива на экран
	for (int i = 0; i < n; i++) {//опять вывелем все элементы массива
		printf("Figure %d: ", i);
		arr[i].print_shape();
		arr[i].print_color();
	}

	delete[] arr;
	system("pause");
	return 0;
}