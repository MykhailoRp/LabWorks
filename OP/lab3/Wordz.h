#pragma once

using namespace std;

class Word {

private:
	string word;

public:
	//read about mutable and imutable and make a desigion what is word
	Word(string wrd_str);
	Word();
	void SetWord(string wrd_str);
	const string GetWord();
	const int CountNum();

	//Word& operator=(Word& other);

};

extern ostream& operator<<(ostream& os, Word w);

class Words {
private:
	Word* words;
	int arr_size = 10;

	const bool change_size(int to_size);

public:
	Words();
	Words(string wrd_str);
	Words(Word* wrd_arr, const int arr_size);
	~Words();

	const bool AddWord(string wrd_str);
	const bool AddWord(Word wrd);
	Word PopWord(int index);

	const string WordsToStr();

	Word GetTaskWord();

	Word& operator[](int index);

	const int GetSize();
	const int GetLength();
};

extern ostream& operator<<(ostream& os, Words& ws);