#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <windows.h>
#include "my_libs.h"

using namespace std;

#define string_size 256

void analize_file(ifstream* FileSorce, ofstream* FileResult);
void analize_file(FILE* FileSorce, FILE* FileResult);

void PerformForStrings();

void PerformForChars();

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int mode = 0;
    char resp = 0;

    if (argc < 3) {
        cout << "!!!Missang arguments!!!";
        return 1;
    }

    if (!strcmp(argv[1], "-mode")) {
        if (!strcmp(argv[2], "FilePointer")) {
            mode = 1;
        }
        else if (!strcmp(argv[2], "FileStream")) {
            mode = 2;
        }
        else {
            cout << "!!!Unexpected option (use FilePointer or FileStream)!!! you used: " << argv[2];
            return 1;
        }
    }
    else {
        cout << "!!!Unexpected option (use -mode)!!! you used: " << argv[1];
        return 1;
    }

ProgramStart:
    switch (mode)
    {
    case 1:
        PerformForChars();
        break;
    case 2:
        PerformForStrings();
        break;
    }

    do {
        cout << endl << "Run program again?\ny/n -> ";
        cin.ignore();
        cin >> resp;

        if (tolower(resp) == 'y') {
            cin.ignore();
            goto ProgramStart;
        }

    } while (tolower(resp) != 'n');


    return 0;
}

void PerformForStrings() {
    string ifile_name, ofile_name;

    ifstream result, F;
    ofstream F_out;

StartFileInput:
    cout << "Input file name: ";

    getline(cin, ifile_name);

    ofile_name = ifile_name;
    ofile_name.insert(ofile_name.size() - 4, "_out");

    F.open(ifile_name, ios::in);

    if (!F) {
        cout << "Failled to open " << ifile_name << endl << endl;
        goto StartFileInput;
    }

    F_out.open(ofile_name, ios::out | ios::trunc);

    if (!F_out) {
        cout << "Failled to open " << ofile_name << endl << endl;
        goto StartFileInput;
    }

    cout << endl;
    show_stream_file_by_name(&F, ifile_name);

    analize_file(&F, &F_out);

    F_out.close();
    F.close();

    result.open(ofile_name, ios::in);

    cout << endl << endl;
    show_stream_file_by_name(&result, ofile_name);

    result.close();
}

void analize_file(ifstream* FileSorce, ofstream* FileResult) {
    string temp_string;
    char temp_buff[256];

    bool opened_bracket;
    bool contains_num;
    int opened_bracked_position;
    int counter;

    while (getline(*FileSorce, temp_string)) {

        opened_bracket = false;
        contains_num = false;
        opened_bracked_position = 0;
        counter = 0;

        for (int i = 0; i < temp_string.size(); i++) {

            switch (temp_string[i])
            {
            case ' ':
                if (contains_num) {
                    counter++;
                    contains_num = false;
                }
                break;
            case '(':
                if (opened_bracket) {
                    temp_string.erase(opened_bracked_position, 1);
                    i--;
                }

                opened_bracket = true;
                opened_bracked_position = i;
                counter = 0;
                break;
            case ')':
                if (opened_bracket) {

                    if (contains_num) {
                        counter++;
                        contains_num = false;
                    }

                    sprintf(temp_buff, "-%d ", counter);

                    temp_string.insert(opened_bracked_position + 1, temp_buff);
                    i += strlen(temp_buff);

                    opened_bracket = false;
                    counter = 0;
                }
                else {
                    temp_string.erase(i, 1);
                    i--;
                }
                break;
            default:
                if (isdigit(temp_string[i]) && opened_bracket) {
                    contains_num = true;
                }
                break;
            }
        }

        if (opened_bracket) {
            temp_string.erase(opened_bracked_position, 1);
        }

        (*FileResult) << temp_string << endl;
    }

    FileSorce->clear();
    FileSorce->seekg(0);
}

void PerformForChars() {
    char* ifile_name;
    char* ofile_name;

    FILE* F;
    FILE* F_out;
    FILE* result;

StartFileInput:
    ifile_name = new char[string_size];

    cout << "Input file name: ";

    cin.get(ifile_name, string_size);

    if ((F = fopen(ifile_name, "r")) == NULL) {
        cout << "Failled to open " << ifile_name << endl << endl;
        free(ifile_name);
        cin.ignore();
        goto StartFileInput;
    }

    ofile_name = insert(ifile_name, strlen(ifile_name) - 4, "_out");

    if ((F_out = fopen(ofile_name, "w")) == NULL) {
        cout << "Failled to open " << ofile_name << endl << endl;
        free(ifile_name);
        cin.ignore();
        goto StartFileInput;
    }

    cout << endl;
    show_pointer_file_by_name(F, ifile_name);

    analize_file(F, F_out);

    fclose(F_out);
    fclose(F);

    result = fopen(ofile_name, "r");

    cout << endl << endl;
    show_pointer_file_by_name(result, ofile_name);

    fclose(result);
}

void analize_file(FILE* FileSorce, FILE* FileResult) {
    char* temp_string = new char[string_size];
    char* temp_new_line;
    char temp_buff[string_size];

    bool opened_bracket;
    bool contains_num, contains_letter;
    int opened_bracked_position;
    int counter;

    while (fgets(temp_string, string_size, FileSorce)) {
        opened_bracket = false;
        contains_num = false;
        contains_letter = false;
        opened_bracked_position = 0;
        counter = 0;

        for (int i = 0; i < string_size && (temp_string[i] != '\0' && temp_string[i] != '\n'); i++) {

            switch (temp_string[i])
            {
            case ' ':
                if (contains_num && contains_letter) {
                    counter++;
                    contains_num = false;
                    contains_letter = false;
                }
                break;
            case '(':
                if (opened_bracket) {
                    erase(temp_string, opened_bracked_position, 1);
                    i--;
                }

                opened_bracket = true;
                opened_bracked_position = i;
                counter = 0;
                break;
            case ')':
                if (opened_bracket) {

                    if (contains_num && contains_letter) {
                        counter++;
                        contains_num = false;
                        contains_letter = false;
                    }

                    sprintf(temp_buff, "-%d ", counter);

                    temp_new_line = insert(temp_string, opened_bracked_position + 1, temp_buff);
                    free(temp_string);
                    temp_string = temp_new_line;

                    i += strlen(temp_buff);

                    opened_bracket = false;
                    counter = 0;
                }
                else {
                    erase(temp_string, i, 1);
                    i--;
                }
                break;
            default:
                if (opened_bracket) {
                    if (isdigit(temp_string[i])) {
                        contains_num = true;
                    }
                    else if (isalpha(temp_string[i])) {
                        contains_letter = true;
                    }
                }
                break;
            }
        }

        if (opened_bracket) {
            erase(temp_string, opened_bracked_position, 1);
        }

        fprintf(FileResult, "%s", temp_string);
    }

    rewind(FileSorce);
}