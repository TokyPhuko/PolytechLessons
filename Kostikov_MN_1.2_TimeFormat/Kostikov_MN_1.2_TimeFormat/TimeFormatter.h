#pragma once
#include<iostream>
#include<string>

class TimeFormatter {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
public:
	TimeFormatter();
	TimeFormatter(std::string str);

	int operator-(TimeFormatter& right);

	void changeTime(std::string str);
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	int getSecond();
	void print();
	void print12();
};

std::ostream& operator<<(std::ostream& stream, TimeFormatter& formmater);
std::istream& operator>>(std::istream& stream, TimeFormatter& formmater);