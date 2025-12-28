//1. Использовать конструкторы для полей структуры в конструкторе копирования;
//2. Добавить перегруженные операторы сложения матрицы с числом и числа с
//матрицей.Один как метод структуры, другой – как глобальную функцию.Подумать
//самостоятельно, какую из перегрузок операторов реализовать первым, а какую
//вторым способом;
//3. Убрать в операторе умножения лишние вызовы конструктора копирования;
//4. Сделать перегруженный метод заполнения матрицы по указателю на функцию
//генерации чисел;
//5. Ввести в структуру метод set, который будет принимать три аргумента(строка,
//	столбец, значение) и записывать в эту ячейку матрицы переданное значение;
//6. Во всех методах и функциях использовать методы set и get вместо прямо
//обращения к элементам массива;


#include <stdio.h>
#include <stdlib.h>
#include <cstring>
// Объявляем шаблонную структуры для работы с матрицами
template <typename T> // Параметр-тип
struct Matrix {
	T* data; // Указатель для хранения матрицы в виде одномерного массива
	int row, column; // Размерность матрицы
	// Конструктор по умолчанию. Создаёт пустую матрицу
	// Используем конструкторы полей
	Matrix() : data(NULL), row(0), column(0) {}
	// Конструктор копирования. Создание одной матрицы из другой
	Matrix(const Matrix& m) : row(m.row), column(m.column), data(new T[m.row * m.column]) { // список инициализации
		printf("Invoke copy constructor\n");
		// Для простых типов можно просто сделать копию региона памяти
		memcpy(data, m.data, sizeof(T) * row * column);
	}
	void free_mem() {
		delete[] data;
	}
	// Деструктор
	~Matrix() {
		free_mem();
	}
	// Выделение памяти под матрицу заданной размерности
	void allocate(int r, int c) {
		row = r;
		column = c;
		data = new T[row * column];
	}
	// Выделение памяти под квадратную матрицу заданной размерности
	void allocate(int s) {
		allocate(s, s);
	}
	// Получение элемента матрицы по одномерному индексу (векторизация по строкам)
	T operator[](int i) {
		return data[i];
	}
	// Получение элемента матрицы по индексам
	T get(int i, int j) const {
		return data[i * column + j];
	}
	T set(int i, int j, T n) {//изменение значения по строке и столбцу
		data[i * column + j] = n;
		return data[i * column + j];
	}
	// Перегрузка оператора сложения в виде метода структуры
	Matrix<T> operator+(const Matrix<T> other) {
		// Проверка на совместимость размерностей
		if ((this->row != other.row) || (this->column != other.column)) {
			Matrix<T> a;
			return a; // Если операция некорректна, возвращаем пустую матрицу
		}
		Matrix<T> result(*this);
		for (int i = 0; i < this->row; i++)
			for (int j = 0; j < this->column; j++)
				result.set(i, j, this->get(i, j) + other.get(i, j));
		return result;
	}

	Matrix<T> operator+(const int& n) {//Матрица + число, сделано как метод структуры, тк оператор применяется именно к матрице
		Matrix<T> result(*this);
		for (int i = 0; i < this->row; i++)
			for (int j = 0; j < this->column; j++) {
				result.set(i, j, result.get(i, j) + n);//прибавляем ко всем элементам матрицы число.
			}
		return result;
	}
	// Перегрузка оператора присваивания
	Matrix<T>& operator=(const Matrix<T>& other) {
		// Проверка на самоприсваивание
		if (this != &other) {
			free_mem();
			allocate(other.row, other.column);
			memcpy(data, other.data, sizeof(T) * row * column);
		}
		return *this;
	}
	// Заполнение матрицы случайными числами
	void fill(int max) {
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				this->set(i, j, rand() % max);
	}

	void fill(T (*generator)()) { // Перегрузка fill для заполнения с помощью собственного генератора
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				this->set(i, j, generator());
	}
	// Вывод матрицы на экран
	void show() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++)
				printf("%d ", get(i, j));
			printf("\n");
		}
	}
	// Проверка на пустую матрицу
	bool is_empty() {
		return (data == NULL) && (row == 0) && (column == 0);
	}
};
template <typename T>
Matrix<T> operator+(const int n, const Matrix<T> mat) {//функция число + матрица
	Matrix<T> result(mat);
	for (int i = 0; i < mat.row; i++)
		for (int j = 0; j < mat.column; j++) {
			result.set(i, j, result.get(i, j) + n);
		}
	return result;
}

// Перегрузка оператора умножения матриц в виде шаблонной глобальной функций
template <typename T>
Matrix<T> operator*(const Matrix<T>& left, const Matrix<T>& right) {// передаем по ссылке
	Matrix<T> result; // Вернули пустую матрицу
	if (left.column == right.row) {
		result.allocate(left.row, right.column);
		for (int i = 0; i < left.row; i++)
			for (int j = 0; j < right.column; j++) {
				T sum = 0;
				for (int k = 0; k < left.column; k++)
					sum += left.get(i, k) * right.get(k, j);
				result.set(i, j, sum);
			}
	}
	return result;
}
template <typename T>
void checkMatrix(Matrix<T>* a) {
	if (a->is_empty())
		printf("Matrix is empty.\n");
	else
		printf("Matrix is NOT empty.\n");
}
int main() {
	Matrix<int> a, b; // Объявление матриц с целыми числами
	checkMatrix<int>(&a); // Проверка корректной работы checkMatrix
	a.allocate(5, 4); // Выделение памяти под матрицу
	b.allocate(4, 5); // Выделение памяти под матрицу
	checkMatrix<>(&a); // Явное указание параметра шаблона можно опускать
	// Заполнение матриц числами
	a.fill(3);
	b.fill(3);
	// Вывод матриц на экран
	printf("Matrix a is:\n");
	a.show();
	printf("Matrix b is:\n");
	b.show();
	// Проверка работы конструктора копирования
	{
		Matrix<int> c(a);
		printf("Matrix c (copy of a) is:\n");
		c.show();
	}
	// Проверка оператора сложения
	{
		Matrix<int> c;
		c.allocate(5, 4);
		c.fill(5);
		// Вызов метода show для анонимного объекта
		printf("Matrix(a + c) is:\n");
		(a + c).show();
		// Вызов конструктора копирования для анонимного объекта
		Matrix<int> d(a + c);
		printf("Matrix d(a + c) is:\n");
		d.show();
	}
	// Проверка оператора присваивания
	{
		Matrix<int> c;
		c = a;
		printf("Matrix c is:\n");
		c.show();
	}
	// Проверка шаблонной функции умножения
	Matrix<int> c;
	c = a * b;
	if (c.is_empty())
		printf("Multiplication failed!\n");
	else {
		printf("Matrix c=a*b is:\n");
		c.show();
	}
	// Проверка шаблонных функции сложения матрицы с числом и числа с матрицей
	c = 3 + a;
	if (c.is_empty())
		printf("Multiplication failed!\n");
	else {
		printf("Matrix c=3+a is:\n");
		c.show();
	}

	c = c + 3;
	if (c.is_empty())
		printf("Multiplication failed!\n");
	else {
		printf("Matrix c=c+3 is:\n");
		c.show();
	}
	// Проверка перегрузки fill для собственного генератора
	c.fill(rand() % 400);
	if (c.is_empty())
		printf("Multiplication failed!\n");
	else {
		printf("Matrix c fill is:\n");
		c.show();
	}
	system("pause");
	return 0;
}