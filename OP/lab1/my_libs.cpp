#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void show_stream_file(ifstream* FileToShow) {
    string temp_line;

    while (getline(*FileToShow, temp_line)) {
        cout << temp_line << endl;
    }

    FileToShow->clear();
    FileToShow->seekg(0);
}


void show_stream_file_by_name(ifstream* FileToShow, string DisplayName) {

    printf("%s:\n", DisplayName.c_str());

    show_stream_file(FileToShow);
}

void show_pointer_file(FILE* FileToShow) {
    string temp_line;

    char ch;

    ch = fgetc(FileToShow);

    while (ch != EOF){
        printf("%c", ch);
        ch = fgetc(FileToShow);
    }

    rewind(FileToShow);
}

void show_pointer_file_by_name(FILE* FileToShow, char* DisplayName) {

    printf("%s:\n", DisplayName);

    show_pointer_file(FileToShow);
}

int erase(char* line, int pos, int len) {
    int i;

    for (i = pos; i < strlen(line) - len; i++) {
        line[i] = line[i + len];
    }

    line[i] = '\0';
    return 1;
}

char* insert(char* line, int pos, const char insertion[]) {
    char* new_line = new char[256];

    int j = 0;
    int i;

    for (i = 0; i < pos; i++) {
        new_line[j++] = line[i];
    }

    for (int b = 0; b < strlen(insertion); b++) {
        new_line[j++] = insertion[b];
    }

    for (; i < strlen(line); i++) {
        new_line[j++] = line[i];
    }

    new_line[j] = '\0';

    return new_line;
}