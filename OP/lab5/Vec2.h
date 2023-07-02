#pragma once

class Vec2 : public TVector
{
public:
	Vec2(double x = 0, double y = 0);

	void SetV(double x = 0, double y = 0);

	double GetX();
	double GetY();

	virtual Vec2 operator+(Vec2 a);
	virtual void operator=(Vec2 a);
	extern friend ostream& operator<<(ostream& os, Vec2 v);
	string to_str();

protected:
	const double z = 0;

private:

};