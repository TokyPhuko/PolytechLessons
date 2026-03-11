#include "Professor.h"

std::string Professor::type2string() {
	switch (employment_type)
	{
	case part_time:
		return "Part-time";
	case full_time:
		return "Full-time";
	default:
		return "";
	}
}

Professor::Professor(Person& person, std::string department, EmploymentType employment_type) :
	Person(person), department(department), employment_type(employment_type) {
}

Professor::Professor(std::string name, unsigned char age, std::string department, EmploymentType
	employment_type) :
	Person(name, age), department(department), employment_type(employment_type) {
}

void Professor::selfIntroduction() {
	Person::selfIntroduction();
	std::cout << "I'm working at " << department << " " << type2string() << std::endl;
}

void Professor::toDo() {
	std::cout << name << ": do research work." << std::endl;
}