#include "PersonsArray.h"


PersonsArray::PersonsArray() : size(0), array(nullptr) {};

PersonsArray::PersonsArray(int size) : size(size), currenSize(0) {
	array = new Person*[size];
}

void PersonsArray::allocate(int size) {
	this->clean();

	this->currenSize = 0;
	this->size = size;
	this->array = new Person*[size];
}

void PersonsArray::clean() {
	if (array != nullptr) {
		for (int i = 0; i < currenSize; i++)
			this->array[i]->~Person();
		delete[] this->array;
	}
	this->array = nullptr;
}

void PersonsArray::pushStudent(Student* s) {
	if (currenSize < size) {
		this->array[currenSize] = s;
		++this->currenSize;
	}
}

void PersonsArray::pushProfessor(Professor* s) {
	if (currenSize < size) {
		this->array[currenSize] = s;
		++this->currenSize;
	}
}

void PersonsArray::pop() {
	--this->currenSize;
	this->array[this->currenSize]->~Person();
}

void PersonsArray::print() {
	for (int i = 0; i < this->currenSize; ++i)
		this->array[i]->toDo();
}