#pragma once
template<typename T>
class QuadPoly {
private:
	T a, b, c;
	QuadPoly();
	T power(T x, T n);
public:
	QuadPoly(T a, T b, T c);
	T operator()(T x);
};