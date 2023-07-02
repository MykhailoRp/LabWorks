#pragma once

using namespace std;

class Polinom
{
public:
	Polinom();
	Polinom(const Polinom& a);
	Polinom(const unsigned int size);
	Polinom(const unsigned int size, const double Cfs[]);
	~Polinom();

	const bool SetCoeff(const double Ñval, const unsigned int Ci);
	const bool SetCoeffs(const double Vals[]);
	const double GetCoeff(const unsigned int Ci);
	const unsigned int GetSize();

	const double PutX(const double X);

	const char * ToCStr();
	
	Polinom& operator=(const Polinom& a);

	Polinom operator+(int a);
	Polinom operator-(int a);
	Polinom& operator+=(int a);
	Polinom& operator-=(int a);

	Polinom operator+(double a);
	Polinom operator-(double a);
	Polinom& operator+=(double a);
	Polinom& operator-=(double a);

	extern friend bool operator==(const Polinom& a, const Polinom& b);
	extern friend Polinom operator+(Polinom a, Polinom b);
	extern friend Polinom operator-(Polinom a, Polinom b);
	extern friend ostream& operator<<(ostream& os, Polinom p);

private:

	double* Coefs = NULL;
	mutable char* c_str_o = NULL;
	unsigned int Cnum;

	const unsigned int calculate_c_size();
};