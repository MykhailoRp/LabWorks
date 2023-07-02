#pragma once
#include <exception>

using namespace std;

struct WrongRange : public exception {
	const char* what() const throw () {
		return "Wrong range";
	}
};
struct ResOverflow : public exception {
	const char* what() const throw () {
		return "Calculation resulted in overflow";
	}
};
struct NotUnsignedInt : public exception {
	const char* what() const throw () {
		return "Input is not unsigned int";
	}
};
struct ValueIsTooBig : public exception {
	const char* what() const throw () {
		return "Int value is too big";
	}
};