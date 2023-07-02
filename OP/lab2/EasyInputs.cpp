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
            cout << "Invalid input" << endl;
        }
        else {
            cin.ignore();
            break;
        }
    }

    return inpt;
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

    const unsigned int inpt = get_menu_option(show_prompt, menu_size+1);

    if (inpt <= menu_size) {
        choices[inpt - 1]();
        return true;
    }

    else return false;
}