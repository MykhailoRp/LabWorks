#include <iostream>
#include <string>
#include "TimeTranslator.h"

using namespace std;

/*

Error codes:

	-1 - unexpected char
	-2 - too many sections
	-3 - section is too large
	-4 - time input is too large

*/

string TimeTransErrorDesp[] = {
	"Unexpected char was provided in a string",
	"Too many sections provided",
	"Provided section is too large",
	"Time value is too large"
};

const int string_to_time(const string input, const int expected_sections, const int max_section_value, const bool notif) {
	
	//12:70
	
	int result = 0;
	int section = 0;
	int mult = def_section_val;
	int section_counter = 1;

	for (int i = 0; i < input.length(); i++) {
		if (isdigit(input[i])) {
			section = (section * 10) + (input[i] - '0');

			if (section > max_section_value) {
				return -3;
			}
		}
		else if(input[i] == ':') {
				result = result * mult + section;
				section = 0;

				section_counter++;
				if (section_counter > expected_sections) {
					return -2;
				}
		}
		else{
			return -1;
		}
	}

	result = result * mult + section;

	if (section_counter < expected_sections) result = int(result * pow(mult, expected_sections - section_counter));
 
	if (notif) cout << "Translated " << input << " to " << result << endl;

	return result;
};

const string time_to_string(const int input, const int expected_sections, const int max_section_value, const bool notif) {

	if (input <= 0) return to_string(input);

	string result = "";
	char str_to_insert[10];

	int left = input, section = 0, sections_num = 0;

	do{
		sections_num++;

		if (sections_num > expected_sections) return "-2";

		section = left % max_section_value;

		sprintf(str_to_insert, "%0*d:", static_cast<unsigned int>(to_string(max_section_value).length()), section);

		result.insert(0, str_to_insert);

		left = (left - section) / max_section_value;

	} while (left);

	sprintf(str_to_insert, "%0*d:", static_cast<unsigned int>(to_string(max_section_value).length()), 0);

	while (sections_num < expected_sections) {
		result.insert(0, str_to_insert);
		sections_num++;
	}

	*(result.end() - 1) = '\0';

	if (notif) cout << "Translated " << input << " to " << result << endl;

	return result;
};

const int input_time(const int expected_sections, const int max_section_value, const bool notif) {
	string input;
	int result;

	getline(cin, input);

	if (notif) cout << "You entered: " << input << endl;

	result = string_to_time(input, expected_sections, max_section_value, notif);

	if (result > dayInSecond) {
		return -4;
	}

	return result;
};

const int get_time(const string prompt, const int expected_sections, const int max_section_value, const bool notif) {
	int time_buff;

	cout << prompt;
	time_buff = input_time(def_section_num, def_section_val, notif);

	if (time_buff < 0) {
		cout << "!!!" << TimeTransErrorDesp[-(time_buff + 1)] << "!!!" << endl;
		return get_time(prompt, expected_sections, max_section_value, notif);
	}
	else return time_buff;
}