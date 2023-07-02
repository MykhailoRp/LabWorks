// lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "LinkedList.h"
#include "EasyHash.h"
#include "MultiInputs.h"

using namespace std;

void show_menu();

template<class Key, class Content>
void add_element(HashList<Key, Content>& l);

template<class Key, class Content>
void get_element(HashList<Key, Content>& l);

template<class Key, class Content>
void pop_elemet(HashList<Key, Content>& l);

template<class Key, class Content>
void show_dict(HashList<Key, Content>& l);

template<class Key, class Content>
void is_empty_test(HashList<Key, Content>& l);

template<class Key, class Content>
void iterator_test(HashList<Key, Content>& l);

template <class Key, class Content>
void perform();



int main(){

    typedef void (*PerformFunc) ();

    HashList<string, PerformFunc> perform_vars(32);

    string key_content;

    bool check = true;

    perform_vars.put("int:int", perform<int, int>);
    perform_vars.put("int:string", perform<int, string>);
    perform_vars.put("int:double", perform<int, double>);
    perform_vars.put("int:bool", perform<int, bool>);
    perform_vars.put("double:int", perform<double, int>);
    perform_vars.put("double:string", perform<double, string>);
    perform_vars.put("double:double", perform<double, double>);
    perform_vars.put("double:bool", perform<double, bool>);
    perform_vars.put("string:int", perform<string, int>);
    perform_vars.put("string:string", perform<string, string>);
    perform_vars.put("string:double", perform<string, double>);
    perform_vars.put("string:bool", perform<string, bool>);


    do{
        cout << "Input key and content type (format: key:content) (\'/exit\' to stop program) --> ";

        Fill(key_content);

        if (perform_vars.contains(key_content)) {
            perform_vars[key_content]();
        }
        else {
            if (!key_content.compare("/exit")) check = false;
            else cout << key_content << " is unsupported" << endl;
        }
    } while (check);

    return 0;
}

void show_menu() {
    cout << "\nDict menu:\n" <<
        "1 - add/set element\n" <<
        "2 - get element\n" <<
        "3 - delete element\n" <<
        "4 - show dict\n" <<
        "5 - test empty\n" <<
        "6 - test iterator\n" <<
        "7 - exit\n" <<
        "(1-7) --->";
}

template<class Key, class Content>
void add_element(HashList<Key, Content>& l) {

    Key key;
    Content cont;

    cout << "Input key: ";
    Fill(key);
    cout << "Input Content: ";
    Fill(cont);

    l.put(key, cont);

    cout << "Added " << l[key] << " to dict, now dict is: " << l << endl;
};

template<class Key, class Content>
void get_element(HashList<Key, Content>& l) {

    Key key;

    cout << "Input key: ";
    Fill(key);

    if (l.contains(key)) cout << key << " : " << l[key] << endl;
    else cout << "Dict does not contain " << key << endl;
};

template<class Key, class Content>
void pop_elemet(HashList<Key, Content>& l) {

    Key key;

    cout << "Input key: ";
    Fill(key);


    if (l.contains(key)) cout << "Poped " << l.pop(key) << " from dict, now dict is: " << l << endl;
    else cout << "Dict does not contain " << key << endl;
};

template<class Key, class Content>
void show_dict(HashList<Key, Content>& l) {
    cout << "Dict is: " << l << endl;
};

template<class Key, class Content>
void is_empty_test(HashList<Key, Content>& l) {
    cout << "Dict is ";

    if (l.is_empty()) cout << "empty";
    else cout << "not empty";

    cout << endl;
};

template<class Key, class Content>
void iterator_test(HashList<Key, Content>& l) {
    cout << "Using iterator to output dict:" << endl;


    cout << "start" << endl;
    for (LinkedList<HashElement<Key, Content>> i : l) {
        for (ListNode<HashElement<Key, Content>> j : i) {
            cout << j << endl;
        }
    }
    cout << "end" << endl;
};


template <class Key, class Content>
void perform() {
    bool res = true;

    MenuOption<Key, Content> menu_arr[] = {
        add_element,
        get_element,
        pop_elemet,
        show_dict,
        is_empty_test,
        iterator_test
    };

    unsigned int hash_size;

    cout << "Hash table size: ";

    Fill(hash_size);

    HashList<Key, Content> dict(hash_size);

    do {
        try {
            res = Menu(show_menu, menu_arr, 6, dict);
        }
        catch(std::exception& e){
            cout << e.what() << endl;
            res = true;
        }
    }while(res);
}