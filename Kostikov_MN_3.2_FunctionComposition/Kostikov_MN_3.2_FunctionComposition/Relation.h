#pragma once

template<typename T>
class Relation {
	T denominator;
	Relation();
public:
	Relation(T n) : denominator(n) {};

	T operator()(T n) {
		return n / denominator;
	}
};