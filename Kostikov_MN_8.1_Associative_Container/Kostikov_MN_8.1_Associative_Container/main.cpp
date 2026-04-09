//1. ¬вести в класс студента метод расчЄта средней оценки студента;
//2. —оздать multiset, где критерием сравнени€ будет средн€€ оценка студента;
//3. ’ранение оценок сделать в map вместо deque. люч Ц название предмета;
//4. —формировать multimap, где ключ Ц название предмета, а значени€ Ц студенты, не
//сдавшие предмет.

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>		// std::map, std::multimap
#include <set>		// std::set, std::multiset
#include <utility>	// std::pair

#include "Student.h"

int main()
{
	// Source data
	const int n_students = 30, n_marks = 5;
	std::array<std::string, 20> names = {
		// Male names
		"James", "John", "Robert", "Michael", "William",
		"David", "Richard", "Joseph", "Thomas", "Charles",
		// Female names
		"Emma", "Olivia", "Sophia", "Isabella", "Ava",
		"Mia", "Charlotte", "Amelia", "Harper", "Evelyn"
	};

	std::array<std::string, 5> subjects = {
		"Programming Basics", "Financial Literacy", "English Language", 
		"Cognitive Psychology", "Statistics and Data Analysis"
	};
	std::array<std::string, 3> groups = { "4931104/50001", "4931104/50002", "4931104/50003" };

	// Create students
	std::vector<Student> all_students;
	all_students.reserve(n_students);
	for (int i = 0; i < n_students; i++) {
		Student s(names[rand() % 20], groups[rand() % 3]);
		std::map<std::string, int>& marks = s.getMarks();
		for (int j = 0; j < n_marks; j++) {
			std::pair<std::string, int> p(subjects[j], rand() % 6);
			marks.insert(p);
		}
		all_students.push_back(s);
	}

	// Sort students by group
	std::cout << "----- Multimap -----" << std::endl;
	std::multimap<std::string, Student> map_by_group;
	for (std::vector<Student>::iterator it = all_students.begin(); it != all_students.end(); it++)
		map_by_group.insert(std::pair<std::string, Student>(it->getGroupNumber(), *it));

	// Print multimap
	for (std::multimap<std::string, Student>::iterator it = map_by_group.begin(); it != map_by_group.end(); it++)
		it->second.print();
	for (int i = 0; i < groups.size(); i++)
		std::cout << "Number of students in group " << groups[i] << ": " << map_by_group.count(groups[i]) << std::endl;

	// Get unique names in each group
	std::map<std::string, std::set<std::string>> unique_names_by_group;
	for (int i = 0; i < groups.size(); i++) {
		auto range = map_by_group.equal_range(groups[i]);
		std::set<std::string> unique_names;
		for (auto it = range.first; it != range.second; it++)
			unique_names.insert(it->second.getName());
		unique_names_by_group.insert(std::pair<std::string, std::set<std::string>>(groups[i], unique_names));
	}

	// Show unique name in groups
	std::cout << std::endl << "----- Unique names -----" << std::endl;
	for (int i = 0; i < groups.size(); i++) {
		std::cout << "Group: " << groups[i] << std::endl;
		std::set<std::string>& s = unique_names_by_group[groups[i]];
		for (std::set<std::string> ::iterator it = s.begin(); it != s.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	auto comp = [](const Student& a, const Student& b) -> bool {
		return a.getGroupNumber() < b.getGroupNumber();
		};
	std::cout << std::endl << "----- Custom key in set -----" << std::endl;
	std::multiset<Student, decltype(comp)> custom_compare(comp);
	for (auto it = all_students.begin(); it != all_students.end(); it++)
		custom_compare.insert(*it);
	for (auto it = custom_compare.begin(); it != custom_compare.end(); it++)
		it->print();

	std::cout << std::endl << "Mid marks for each student" << std::endl;
	for (int i = 0; i < groups.size(); i++) {
		auto range = map_by_group.equal_range(groups[i]);
		std::cout << groups[i] << std::endl;
		for (auto it = range.first; it != range.second; it++)
			std::cout << it->second.getName() << " " << it->second.getMidMark() << std::endl;
	}

	std::multiset<Student> valhalla_table;
	for (auto it = all_students.begin(); it != all_students.end(); it++)
		valhalla_table.insert(*it);

	std::cout << "\nMultiset data: \n";
	for (auto it = valhalla_table.begin(); it != valhalla_table.end(); it++)
		std::cout << it->getName() << ' ' << it->getMidMark() << "\n";

	std::multimap<std::string, Student> nee_sdaliii;
	
	for (auto it = all_students.begin(); it != all_students.end(); it++) {
		for (auto sub : subjects) {
			if (it->getMark(sub) <= 2) {
				std::pair<std::string, Student> p(sub, *it);
				nee_sdaliii.insert(p);
			}
		}
	}

	std::cout << "Neee SDALII: \n";
	for (auto it = nee_sdaliii.begin(); it != nee_sdaliii.end(); it++)
		std::cout << it->first << " " << it->second.getName() << ' ' << it->second.getMark(it->first) << std::endl;

	return 0;
}