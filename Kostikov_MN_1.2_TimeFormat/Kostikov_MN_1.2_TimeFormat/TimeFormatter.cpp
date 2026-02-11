#include "TimeFormatter.h"
#include <ctime>
#include<string>
#include<iostream>


std::string to_str(int n) { return (n < 10 ? "0" + std::to_string(n) : std::to_string(n)); }

TimeFormatter::TimeFormatter() {
	time_t timestamp = time(&timestamp);
	struct tm datetime = *localtime(&timestamp);

	this->year = datetime.tm_year + 1900;
	this->month = datetime.tm_mon;
	this->day = datetime.tm_mday;
	this->hour = datetime.tm_hour;
	this->minute = datetime.tm_min;
	this->second = datetime.tm_sec;
}

TimeFormatter::TimeFormatter(std::string str) {
	this->changeTime(str);
}

int TimeFormatter::operator-(TimeFormatter& right) {
	int months_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int days = 0;

	for (int i = right.getYear() + 1; i < this->year; i++) {
		if (i % 4 == 0) {
			days += 366;
		}
		else {
			days += 365;
		}
	}

	for (int i = right.getMonth()+1; i < 12 - right.getMonth(); i++) {
		if ((i == 2) and (right.getYear() % 4 == 0)) {
			days += 29;
		}
		else {
			days += months_days[i-1];
		}
	}

	for (int i = 1; i < this->getMonth(); i++) {
		if ((i == 2) and (this->getYear() % 4 == 0)) {
			days += 29;
		}
		else {
			days += months_days[i-1];
		}
	}

	int time = this->second - right.getSecond() + 60 * (this->minute - right.getMinute()) + 60 * 60 * (this->hour - right.getHour()) + 60 * 60 * 24 * days;

	return time;
}

void TimeFormatter::changeTime(std::string str) {
	sscanf_s(str.c_str(), "%d-%d-%d_%d-%d-%d", &year, &month, &day, &hour, &minute, &second);
}

int TimeFormatter::getYear() {
	return year;
}

int TimeFormatter::getMonth() {
	return month;
}

int TimeFormatter::getDay() {
	return day;
}

int TimeFormatter::getHour() {
	return hour;
}

int TimeFormatter::getMinute() {
	return minute;
}

int TimeFormatter::getSecond() {
	return second;
}

void TimeFormatter::print() {
	std::string result = std::to_string(year) + "-" + to_str(month) + "-" + to_str(day) + "_" + to_str(hour) + "-" + to_str(minute) + "-" + to_str(second);

	std::cout << result << std::endl;
}

void TimeFormatter::print12() {
	std::string result = std::to_string(year) + "-" + to_str(month) + "-" + to_str(day) + "_" + (hour > 12 ? to_str(hour - 12)+"PM" : to_str(hour)+"AM") + "-" + to_str(minute) + "-" + to_str(second);

	std::cout << result << std::endl;
}

std::ostream& operator<<(std::ostream& stream, TimeFormatter& formatter) {
	std::string result = std::to_string(formatter.getYear()) + "-" + to_str(formatter.getMonth()) + "-" + to_str(formatter.getDay()) + "_" + to_str(formatter.getHour()) + "-" + to_str(formatter.getMinute()) + "-" + to_str(formatter.getSecond());

	return stream << result << std::endl;
}

std::istream& operator>>(std::istream& stream, TimeFormatter& formatter) {
	std::string str;
	stream >> str;
	formatter.changeTime(str);
	return stream;
}