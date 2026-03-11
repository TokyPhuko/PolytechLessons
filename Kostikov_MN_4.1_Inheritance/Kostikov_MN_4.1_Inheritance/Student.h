#pragma once
#include "Person.h"


class Student : public Person {
private:
	unsigned char course;
	std::string direction;

	Student();
public:
	Student(std::string name, unsigned char age, unsigned char course, std::string university);

	void selfIntroduction();
	void toDo();

	~Student() {}
};