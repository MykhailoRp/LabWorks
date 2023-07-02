#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include "Performer.h"
#include "FileRepresentExceptions.h"

using namespace std;


class IntArr {

	unsigned int size = 0;
	unsigned int* arr = nullptr;

public:
	IntArr(unsigned int _size, unsigned int* _arr) {

		if (_size == 0) {
			throw GeneratedZeroSize();
		}

		size = _size;

		arr = new unsigned int[size];

		for (unsigned int i = 0; i < _size; i++) {
			arr[i] = _arr[i];
		}
	}

	IntArr(IntArr&& other) {
		size = other.size;
		arr = other.arr;

		other.size = 0;
		other.arr = nullptr;
	}

	IntArr(IntArr& other) : IntArr(other.size, other.arr) {}

	IntArr() {}

	~IntArr() {
		delete[] arr;
	}

	void clear() {
		size = 0;
		delete[] arr;
		arr = nullptr;
	}

	unsigned int get_size() { return size; }
	bool empty() { return size == 0; }

	void operator=(IntArr& other) {
		delete[] arr;

		arr = other.arr;
		size = other.size;
	}

	IntArr& operator=(IntArr&& other) {
		size = other.size;

		delete[] arr;

		arr = new unsigned int[size];

		for (unsigned int i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}

		return *this;
	}

	void load_from_bin(string name) {
		ifstream in_file(name, ios::binary);

		in_file.seekg(0, ios::end);
		streampos fileSize = in_file.tellg();
		in_file.seekg(0, ios::beg);

		unsigned int _size = (unsigned int) fileSize / sizeof(unsigned int);
		unsigned int* _arr = new unsigned int[_size];

		if(!in_file.read(reinterpret_cast<char*>(_arr), fileSize)) throw FailedToRead();

		in_file.close();

		delete arr;

		arr = _arr;
		size = _size;
	}

	void save_to_bin(string name) {
		if (size == 0) throw FileIsEmpty();

		ofstream out_file(name, ios::binary);

		out_file.write(reinterpret_cast<const char*>(arr), size * sizeof(int));

		out_file.close();
	}

	string to_str() {

		if (size == 0) return "";

		string res;

		for (unsigned int i = 0; i < size; i++) {
			res += to_string(arr[i]) + ", ";
		}

		*(res.end() - 2) = '\0';

		return res;
	}

	void append(unsigned int value) {

		unsigned int new_size = size + 1;

		unsigned int* new_arr = new unsigned int[new_size];

		for (unsigned int i = 0; i < size; i++) {
			new_arr[i] = arr[i];
		}
		new_arr[size] = value;

		delete[] arr;
		arr = new_arr;
		size = new_size;
	}

	IntArr get_performed(unsigned int r_left, unsigned int r_right, unsigned int increase_by) {
		unsigned int new_size;

		unsigned int* new_arr;

		new_arr = perform_for_range(arr, size, new_size, r_left, r_right, increase_by);

		IntArr res(new_size, new_arr);

		delete[] new_arr;

		return res;
	}
};