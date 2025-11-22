//Написать отдельную программу, где структура RandomGenerator будет содержать
//массив коэффициентов генератора.Метод myRandom и используется этот массив
//коэффициентов для формирования значения нового бита.Массив коэффициентов
//содержит 0 или 1: «1» бит участвует в формировании нового состояния, «0» – нет.
//Массив коэффициентов должен быть назначен генератору при создании
//переменной с помощью конструктора.Создать и проверить 3 генератора со
//следующими массивами коэффициентов(включая массив из первой части задания) :
//{0, 1, 1, 1, 0, 0, 0, 1}
//{ 1, 0, 0, 0, 1, 1, 0, 1 }

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
	int ratios[8] = { 0, 0, 0, 1, 1, 1, 0, 1 }; //значение по умолчанию для массива коэффицентов
	int count_mass_elements = 0;
	Register reg;
	Register inter = reg;

	unsigned char myRandom() {
		inter = reg;
		reg.value <<= 1;
		unsigned char z = 0;//инициализируем нулем тк 0 не влияет на результат xor (0^1=1 и 0^0=0)

		for (int i = 0; i < 8; i++) {//перебираем коэффиценты и ксорим нужные
			if (ratios[i] == 1) {
				switch (i + 1) {
				case 1: z ^= inter.map.b1; break;//ксорим необходимые значения
				case 2: z ^= inter.map.b2; break;
				case 3: z ^= inter.map.b3; break;
				case 4: z ^= inter.map.b4; break;
				case 5: z ^= inter.map.b5; break;
				case 6: z ^= inter.map.b6; break;
				case 7: z ^= inter.map.b7; break;
				case 8: z ^= inter.map.b8; break;
				}
			}
		}

		reg.map.b1 = z;//меняем младший бит
		
		return reg.value;
	}

	int* randMass() {
		int a = (int)(myRandom());
		int b = 0;

		while (b != a) {//изначально мы не знаем сколько раз необходимо произвести сдвиг, чотбы замкнуть цикл (перебрать все возможные значения и вернуться к первому)
			b = (int)(myRandom());//поэтому перебираем элементы, ищем когда произойдет совпадение и фиксируем count_mass_elements длину неоходимого массива
			count_mass_elements++;
		}

		mass = new int[count_mass_elements];//создаем массив

		for (int i = 0; i < count_mass_elements; i++) {
			mass[i] = (int)(myRandom());//добавляем элементы
		}

		return mass;
	}

	~RandomGenerator() {//деструктор
		delete[] mass;//очистка памяти
	}
};


int main() {
	RandomGenerator r; //создаем элемент структуры
	int ratios1[8] = { 0, 0, 0, 1, 1, 1, 0, 1 };//массивы коэффицентов
	int ratios2[8] = { 0, 1, 1, 1, 0, 0, 0, 1 };
	int ratios3[8] = { 1, 0, 0, 0, 1, 1, 0, 1 };

	memcpy(r.ratios, ratios1, 8*sizeof(int));//копируем необходимый массив коэффицентов в элемент структуры
	r.randMass();//генерируем наш массив
	std::cout << "Start generating... " << std::endl;

	for (int i = 0; i < r.count_mass_elements; i++)
		std::cout << r.mass[i] << std::endl;//выводим

	std::cout << std::endl << "Sequence length is " << r.count_mass_elements << std::endl;

	RandomGenerator r2;//аналогично вышеописанным операциям
	memcpy(r2.ratios, ratios2, 8 * sizeof(int));
	r2.randMass();
	std::cout << "Start generating... " << std::endl;

	for (int i = 0; i < r2.count_mass_elements; i++)
		std::cout << r2.mass[i] << std::endl;

	std::cout << std::endl << "Sequence length is " << r2.count_mass_elements << std::endl;

	RandomGenerator r3;
	memcpy(r3.ratios, ratios3, 8 * sizeof(int));
	r3.randMass();
	std::cout << "Start generating... " << std::endl;

	for (int i = 0; i < r3.count_mass_elements; i++)
		std::cout << r3.mass[i] << std::endl;

	std::cout << std::endl << "Sequence length is " << r3.count_mass_elements << std::endl;

	system("pause");
	return 0;
}