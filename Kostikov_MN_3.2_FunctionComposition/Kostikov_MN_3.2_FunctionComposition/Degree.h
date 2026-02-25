#pragma once

template<typename T>
class Degree {
	T x;
	Degree();
public:
	Degree(T n) : x(n) {};

	T operator()(T n) {
		T res = 1;
		for (int i = 0; i < this->x; i++) {
			res *= n;
		}
		return res;
	}
};