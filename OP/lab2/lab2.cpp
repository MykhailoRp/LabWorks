#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>
#include "TimeTranslator.h"
#include "ScheduleDB.h"
#include "EasyFileManager.h"
#include "EasyInputs.h"

#define day_seconds 24*60*60
#define default_size 50
#define full_explanation false

using namespace std;

Event* my_db;
int my_db_size = default_size;

void start_menu();
void edit_menu();

void create_new_choice();

void load_from_file_choice();
void save_free_time();

void show_events();

void del_db_element();
void add_db_elements();
void change_db_element();

void save_to_file();


int main(){
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    start_menu();

    return 0;
}

void show_start_menu() {
    cout << "Menu for evets db:\n\n" <<
        "1 - Open from a file\n" <<
        "2 - Create new\n" <<
        "3 - Close the program\n" <<
        "\n----> ";
}

typedef void (*MenuOption) ();

void start_menu() {
    const MenuOption menuOptions[] = { load_from_file_choice, create_new_choice };

    while (Menu(show_start_menu, menuOptions, 2));
}

void load_from_file_choice() {
    ifstream* inFile;

    inFile = OpenBinForInput("Provide file name to load events from: ");

    if (inFile == NULL) {
        cout << "File wasnt opened" << endl;
        return;
    }

    cout << "File was opened, now loading events" << endl;

    my_db = LoadFromFileDB(inFile, &my_db_size);

    if (my_db == NULL) {
        cout << "Failed to read file" << endl;
        return;
    }

    cout << "Events were loaded, closing file" << endl;

    CloseFile(inFile);

    return edit_menu();

}

void create_new_choice() {
    my_db_size = default_size;

    my_db = CreateDB(my_db_size);

    return edit_menu();
}

void show_edit_menu() {
    cout << "Menu for evets db:\n\n" <<
        "1 - Add new events\n" <<
        "2 - Change event\n" <<
        "3 - Delete event\n" <<
        "4 - Show events\n" <<
        "5 - Save events to a file\n" <<
        "6 - Show and save free time\n" <<
        "7 - Return to start menu (loose all unsaved data)\n" <<
        "\n----> ";
}

void edit_menu() {

    const MenuOption menuOptions[] = { add_db_elements, change_db_element, del_db_element, show_events, save_to_file, save_free_time };

    while (Menu(show_edit_menu, menuOptions, 6));

    delete[] my_db;
}

void add_db_elements() {
    cout << "Input new elements (leave name empty to stop)" << endl;
    my_db = FillDB(my_db, &my_db_size, full_explanation);
    cout << "Done adding new elements\n\nNow sorting..." << endl;
    OrderDB(my_db, &my_db_size);
    cout << "Done sorting" << endl;
}

void change_db_element() {
    int index = 0;
    Event event_buff;

    cout << "Input event number to change: ";
    index = GetInt();

    if (index < 1) {
        cout << "!!!Input cant be less than 1!!!" << endl;
        return;
    }
    else if (index > my_db_size) {
        cout << "!!!Input cant be larger than " << my_db_size << "!!!" << endl;
        return;
    }

    cout << "Changing event " << my_db[index - 1].name << endl;

    event_buff = GetEvent(full_explanation);

    if (event_buff.name.empty()) { 
        cout << "Change canceled" << endl;
        return; 
    }

    my_db[index - 1] = event_buff;

    cout << "Done changing event" << endl;

    cout << "Now sorting..." << endl;
    OrderDB(my_db, &my_db_size);
    cout << "Done sorting" << endl;
}

void del_db_element() {
    int index = 0;

    cout << "Input event number to delete: ";
    index = GetInt();

    if (index < 1) {
        cout << "!!!Input cant be less than 1!!!" << endl;
        return;
    }
    else if (index > my_db_size) {
        cout << "!!!Input cant be larger than " << my_db_size << "!!!" << endl;
        return;
    }

    cout << "Deleting event " << my_db[index - 1].name << endl;

    DelElementDB(my_db, &my_db_size, index - 1);

    cout << "Done deleting event" << endl;
}

void show_events() {
    int now_timestamp;
    Event e_buff;

    cout << "These are your events for today:" << endl;

    ShowDB(my_db, &my_db_size, full_explanation);

    cout << endl;

    time_t now = time(0);

    tm* ltm = localtime(&now);

    now_timestamp = (ltm->tm_hour * def_section_val + ltm->tm_min) * def_section_val + ltm->tm_sec;

    e_buff = GetClosest(my_db, &my_db_size, now_timestamp);

    if (e_buff.name.empty()) {
        cout << "No more events for today" << endl;
    }
    else {
        cout << "This is the next event in schedule: " << EventToString(e_buff, full_explanation) << endl;
    }
}

void save_to_file() {
    ofstream* outFile;

    outFile = OpenBinForOut("Provide file name to save events to: ");

    if (outFile == NULL) {
        cout << "File wasnt opened" << endl;
        return;
    }

    cout << "File was opened, now saving events" << endl;

    SaveToFileDB(outFile, my_db, &my_db_size);

    cout << "Events were saved, closing file" << endl;

    CloseFile(outFile);
}

void save_free_time() {
    ofstream* outFile;
    string free_time_str;
    int time_stamp = 0;

    outFile = OpenForOut("Provide file name to save events to: ");

    if (outFile == NULL) {
        cout << "File wasnt opened" << endl;
        return;
    }

    cout << "File was opened" << endl;

    time_stamp = get_time("Provide time (hh:mm:ss): ", def_section_num, def_section_val, full_explanation);

    free_time_str = GetFreeTime(my_db, &my_db_size, time_stamp, day_seconds, full_explanation);

    cout << free_time_str;
    (*outFile) << free_time_str;

    CloseFile(outFile);
}