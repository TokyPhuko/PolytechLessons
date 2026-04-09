#include <iostream>
#include "Student.h"

Student::Student(std::string& name, std::string& group_number) {
	this->name = name;
	this->group_number = group_number;
}

std::string Student::getName() const {
	return name;
}

std::string Student::getGroupNumber() const {
	return group_number;
}

std::map<std::string, int>& Student::getMarks() {
	return marks;
}

int Student::getMark(std::string sub) {
	return this->marks[sub];
}

float Student::getMidMark() const {
	float mid_mark = 0;

	for (auto it = marks.begin(); it != marks.end(); it++) {
		mid_mark += static_cast<float>(it->second);
	}

	mid_mark /= marks.size();

	return mid_mark;
}

bool Student::operator< (const Student& other) const {
	return (this->getMidMark() < other.getMidMark());
}

void Student::print() const {
	std::cout << name << "; group: " << group_number << "; marks: ";
	for (auto it = marks.begin(); it != marks.end(); it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}

	std::cout << std::endl;
}
