#include <string>
#include <iostream>
#include "Polinom.h"

using namespace std;


const int expected_x_length = 20;


const unsigned int Polinom::calculate_c_size() {

	unsigned int res = 0;

	for (unsigned int i = 0; i < Cnum; i++) {
		res += (int) to_string(GetCoeff(i)).length() + (GetCoeff(i) < 0 ? 2 : 1) + expected_x_length + (int)to_string(i).length();
	}

	return res;
}


Polinom::Polinom() {
	Coefs = new double[5];
	Cnum = 5;
}
Polinom::Polinom(const Polinom& a) {
	Cnum = a.Cnum;
	Coefs = new double[Cnum];

	SetCoeffs(a.Coefs);
}
Polinom::Polinom(const unsigned int size) {
	Coefs = new double[size];
	Cnum = size;
}
Polinom::Polinom(const unsigned int size, const double Cfs[]) {
	Coefs = new double[size];
	Cnum = size;

	for(unsigned int i = 0; i < size; i++) {
		SetCoeff(Cfs[i], i);
	}
}
Polinom::~Polinom() {
	delete[] Coefs;
	if (c_str_o != NULL) delete[] c_str_o;
}

const bool Polinom::SetCoeff(const double Ñval, const unsigned int Ci) {
	if (Ci >= Cnum) {
		return false;
	}

	Coefs[Ci] = Ñval;

	return true;
}
const bool Polinom::SetCoeffs(const double Vals[]) {
	for (unsigned int i = 0; i < Cnum; i++) {
		SetCoeff(Vals[i], i);
	}

	return true;
}

const double Polinom::GetCoeff(const unsigned int Ci) {
	if (Ci >= Cnum) {
		return NAN;
	}

	return Coefs[Ci];
}

const unsigned int Polinom::GetSize() {
	return Cnum;
}

const double Polinom::PutX(const double X) {
	double res = 0;

	for (unsigned int i = 0; i < Cnum; i++) {
		res += Coefs[i] * pow(X, i);
	}

	return res;
}

Polinom& Polinom::operator=(const Polinom& a) {
	if (Cnum != a.Cnum) exit(1);

	SetCoeffs(a.Coefs);

	return *this;
}
Polinom Polinom::operator+(int a) {
	Polinom res = *this;

	for (unsigned int i = 0; i < Cnum; i++) {
		res.SetCoeff(GetCoeff(i) + a, i);
	}
	return res;
}
Polinom Polinom::operator-(int a) {
	return operator+(-a);
}
Polinom& Polinom::operator+=(int a) {
	*this = *this + a;
	return *this;
}
Polinom& Polinom::operator-=(int a) {
	*this = *this - a;
	return *this;
}
Polinom Polinom::operator+(double a) {
	Polinom res = *this;

	for (unsigned int i = 0; i < Cnum; i++) {
		res.SetCoeff(GetCoeff(i) + a, i);
	}
	return res;
}
Polinom Polinom::operator-(double a) {
	return operator+(-a);
}
Polinom& Polinom::operator+=(double a) {
	*this = *this + a;
	return *this;
}
Polinom& Polinom::operator-=(double a) {
	*this = *this - a;
	return *this;
}

Polinom operator+(Polinom a, Polinom b) {

	unsigned int i = 0;

	bool a_smaller = a.Cnum < b.Cnum;

	Polinom res((a_smaller) ? a.Cnum : b.Cnum);

	for (; i < res.Cnum; i++) {
		res.SetCoeff(a.GetCoeff(i) + b.GetCoeff(i), i);
	}

	for (; i < ((a_smaller) ? b : a).Cnum; i++) {
		res.SetCoeff(((a_smaller) ? b : a).GetCoeff(i), i);
	}
	return res;
}

Polinom operator-(Polinom a, Polinom b) {

	unsigned int i = 0;

	bool a_smaller = a.Cnum < b.Cnum;

	Polinom res((a_smaller) ? a.Cnum : b.Cnum);

	for (; i < res.Cnum; i++) {
		res.SetCoeff(a.GetCoeff(i) - b.GetCoeff(i), i);
	}

	for (; i < ((a_smaller) ? b : a).Cnum; i++) {
		res.SetCoeff(((a_smaller) ? b : a).GetCoeff(i), i);
	}
	return res;
}

bool operator==(const Polinom& a, const Polinom& b) {

	if (a.Cnum != b.Cnum) return false;

	for (unsigned int i = 0; i < a.Cnum; i++)
		if (a.Coefs[i] != b.Coefs[i]) 
			return false;

	return true;
}

ostream& operator<<(ostream& os, Polinom p) {

	os << p.ToCStr();

	return os;
}

const char * Polinom::ToCStr() {

	unsigned int i = 0;

	const unsigned int c_size = calculate_c_size();
	
	if (c_str_o != NULL) delete[] c_str_o;

	c_str_o = new char[c_size];

	while ((GetCoeff(i) == 0 || GetCoeff(i) == NAN) && i <= Cnum) i++;

	if (i >= Cnum) return "0";

	sprintf(c_str_o, "%lf", GetCoeff(i));

	if (i != 0) sprintf(c_str_o, "%s * X^%d", c_str_o, i);

	for (i++; i < Cnum; i++) {
		if (GetCoeff(i) != 0) sprintf(c_str_o, "%s %+lf * X^%d", c_str_o, GetCoeff(i), i);
	}

	return c_str_o;
}