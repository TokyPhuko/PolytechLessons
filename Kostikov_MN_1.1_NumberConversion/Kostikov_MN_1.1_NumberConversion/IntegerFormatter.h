#pragma once
#include <iostream>
// Our format for number: <radix>r<number presentation>
template<typename T>
class IntegerFormatter {
private:
	T number;
	char radix;
	void upper(char* str);
public:
	IntegerFormatter();
	IntegerFormatter(T number);
	IntegerFormatter(T number, char radix);
	IntegerFormatter(const char* str);
	// Getter & setter for number
	T get();
	void set(T number);
	char operator[](int pos);
	// Getter & setter for radix
	char getRadix();
	void setRadix(char radix);
	// Conversion functions
	void from(const char* str);
	char* to();
	// Others
	void print();
	// Friend functions for arithmetic operations
	friend IntegerFormatter<T>& operator+(int left, IntegerFormatter<T>& formmater);
	friend IntegerFormatter<T>& operator-(int left, IntegerFormatter<T>& formmater);
	friend IntegerFormatter<T>& operator+(IntegerFormatter<T>& left, IntegerFormatter<T>& formmater);
	friend IntegerFormatter<T>& operator-(IntegerFormatter<T>& left, IntegerFormatter<T>& formmater);
};
// Global functions
template<typename T>
std::ostream& operator<<(std::ostream& stream, IntegerFormatter<T>& formmater);
template<typename T>
std::istream& operator>>(std::istream& stream, IntegerFormatter<T>& formmater);

template class IntegerFormatter<int>; //явная инстанцировка для используемого в примерах типа, чтобы избежать ошибок линковщика и не выносить реализацию в текущий файл (как это сделано с Converts.h)
template std::ostream& operator<<(std::ostream&, IntegerFormatter<int>&);
template std::istream& operator>>(std::istream&, IntegerFormatter<int>&);