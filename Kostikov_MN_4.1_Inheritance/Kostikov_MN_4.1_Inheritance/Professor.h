#pragma once
#include "Person.h"


enum EmploymentType { part_time, full_time };
class Professor : public Person {
private:
	std::string department;
	EmploymentType employment_type;

	std::string type2string();

	Professor();
public:
	Professor(Person& person, std::string department, EmploymentType employment_type);
	Professor(std::string name, unsigned char age, std::string department, EmploymentType employment_type);

	void selfIntroduction();
	void toDo();

	~Professor() {}
};