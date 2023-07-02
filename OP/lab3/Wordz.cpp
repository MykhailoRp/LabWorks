#include <iostream>
#include <string>
#include <ctype.h>
#include "Wordz.h"

using namespace std;

bool is_just_a_word(string wrd) {
	if (wrd.find(' ') != string::npos ||
		wrd.find('.') != string::npos ||
		wrd.find(',') != string::npos ||
		wrd.find('/') != string::npos ||
		wrd.find('\\') != string::npos ||
		wrd.find('|') != string::npos
		) return false;

	bool alpha = false;

	for (int i = 0; i < wrd.length() && !alpha; i++) alpha = isalpha(wrd[i]);

	return alpha;
}

//Word

Word::Word(string wrd_str) {
	SetWord(wrd_str);
}

Word::Word() {
	SetWord("");
}

void Word::SetWord(string wrd_str) {
	word.clear();
	word.append(wrd_str);
}

const string Word::GetWord() {
	return word;
}

const int Word::CountNum() {
	const int len = (int) word.length();
	int cnt = 0;

	for (int i = 0; i < len; i++) {
		if (isdigit(word[i])) cnt++;
	}

	return cnt;
}

ostream& operator<<(ostream& os, Word w) {
	os << w.GetWord();
	return os;
}

//end Word



//Words

Words::Words() {
	words = new Word[arr_size];
}
Words::Words(string wrd_str) {
	words = new Word[arr_size];

	const int str_len = (int) wrd_str.length();

	size_t wrd_start = 0, wrd_end = wrd_str.find(' ');

	while (wrd_end != string::npos && wrd_start < str_len-1 && wrd_end < str_len){

		AddWord(wrd_str.substr(wrd_start, wrd_end - wrd_start));

		wrd_start = wrd_end + 1;

		wrd_end = wrd_str.substr(wrd_start).find(' ');

		if (wrd_end == string::npos) {
			AddWord(wrd_str.substr(wrd_start));
			break;
		}

		wrd_end = wrd_end + wrd_start;

	}
}
Words::Words(Word* wrd_arr, const int arr_size) {
	words = new Word[arr_size];

	for (int i = 0; i < arr_size; i++) {
		words[i].SetWord(wrd_arr[i].GetWord());
	}
}
Words::~Words() {
	delete[] words;
}

const bool Words::AddWord(string wrd_str) {

	if (!is_just_a_word(wrd_str)) return false;

	const int len = GetLength();

	if (len >= arr_size) {
		if(!change_size(arr_size * 2)) return false;
	}

	words[len].SetWord(wrd_str);

	return true;
}
const bool Words::AddWord(Word wrd) {
	return AddWord(wrd.GetWord());
}

Word Words::PopWord(int index) {

	Word temp_res;

	if (index >= arr_size) exit(0);

	temp_res.SetWord(words[index].GetWord());

	for (int i = index; i < arr_size - 1; i++) {
		words[i].SetWord(words[i + 1].GetWord());
	}

	return temp_res;
}

const string Words::WordsToStr() {

	string res = "";

	const int length = GetLength();

	for (int i = 0; i < length; i++) {
		res += words[i].GetWord();
		res += " ";
	}

	return res;
}

Word Words::GetTaskWord() {
	int index = 0;
	const int length = GetLength();

	for (int i = 0; i < length; i++) {
		if (words[index].CountNum() < words[i].CountNum()) {
			index = i;
		}
	}

	return words[index];
}

Word& Words::operator[](int index) {

	if (index >= arr_size) exit(0);

	return words[index];
}

const bool Words::change_size(int to_size) {

	Word* new_words = new Word[to_size];

	for (int i = 0; i < arr_size && i < to_size; i++) {
		new_words[i].SetWord(words[i].GetWord());
	}

	delete[] words;
	arr_size = to_size;

	words = new_words;

	return true;
}

const int Words::GetSize() {
	return arr_size;
}

const int Words::GetLength() {

	for (int i = 0; i < arr_size; i++) {
		if (words[i].GetWord().empty()) return i;
	}

	return arr_size;
}


ostream& operator<<(ostream& os, Words& ws) {
	for (int i = 0; i < ws.GetLength(); i++) {
		os << ws[i] << ' ';
	}
	return os;
}

//end Words