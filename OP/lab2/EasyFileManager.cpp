#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include "EasyFileManager.h"

using namespace std;

/*

Error codes:

    1 - prohibited characters
    2 - lacks extension
    3 - invalid extension
    4 - file exists

*/

const string TimeTransErrorDesp[] = {
    "Using \\/:*?\"<>| charachters in name",
    "No extection provided",
    "Invalid extension",
    "File allready exists"
};

const char prohibited_characters[] = "\\/:*?\"<>|";

const int check_file_name(const string name, const string extension, const bool write) {
    ifstream tempFile;
    const size_t string_length = name.length();
    const size_t prohibited_length = strlen(prohibited_characters);

    for (int i = 0; (size_t) i < prohibited_length; i++) {
        if (name.find(prohibited_characters[i]) != string::npos) return 1;
    }

    const size_t dot_pos = name.rfind('.');

    if (dot_pos == string::npos) return 2;

    if (name.find(extension, dot_pos) == string::npos) return 3;

    if (!write) {
        tempFile.open(name, ios::in);

        if (tempFile.is_open()) {
            tempFile.close();
            return 4;
        }
    }

    return 0;
}

string get_file_name(const string prompt, const string extension, const bool write) {
    string file_name;
    char responce;

    cout << prompt;

    getline(cin, file_name);

    if (file_name.empty()) return "\0";

    const int res = check_file_name(file_name, extension, write);

    if (res > 0 && res < 4) {
        cout << TimeTransErrorDesp[res-1] << endl;

        return get_file_name(prompt, extension, write);
    }
    else if (res == 4 && write){
        cout << TimeTransErrorDesp[res - 1] << endl;

        do {
            cout << "Overwrite? y/n -> ";
            cin >> responce;
            responce = tolower(responce);
        } while (responce != 'n' && responce != 'y');

        if (responce == 'n') return get_file_name(prompt, extension, write);
        else return file_name;
    }

    return file_name;
}

ifstream* OpenBinForInput(const string prompt) {
    ifstream* F = new ifstream;
    string ifile_name;

    ifile_name = get_file_name(prompt, "dat", false);

    if (ifile_name.empty()) {
        delete F;
        return NULL;
    }

    F->open(ifile_name, ios::in | ios::binary);

    if (!F->is_open()) {
        cout << "Failled to open " << ifile_name << endl;
        return OpenBinForInput(prompt);
    }

    return F;
}

ofstream* OpenBinForOut(const string prompt) {
    ofstream* F = new ofstream;
    string ofile_name;

    ofile_name = get_file_name(prompt, "dat", true);

    if (ofile_name.empty()) {
        delete F;
        return NULL;
    }

    F->open(ofile_name, ios::out | ios::binary);

    if (!F->is_open()) {
        cout << "Failled to open " << ofile_name << endl;
        return OpenBinForOut(prompt);
    }

    return F;
}

ifstream* OpenForInput(const string prompt) {
    ifstream* F = new ifstream;
    string ifile_name;
    
    ifile_name = get_file_name(prompt, "txt", false);

    if (ifile_name.empty()) { 
        delete F;
        return NULL; 
    }

    F->open(ifile_name, ios::in);

    if (!F->is_open()) {
        cout << "Failled to open " << ifile_name << endl;
        return OpenForInput(prompt);
    }

    return F;
}

ofstream* OpenForOut(const string prompt) {
    ofstream* F = new ofstream;
    string ofile_name;

    ofile_name = get_file_name(prompt, "txt", true);

    if (ofile_name.empty()) {
        delete F;
        return NULL;
    }

    F->open(ofile_name, ios::out);

    if (!F->is_open()) {
        cout << "Failled to open " << ofile_name << endl;
        return OpenForOut(prompt);
    }

    return F;
}

void CloseFile(ifstream* F) {
    F->close();
    delete F;
}

void CloseFile(ofstream* F) {
    F->close();
    delete F;
}