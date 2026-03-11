#pragma once
#include <string>
#include <iostream>


class Person {
protected:
	std::string name;
	unsigned char age;

	Person() {};
public:
	Person(std::string name, unsigned char age);

	virtual void selfIntroduction();
	virtual void toDo() = 0;

	virtual ~Person() {}
};