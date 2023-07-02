#include <iostream>
#include <string>
#include "EasyInputs.h"

using namespace std;

int GetInt() {
    int inpt = 0;

    while (true) {
        cin >> inpt;

        if (!cin.good() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\nTry again: " << endl;
        }
        else {
            cin.ignore();
            break;
        }
    }

    return inpt;
}
double GetDouble() {
    double inpt = 0;

    while (true) {
        cin >> inpt;

        if (!cin.good() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\nTry again: " << endl;
        }
        else {
            cin.ignore();
            break;
        }
    }

    return inpt;
}

bool Y_N_Q() {
    char resp = 0;

    do {
        cout << "y/n? -> ";
        cin >> resp;

        if (!cin.good() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input" << endl;
        }
        else {
            cin.ignore();
        }
    } while (resp != 'y' && resp != 'Y' && resp != 'n' && resp != 'N');

    return resp == 'y' || resp == 'Y';
}

const unsigned int get_menu_option(ShowMenu show_prompt, const unsigned int menu_size) {
    int inpt = 0;

    while (true) {

        show_prompt();

        inpt = GetInt();

        if (inpt < 1 || inpt > (int) menu_size) {
            cout << "Invalid choice" << endl;
        }
        else break;
    }

    return inpt;
}

const bool Menu(ShowMenu show_prompt, const MenuOption choices[], const unsigned int menu_size) {

    const unsigned int inpt = get_menu_option(show_prompt, menu_size + 1);

    if (inpt <= menu_size) {
        choices[inpt - 1]();
        return true;
    }

    else return false;
}