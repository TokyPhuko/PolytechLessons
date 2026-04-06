//1. Написать шаблонную функцию, принимающую последовательный контейнер и
//выполняющую его сортировку с использованием итераторов(не используя
//	алгоритмы стандартной библиотеки);
//2. Перегрузить функцию из п. 1 функцией, где направление сортировки определяется
//с помощью функции сравнения элементов, переданной как указатель в качестве
//аргумента;


#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>

class FileNotFound {};
class IOError {};

template<typename T>
void print(T& container) {
	for (int i = 0; i < container.size(); i++)
		std::cout << container[i] << " ";
	std::cout << std::endl;
}

template<typename T>
void print2(T& container) {
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
	for (int i = 0; i < container.size() - 1; i++) {
		bool flag = false;
		
		for (int j = 0; j < container.size() - i - 1; j++) {
			if (compare(container[j], container[j + 1])) {
				swap(container[j], container[j + 1]);

				flag = true;
			}
		}

		if (!flag) {
			break;
		}
	}
}

// Switch to release
int main() {
	std::fstream file;
	std::vector<int> vec;

	if (vec.empty())
		std::cout << "Array is empty" << std::endl;

	try {
		file.open("in.txt");
		if (!file.is_open())
			throw FileNotFound();

		while (!file.eof()) {
			int val;
			file >> val;
			if (file.fail())
				throw IOError();
			vec.push_back(val);
		}

		std::cout << "front() = " << vec.front() << "; back() = " << vec.back() << "; size() = " << vec.size() << std::endl;

		/*try {
			std::cout << vec[vec.size() + 100] << std::endl;
			std::cout << "No exception in method []" << std::endl;
		}
		catch (...) {
			std::cout << "Catch" << std::endl;
		}*/

		try {
			vec.at(vec.size());
		}
		catch (std::out_of_range) {
			std::cout << "Exception in method at()" << std::endl;
		}

		print(vec);

		// Можно менять значения в контейнере как в массиве
		vec[2] = -10;
		vec.at(3) = -5;

		std::vector<int> to_remove = { 1, 4, 5 };
		std::array<int, 3> to_insert = { -1, -4, -5 };
		for (int i = 0; i < to_remove.size(); i++) {
			for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
				if (*it == to_remove.at(i)) {
					it = vec.erase(it);
					it = vec.insert(it, to_insert[i]);
					std::cout << to_remove.at(i) << " was deleted" << std::endl;
					std::cout << to_insert.at(i) << " was inserted" << std::endl;
				}
		}

		print2(vec);

		std::cout << "vector sort: ";
		sort(vec, [](int a, int b) {return a > b;});
		print(vec);

		vec.clear();
		std::cout << "Vector was cleared" << std::endl;
		print2(vec);

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