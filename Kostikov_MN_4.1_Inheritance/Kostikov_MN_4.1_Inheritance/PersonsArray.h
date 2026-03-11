#pragma once
#include "Person.h"
#include "Student.h"
#include "Professor.h"

class PersonsArray {
	Person** array;
	int size;
	int currenSize;
public:
	PersonsArray();
	PersonsArray(int size);

	void allocate(int size);
	void clean();
	void pushStudent(Student* s);
	void pushProfessor(Professor* s);
	void pop();
	void print();
};