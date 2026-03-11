#include "Student.h"


Student::Student(std::string name, unsigned char age, unsigned char course, std::string university)
	: Person(name, age), course(course), direction(university) {
}

void Student::selfIntroduction() {
	Person::selfIntroduction();
	std::cout << "I'm studying for " << direction << " at " << (int)course << " course."
		<< std::endl;
}

void Student::toDo() {
	std::cout << name << ": do my homework." << std::endl;
}