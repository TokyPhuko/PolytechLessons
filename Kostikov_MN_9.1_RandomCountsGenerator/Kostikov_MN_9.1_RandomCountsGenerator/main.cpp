//1. Добавить глобальную функцию, которая внутри себя формирует массив, хранящий
//всю последовательность случайных чисел, и возвращает этот массив(функция не должна иметь входных аргументов и не должна использовать статические
//	переменные);
//2. Создать структуру RandomGenerator и скопировать туда функцию myRandom и перенести
//функцию из п. 1;
//3. Перенести состояние регистра из функции myRandom в поля структуры RandomGenerator;


#include <iostream>


struct BitMap {// Структура для обеспечания побитного доступа к данным
	// unsigned char - 1 байт = 8 бит
	unsigned char b1 : 1; // 1-ый бит числа типа unsigned char
	unsigned char b2 : 1; // 2-ой бит числа типа unsigned char
	unsigned char b3 : 1; // 3-ий бит числа типа unsigned char
	unsigned char b4 : 1; // 4-ый бит числа типа unsigned char
	unsigned char b5 : 1; // 5-ый бит числа типа unsigned char
	unsigned char b6 : 1; // 6-ой бит числа типа unsigned char
	unsigned char b7 : 1; // 7-ой бит числа типа unsigned char
	unsigned char b8 : 1; // 8-ой бит числа типа unsigned char
};

union Register {// Создаём тип для регистра
	BitMap map; // Побитный доступ к регистру
	unsigned char value; // Доступ к регистру как к целому числу
	// С помощью конструктора по умолчанию инициализируем регистр
	Register() {
		value = 1;
	}
};

struct RandomGenerator {//создаем структуру
	int* mass;
	Register reg;

	RandomGenerator() {//конструктор
		mass = new int[255]; //создаем динамический массив чтобы он мог храниться до того пока мы его не удалим. в массиве будет ровно 255 уникальных элементов
	}

	unsigned char myRandom() {//перенесенный метод
		Register inter = reg;
		reg.value <<= 1;
		reg.map.b1 = inter.map.b4 ^ inter.map.b5 ^ inter.map.b6 ^ inter.map.b8;

		return reg.value;
	}

	int* randMass() {//перенесенный метод
		for (int i = 0; i < 255; i++) {
			mass[i] = (int)(myRandom());
		}

		return mass;
	}

	~RandomGenerator() {//деструктор
		delete[] mass;//очистка памяти
	}
};


unsigned char myRandom();// Функция генерации следующего числа случайной последовательности
int* randMass();


int main() {
	unsigned char a = myRandom(), b = 0;

	std::cout << "a = " << (int)a << std::endl << std::endl;
	std::cout << "Start generating... " << std::endl;

	int i = 0;

	while (b != a) {
		std::cout << (int)(b = myRandom()) << std::endl;
		i++;
	}

	std::cout << std::endl << "Sequence length is " << i << std::endl;

	system("pause");
	return 0;
}


unsigned char myRandom() {
	static Register reg;// Статическая переменная живёт до окончания программы, а не функции
	Register inter = reg;
	reg.value <<= 1;
	reg.map.b1 = inter.map.b4 ^ inter.map.b5 ^ inter.map.b6 ^ inter.map.b8;// В данном примере предполагается массив коэффициентов b1 -> b8 - {0, 0, 0, 1, 1, 1, 0, 1}

	return reg.value;
}

int* randMass() {//функция создания массива рандомных значений
	int* mass = new int[255];//динамический массив значений. мы его нигде не удаляем, тк и функцию нигде не вызываем

	for (int i = 0; i < 255; i++) {//записываем все возможные 255 значений в массив
		mass[i] = (int)(myRandom());
	}

	return mass;
}