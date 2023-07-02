#include <string>
#include <iostream>
#include "MyVect.h"
#include "Vec2.h"
#include "Vec3.h"

Vec3::Vec3(double _x, double _y, double _z) {
	SetV(_x, _y, _z);
}

void Vec3::SetV(double _x, double _y, double _z) {
	x = _x;
	y = _y;
	z = _z;
}
double Vec3::GetX() {
	return x;
}
double Vec3::GetY() {
	return y;
}
double Vec3::GetZ() {
	return z;
}

Vec2 Vec3::ProjectToXY() {
	return Vec2(GetX(), GetY());
}
Vec2 Vec3::ProjectToYZ() {
	return Vec2(GetY(), GetZ());
}
Vec2 Vec3::ProjectToXZ() {
	return Vec2(GetX(), GetZ());
}

string Vec3::to_str() {
	string res = "( ";

	res += to_string(GetX()) + "; ";
	res += to_string(GetY()) + "; ";
	res += to_string(GetZ()) + " )";

	return res;

}

void Vec3::operator=(Vec2 other) {
	x = other.GetX();
	y = other.GetY();
	z = 0;
}