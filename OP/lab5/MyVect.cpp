#include <string>
#include <iostream>
#include "MyVect.h"

using namespace std;

TVector::TVector(double _x, double _y, double _z) {
	x = _x;
	y = _y;
	z = _z;
}

double TVector::modul() {
	return sqrt(modulSq());
}
double TVector::modulSq() {
	return x * x + y * y + z * z;
}

double TVector::scalyar(TVector other) {
	return x * other.x + y * other.y + z * other.z;
}

bool TVector::IsParallelTo(TVector other) {

	double ref_coef = 0;

	if (x != 0) {
		ref_coef = other.x / x;
	}
	else if (y != 0) {
		ref_coef = other.y / y;
	}
	else if (z != 0) {
		ref_coef = other.z / z;
	}
	else {
		ref_coef = 0;
	}

	return (*this) * ref_coef == other;
}

bool TVector::IsPerpendTo(TVector other) {
	return scalyar(other) == 0;
}

TVector TVector::operator*(double a) {
	return TVector(x * a, y * a, z * a);
}

void TVector::operator=(TVector a) {
	x = a.x;
	y = a.y;
	z = a.z;
}

void TVector::operator+=(TVector a) {
	x += a.x;
	y += a.y;
	z += a.z;
}

bool TVector::operator==(TVector other) {
	return x == other.x && y == other.y && z == other.z;
}

TVector TVector::operator+(TVector a) {
	return TVector(x + a.x, y + a.y, z + a.z);
}

string TVector::to_str() {
	string res = "TO_STR IS UNSPECIFIED";

	return res;

}

ostream& operator<<(ostream& os, TVector v) {
	os << "( " << v.x << "; " << v.y << "; " << v.z << " )";
	return os;
}