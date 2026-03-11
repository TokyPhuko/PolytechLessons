#include "Person.h"


Person::Person(std::string name, unsigned char age) {
	this->name = name;
	this->age = age;
}

void Person::selfIntroduction() {
	std::cout << "My name is " << name << ". I'm " << (int)age << " years old." <<
		std::endl;
}