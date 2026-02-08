#include "IntegerFormatter.h"
#include <numeric> // C-string, memcpy, itoa
#include <stdio.h> // printf
#include <ctype.h> // toupper
#include "Converts.h"
template<typename T>
IntegerFormatter<T>::IntegerFormatter() {
	number = 0;
	radix = 0;
}
template<typename T>
IntegerFormatter<T>::IntegerFormatter(T number) {
	this->number = number;
	this->radix = 10;
}
template<typename T>
IntegerFormatter<T>::IntegerFormatter(T number, char radix) {
	this->number = number;
	this->radix = radix;
}
template<typename T>
IntegerFormatter<T>::IntegerFormatter(const char* str) {
	from(str);
}
template<typename T>
void IntegerFormatter<T>::upper(char* str) {
	for (int i = 0; i < strlen(str); i++)
		str[i] = toupper(str[i]);
}
template<typename T>
T IntegerFormatter<T>::get() {
	return number;
}
template<typename T>
void IntegerFormatter<T>::set(T number) {
	this->number = number;
}
template<typename T>
char IntegerFormatter<T>::operator[](int pos) {
	char number_str[33];
	converts::number_to_string(this->number, number_str, radix);
	upper(number_str);
	return number_str[pos];
}
template<typename T>
char IntegerFormatter<T>::getRadix() {
	return radix;
}
template<typename T>
void IntegerFormatter<T>::setRadix(char radix) {
	this->radix = radix;
}
template<typename T>
void IntegerFormatter<T>::from(const char* str) {
	// Get length
	int l = strlen(str);
	// Find index of 'r'
	int i = 0;
	for (; i < l && str[i] != 'r'; i++);
	// Split string
	char radix_str[3];
	char* number_str = new char[l - i - 1];
	for (int j = 0; j < i; j++) {
		radix_str[j] = str[j];
	}
	radix_str[i] = '\0';
	strcpy(number_str, str + i + 1);
	radix = converts::string_to_number<char>(radix_str);
	char* end_ptr = nullptr;
	number = strtol(number_str, &end_ptr, radix);
}
template<typename T>
char* IntegerFormatter<T>::to() {
	// Create strings for number and radix
	char radix_str[4]; // max = 255 + string terminator
	char number_str[33]; // max = 32 binary digits + string terminator
	// Convert numbers to strings
	converts::number_to_string(radix, radix_str, 10);
	converts::number_to_string(number, number_str, radix);
	upper(number_str);
	// Create output string
	int l = strlen(radix_str) + 1 + strlen(number_str) + 1;
	char* out = new char[l];
	strcpy(out, radix_str); // Copy radix
	strcpy(out + strlen(radix_str), "r"); // Copy separator
	strcpy(out + strlen(radix_str) + 1, number_str); // Copy number
	return out;
}
template<typename T>
void IntegerFormatter<T>::print() {
	printf("%s\n", to());
}
template<typename T>
IntegerFormatter<T>& operator+(int left, IntegerFormatter<T>& formatter) {
	formatter.number += left;
	return formatter;
}
template<typename T>
IntegerFormatter<T>& operator-(int left, IntegerFormatter<T>& formatter) {
	formatter.number -= left;
	return formatter;
}
template<typename T>
IntegerFormatter<T>& operator+(IntegerFormatter<T>& left, IntegerFormatter<T>& formatter) {
	IntegerFormatter<T> result (formatter.number + left.number, left.radix);
	return result;
}
template<typename T>
IntegerFormatter<T>& operator-(IntegerFormatter<T>& left, IntegerFormatter<T>& formatter) {
	IntegerFormatter<T> result(-formatter.number + left.number, left.radix);
	return result;
}
template<typename T>
std::ostream& operator<<(std::ostream& stream, IntegerFormatter<T>& formatter) {
	return stream << formatter.to();
}
template<typename T>
std::istream& operator>>(std::istream& stream, IntegerFormatter<T>& formatter) {
	std::string str;
	stream >> str;
	formatter.from(str.c_str());
	return stream;
}