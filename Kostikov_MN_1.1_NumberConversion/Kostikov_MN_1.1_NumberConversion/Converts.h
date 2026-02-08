#pragma once
namespace converts { //реализация задания 2 причем тк функции шаблонные достаточно одной реализации для atoi/strtol
	template<typename T>
	void number_to_string(T number, char* buffer, char base) {
		bool sign_negative = false;
		if (number < 0) {
			sign_negative = true;
			number = -number;
		}

		if (number == 0) {
			buffer[0] += '0\0';
		}
		else {
			char temp[65];
			int i = 0;
			while (number > 0) {
				if ((number % base) < 10) temp[i++] = '0' + (number % base);
				else temp[i++] = (number % base) - 10 + 'A';
				number /= base;
			}

			if (sign_negative) *buffer++ = '-';

			while (i > 0) {
				*buffer++ = temp[--i];
			}
			*buffer++ = '\0';
		}
	}

	template<typename T>
	T string_to_number(char* buffer) {
		T result = 0;
		bool sign_negative = false;

		while (*buffer != '\0') {
			if (*buffer == '-') {
				sign_negative = true;
				buffer++;
				continue;
			}

			result = result * 10 + (*buffer - '0');
			buffer++;
		}

		if (sign_negative) result = -result;

		return result;
	}
}