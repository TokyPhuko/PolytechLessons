#pragma once
#include <string>
#include <deque>
#include <map>

class Student {
private:
	std::string name;
	std::string group_number;
	std::map<std::string, int> marks;

public:
	Student(std::string& name, std::string& group_number);

	std::string getName() const;
	std::string getGroupNumber() const;
	std::map<std::string, int>& getMarks();
	int getMark(std::string sub);
	float getMidMark() const;

	bool operator<(const Student& other) const;

	void print() const;
};