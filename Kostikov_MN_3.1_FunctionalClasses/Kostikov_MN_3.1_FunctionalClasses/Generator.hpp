#pragma once
#include "Generator.h"
template<typename T>
QuadPoly<T>::QuadPoly(T a, T b, T c) : a(a), b(b), c(c) {}
template<typename T>
T QuadPoly<T>::power(T x, T n) {
	T res = 1;
	for (T i = 0; i < n; i++, res *= x);
	return res;
}
template<typename T>
T QuadPoly<T>::operator()(T x) {
	return a * power(x, 2) + b * power(x, 2) + c;
}