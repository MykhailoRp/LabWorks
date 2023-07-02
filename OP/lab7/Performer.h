#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <cctype>
#include "PerformerExceptions.h"


using namespace std;


bool check_for_unsigned(string s) {
	for (char i : s) {
		if (!isdigit(i)) return false;
	}

	return true;
}

unsigned int get_unsigned_int(string s) {
	if (!check_for_unsigned(s)) throw NotUnsignedInt();

	try {
		return stoul(s);
	}
	catch (System::Runtime::InteropServices::SEHException^){
		throw ValueIsTooBig();
	}
}

bool range(unsigned int r_left, unsigned int r_right, unsigned int value) {
	return r_left <= value && value <= r_right;
}


unsigned int* perform_for_range(unsigned int* arr_start, unsigned int size_start, unsigned int& size_end, unsigned int r_left, unsigned int r_right, unsigned int increase_by) {
	size_end = 0;
	unsigned int* temp_new = new unsigned int[size_start];

	for (unsigned int i = 0; i < size_start; i++) {
		if (range(r_left, r_right, arr_start[i])) {
			temp_new[size_end] = arr_start[i] * increase_by;

			if (increase_by != 0 && temp_new[size_end] / increase_by != arr_start[i]) {
				delete[] temp_new;
				throw ResOverflow();
			}

			size_end++;
		}
	}

	unsigned int* final_new = new unsigned int[size_end];

	for (unsigned int i = 0; i < size_end; i++) {
		final_new[i] = temp_new[i];
	}

	delete[] temp_new;

	return final_new;
}