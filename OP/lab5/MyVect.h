#pragma once

using namespace std;

class TVector
{
public:
	TVector(double x = 0, double y = 0, double z = 0);

	virtual double modul();
	virtual double scalyar(TVector other);

	virtual bool IsParallelTo(TVector other);
	virtual bool IsPerpendTo(TVector other);

	virtual TVector operator*(double a);
	virtual TVector operator+(TVector a);
	virtual void operator=(TVector a);
	virtual void operator+=(TVector a);
	virtual bool operator==(TVector other);

	virtual string to_str();

	extern friend ostream& operator<<(ostream& os, TVector v);

protected:
	double x = 0, y = 0, z = 0;

	virtual double modulSq();

private:

};