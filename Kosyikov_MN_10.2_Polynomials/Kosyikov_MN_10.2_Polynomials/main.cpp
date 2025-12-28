//7. Написать отдельную программу для работы с полиномами(многочленами)
//произвольной степени.Полином должен быть объявлен как шаблонная структура и
//поддерживать операции :
// сложения;
// присваивания;
// дифференцирования;
// получения коэффициента чере оператор[] с возможноостью изменения;
// вычисления значения в точке через оператор().
//Продемонстрировать работу структуры на примере работы с несколькими
//полиномами.

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>//для pow

template<typename T>
struct Polynomial {
	T* data;//массив коэффицентов
	int degree;//степень многочлена

	Polynomial(int n) : degree{n}, data(new T[n + 1]) {}//конструктор

	Polynomial(const Polynomial& m) : degree{m.degree}, data(new T[m.degree+1]){//конструктор копирования
		memcpy(data, m.data, sizeof(T) * (degree+1));
	}

	void free_mem() {//очистка памяти
		delete[] data;
	}

	~Polynomial() {//деструктор
		free_mem();
	}

	void fill(int max) {//заполнение массива коэффицентов рандомными значениями
		for (int i = 0; i < degree+1; i++)
			data[i] = (rand() % max);
	}

	void show() {//демонстрация полинома
		for (int i = degree; i > 0; i--)
			printf("%dx^(%d)+", data[i], i);
		printf("%d \n", data[0]);//свободный член
	}

	void diff() {//дифференцирование
		Polynomial<T> result(degree - 1);
		for (int i = 1; i < degree + 1; i++)
			result[i - 1] = (*this)[i] * i;

		*this = result;
	}

	T& operator[](int i) {//возвращаем по ссылке чтобы была возможность изменять значения
		return data[i];
	}

	Polynomial<T>& operator=(const Polynomial<T>& other) {//оператор присваивания
		if (this != &other) {
			free_mem();
			degree = other.degree;
			data = new T[degree + 1];
			memcpy(data, other.data, sizeof(T) * (degree + 1));
		}
		return *this;
	}

	Polynomial<T> operator+(Polynomial<T> other) {//оператор сложения
		int mm, mi;
		Polynomial<T> result(0);
		if (other.degree > this->degree) { 
			mm = other.degree;
			mi = this->degree;
			result = other;
		}
		else {
			mm = this->degree;
			mi = other.degree;
			result = (*this);
		}

		for (int i = 0; i < mi + 1; i++)
			result[i] = other[i] + (*this)[i];
		
		return result;
	}

	T operator()(int x) {//рассчет при конкретном x
		T s = 0;
		for (int i = 0; i < degree + 1; i++)
			s += (*this)[i] * pow(x, i);
		return s;
	}
};

int main() {
	Polynomial<int> a(4);
	a.fill(19);
	printf("A = ");
	a.show();
	a.diff();
	printf("A' = ");
	a.show();
	Polynomial<int> b(3);
	b.fill(5);
	printf("B = ");
	b.show();
	printf("B[1] = 0; B = ");
	b[1] = 0;
	b.show();
	Polynomial<int> c(b);
	printf("C = ");
	c.show();
	printf("C = C+B = ");
	c = c+b;
	c.show();
	printf("B(0) = %d\n", b(0));

	system("pause");
	return 0;
}