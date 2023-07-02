#include <iostream>
#include <string>
#include "Wordz.h"

using namespace std;


char* name_pointer() {
	int size = 256;
	char* name = new char[size];

	int i = -1;
	do {
		i++;

		if (i >= size) {
			printf("Input is too long. Please try again.\n");
			return nullptr;
		}

		name[i] = getchar();
	} while (name[i] != '\n');

	name[i] = '\0';

	if (strchr(name, '.') == nullptr) {
		strcat(name, ".txt");
	}

	char* result = new char[strlen(name) + 1];
	strcpy(result, name);

	return result;
}

void PerformForLine() {
	string temp_line;

	cout << "Input words (any words with prohibited symbols will be ignored): ";

	do {
		getline(cin, temp_line);
	} while (temp_line.empty());

	Words db(temp_line);

	cout << "Extracted words: " << db << endl;
		
	cout << "Word with most numbers: " << db.GetTaskWord() << endl;
}

int main() {
	char res = 0;

	cout << "1" << name_pointer() << endl;
	cout << "2" << name_pointer() << endl;
	cout << "3" << name_pointer() << endl;

	do {
		PerformForLine();

		do {
			cout << "Perform againg? (y/n): ";
			cin >> res;
			cin.ignore();
		} while (res != 'y' && res != 'Y' && res != 'n' && res != 'N');

	} while (res == 'y' || res == 'Y');
}