#include <string>
#include <iostream>
#include "MyVect.h"
#include "Vec2.h"

Vec2::Vec2(double _x, double _y) {
	Vec2::SetV(_x, _y);
}

void Vec2::SetV(double _x, double _y) {
	x = _x;
	y = _y;
}

double Vec2::GetX() {
	return x;
}
double Vec2::GetY() {
	return y;
}

Vec2 Vec2::operator+(Vec2 a) {
	return Vec2(GetX() + a.GetX(), GetY() + a.GetY());
}

ostream& operator<<(ostream& os, Vec2 v) {
	os << "( " << v.GetX() << "; " << v.GetY() << " )";
	return os;
}

string Vec2::to_str() {
	string res = "( ";

	res += to_string(GetX()) + "; ";
	res += to_string(GetY()) + " )";

	return res;

}

void Vec2::operator=(Vec2 a) {
	SetV(a.GetX(), a.GetY());
}