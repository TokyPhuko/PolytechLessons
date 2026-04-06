//3. Написать отдельную программу, которая будет считывать из текстового файла
//вещественные числа и сохранять их в список std::list.Далее выполняет его
//сортировку с помощью функции из п. 1 и записывает минимальный и максимальный
//элементы в другой текстовый файл.


#include <iostream>
#include <string>
#include <array>
#include <list>
#include <fstream>

class FileNotFound {};
class IOError {};

template<typename T>
void findAndSaveMinMaxMid(T& container) {
	if (!container.empty()) {
		typename T::iterator it = container.begin();

		typename T::value_type mid = 0;
		typename T::value_type min = *it;
		typename T::value_type max = *it;
		it++;

		for (it; it != container.end(); it++) {
			mid += *it;

			if (*it < min) {
				min = *it;
			}

			if (*it > max) {
				max = *it;
			}
		}

		mid /= container.size();

		try {
			std::ofstream out;
			out.open("out.txt");
			if (!out.is_open())
				throw FileNotFound();

			out << "mid " << mid << "\n" << "min " << min << "\n" << "max " << max << "\n";
			out.close();
		}
		catch (FileNotFound) {
			std::cout << "File not found" << std::endl;
		}
	}
	else {
		std::cout << "List is empty" << std::endl;
	}
}


template<typename T>
void print(T& container) {
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template<typename T>
void swap(T& a, T& b) {
	T z = a;
	a = b;
	b = z;
}

template<typename T>
void sort(T& container, bool (*compare) (typename T::value_type a, typename T::value_type b)) {
	if (container.size() <= 1) return;

	T left, right;
	typename T::iterator it = container.begin();
	int mid = container.size() / 2;

	for (int i = 0; i < mid; ++i) {
		left.splice(left.end(), container, it++);
	}
	right.splice(right.end(), container, container.begin(), container.end());

	sort(left, compare);
	sort(right, compare);

	left.merge(right, compare);
	container.merge(left, compare);
}

// Switch to release
int main() {
	std::fstream file;
	std::list<float> li;

	if (li.empty())
		std::cout << "List is empty" << std::endl;

	try {
		file.open("in.txt");
		if (!file.is_open())
			throw FileNotFound();

		while (!file.eof()) {
			float val;
			file >> val;
			if (file.fail())
				throw IOError();
			li.push_back(val);
		}

		std::cout << "front() = " << li.front() << "; back() = " << li.back() << "; size() = " << li.size() << std::endl;

		print(li);

		std::cout << "List sort: ";
		sort(li, [](float a, float b) {return a > b;});
		print(li);

		findAndSaveMinMaxMid(li);

		li.clear();
		std::cout << "List was cleared" << std::endl;
		print(li);

		file.close();
	}
	catch (FileNotFound) {
		std::cout << "File not found" << std::endl;
	}
	catch (IOError f) {
		std::cout << "Read/write error" << std::endl;
		file.close();
	}

	return 0;
}