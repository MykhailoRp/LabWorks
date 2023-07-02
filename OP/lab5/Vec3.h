#pragma once

class Vec3 : public TVector
{
public:
	Vec3(double x = 0, double y = 0, double z = 0);

	void SetV(double x = 0, double y = 0, double z = 0);

	double GetX();
	double GetY();
	double GetZ();

	Vec2 ProjectToXY();
	Vec2 ProjectToYZ();
	Vec2 ProjectToXZ();

	string to_str();

	void operator=(Vec2 other);

protected:

private:

};