#include "Person.h"
#include "Professor.h"
#include "Student.h"
#include "PersonsArray.h"
#include <string>
#include <list>
// Используется виртуальность метода
void print(Person& person) {
	person.selfIntroduction();
}
// Не используется виртуальность метода
template<typename T>
void printAll(T* persons, int n) {
	for (int i = 0; i < n; i++)
		persons[i].selfIntroduction();
}

void printToDo(int n, Person** p) { //Выбран полиморфизм так каак это оптимальное решение для существующего массива p
	for (int i = 0; i < n; i++)
		p[i]->toDo();
}
int main() {
	// Число элементов массива
	const int n = 10;
	// Список имён
	std::string names[] = { "Ann", "John", "Kate", "Mike", "Susanne", "Peter" };
	// Список направлений обучения
	std::string directions[] = {
	"Technical Physics",
	"Radio Engineering",
	"Infocommunication Technologies and Communication Systems",
	"Electronics and Nanoelectronics" };
	// Список подразделений
	std::string departments[] = {
	"High School of Applied Physics and Space Technology",
	"High School of Electronics and Microsystem Technology",
	"High School of Engineering Physics" };
	// Создаём массив студентов
	// Выделяем память под масств
	Student* stud = (Student*)malloc(n * sizeof(Student));
	for (int i = 0; i < n; i++)
		// Создание экземпляра класса по заданному адресу
		new((void*)(stud + i)) Student(names[rand() % 6], rand() % 6 + 18, rand() % 4 + 1,
			directions[rand() % 4]);
	// Создаём массив преподавателей
	Professor* prof = (Professor*)malloc(n * sizeof(Professor));
	for (int i = 0; i < n; i++)
		new((void*)(prof + i)) Professor(names[rand() % 6], rand() % 30 + 25,
			departments[rand() % 3], (EmploymentType)(rand() % 2));
	// Работа с виртуальными методами
	std::cout << "Virtual methods" << std::endl;
	print(stud[0]);
	print(prof[0]);
	// Вывод информации о студентах через виртуальн
	std::cout << std::endl << "Template for function" << std::endl;
	printAll(stud, n);
	// Вывод информации о студентах
	printAll(prof, n);
	// Объединение студентов и преподавателей на основе класса человек
	Person** p = new Person * [2 * n];
	for (int i = 0; i < n; i++) {
		p[i] = &stud[i];
		p[n + i] = &prof[i];
	}
	// Работа с чисто виртуальным методом
	printToDo(2 * n, p);
	// Освобождение памяти
	for (int i = 0; i < n; i++) {
		stud[i].~Student();
		prof[i].~Professor();
	}
	free(stud);
	free(prof);

	std::cout << std::endl << std::endl;

	PersonsArray pp{ 10 };
	pp.pushStudent(new Student(names[rand() % 6], rand() % 6 + 18, rand() % 4 + 1, directions[rand() % 4]));
	pp.pushStudent(new Student(names[rand() % 6], rand() % 6 + 18, rand() % 4 + 1, directions[rand() % 4]));
	pp.pushProfessor(new Professor(names[rand() % 6], rand() % 30 + 25, departments[rand() % 3], (EmploymentType)(rand() % 2)));
	pp.print();
	pp.pop();
	std::cout << std::endl;
	pp.print();
	system("pause");
	return 0;
}