#pragma once
#include "Filter.h"
template<typename T>
RangeTest<T>::RangeTest(T lower, T upper, BoundType bound_type) : lower(lower), upper(upper), bound_type(bound_type) {}
template<typename T>
RangeTest<T>::RangeTest(T bound, BoundType bound_type) : bound_type(bound_type) {
	switch (bound_type) {
	case Lower:
		lower = bound;
		break;
	case Upper:
		upper = bound;
		break;
	default:
		break;
	}
}
template<typename T>
bool RangeTest<T>::operator()(T x) {
	switch (bound_type) {
	case Lower:
		return (x > lower);
	case Upper:
		return (x < upper);
	case Both:
		return (x > lower) && (x < upper);
	case Outside:
		return (x < lower) || (x > upper);
	default:
		return false;
	}
}