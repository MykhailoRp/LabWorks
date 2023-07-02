#pragma once

using namespace std;

const int def_section_num = 3;
const int def_section_val = 60;
const int dayInSecond = 86400;

extern const int input_time(const int expected_sections, const int max_section_value, const bool);
extern const int get_time(const string prompt, const int expected_sections, const int max_section_value, const bool);
extern const int string_to_time(string, const int, const int, const bool);
extern const string time_to_string(const int, const int, const int, const bool);