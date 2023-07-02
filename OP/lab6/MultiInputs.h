#pragma once
#include <iostream>
#include "EasyHash.h"


using namespace std;

template<class C>
extern void Fill(C& obj) {
    while (true) {
        cin >> obj;

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
}

template <class Key, class Content>
using MenuOption = void (*)(HashList<Key, Content>& list);

typedef void (*ShowMenu) ();

const unsigned int get_menu_option(ShowMenu show_prompt, const unsigned int menu_size) {
    unsigned int inpt = 0;

    while (true) {

        show_prompt();

        Fill<unsigned int>(inpt);

        if (inpt < 1 || inpt >(int) menu_size + 1) {
            cout << "Invalid choice" << endl;
        }
        else break;
    }

    return inpt;
}

template <class Key, class Content>
const bool Menu(ShowMenu show_prompt, const MenuOption<Key, Content> choices[], const unsigned int menu_size, HashList<Key, Content>& list) {

    const unsigned int inpt = get_menu_option(show_prompt, menu_size + 1);

    if (inpt <= menu_size) {
        choices[inpt - 1](list);
        return true;
    }

    else return false;
}