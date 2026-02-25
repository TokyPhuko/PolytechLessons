#pragma once
enum BoundType {
	Lower, Upper, Both, Outside
};
template<typename T>
class RangeTest {
private:
	T lower, upper;
	BoundType bound_type;
	RangeTest();
public:
	RangeTest(T lower, T upper, BoundType bound_type);//Both or Outside
	RangeTest(T bound, BoundType bound_type);
	bool operator()(T x);
};