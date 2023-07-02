#pragma once
#include <exception>

using namespace std;

struct FailedToOpen : public exception {
	const char* what() const throw () {
		return "Failed to open file";
	}
};
struct AllreadyOpened : public exception {
	const char* what() const throw () {
		return "File is allready opened";
	}
};
struct AllreadyCLosed : public exception {
	const char* what() const throw () {
		return "File is allready closed";
	}
};
struct TryingToSameSave : public exception {
	const char* what() const throw () {
		return "Tying to save file to opened name";
	}
};
struct FailedToRead : public exception {
	const char* what() const throw () {
		return "Failed to read file";
	}
};
struct FailedToWrite : public exception {
	const char* what() const throw () {
		return "Failed to write to file";
	}
};
struct FileIsEmpty : public exception {
	const char* what() const throw () {
		return "Arr is empty";
	}
};
struct GeneratedZeroSize : public exception {
	const char* what() const throw () {
		return "Trying to create a zero sized arr";
	}
};