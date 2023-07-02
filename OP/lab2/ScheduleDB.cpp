#include <iostream>
#include <fstream>
#include <string>
#include "TimeTranslator.h"
#include "ScheduleDB.h"

using namespace std;

int GetLastElementIndexDB(Event* db, int* size) {
    int i = 0;
    while (db[i].name != "\0" && i < *size) i++;
    return i;
}

int GetActualSizeDB(Event* db, int* size) {
    return GetLastElementIndexDB(db, size) + 1;
}

Event* CreateDB(int size) {
    Event* db = new Event[size];

    for (int i = 0; i < size; i++) {
        db[i].name = "\0";
        db[i].time_start = 0;
        db[i].duration = 0;
    }

    return db;
}

Event* ExtendDB(Event* old_db, int* size) {

    Event* new_db = CreateDB((*size) * 2);

    for (int i = 0; i < *size; i++) {
        new_db[i] = old_db[i];
    }

    delete [] old_db;
    *size = (*size) * 2;
    return new_db;
}

Event* OptimizeDB(Event* old_db, int* size) {

    int actual_size;

    actual_size = GetActualSizeDB(old_db, size);

    Event* new_db = CreateDB(actual_size);

    for (int i = 0; i < actual_size; i++) {
        new_db[i] = old_db[i];
    }

    delete[] old_db;
    *size = actual_size;
    return new_db;
}

Event DelElementDB(Event* db, int* size, int index) {
    Event buff = db[index];

    for (int i = index; i < *size - 1; i++) {
        db[i] = db[i+1];
    }

    return buff;
}

void AddElementDB(Event* db, int index, Event buff) {
    db[index].name = buff.name;
    db[index].time_start = buff.time_start;
    db[index].duration = buff.duration;
}

int AppendElementDB(Event* db, int* size, Event buff) {
    int index = 0;
    index = GetLastElementIndexDB(db, size);

    AddElementDB(db, index, buff);

    return index;
}

Event GetEvent(const bool notif) {
    string name_buff;
    int time_s_buff, time_d_buff;

    cout << "Input event name (empty to stop): ";
    getline(cin, name_buff);

    if (notif) cout << "You entered: " << name_buff << endl;

    if (name_buff.empty()) return {"\0", 0, 0};

    time_s_buff = get_time("Input event start time (hh:mm:ss): ", def_section_num, def_section_val, notif);

    if (notif) cout << "You entered: " << time_s_buff << endl;

    time_d_buff = get_time("Input event duration (hh:mm:ss): ", def_section_num, def_section_val, notif);

    if (notif) cout << "You entered: " << time_d_buff << endl;

    return { name_buff, time_s_buff, time_d_buff };
}

Event* FillDB(Event* db, int* size, const bool notif) {
    int added = 0;
    int current_end = 0;

    Event event_buff;

    current_end = GetLastElementIndexDB(db, size);

    do {
        
        event_buff = GetEvent(notif);

        if (event_buff.name.empty()) break;

        added++;

        if ((current_end + added) >= *size) {
            db = ExtendDB(db, size);
        }

        AddElementDB(db, current_end + added - 1, event_buff);
    } while (true);

    return db;
}

Event GetClosest(Event* db, int* size, int time_sec) {
    int actual_size;

    actual_size = GetLastElementIndexDB(db, size);

    for (int i = 0; i < actual_size; i++) {
        if (time_sec < db[i].time_start) {
            return db[i];
        }
    }

    return { "\0", 0, 0 };
}

const string EventToString(Event e, const bool notif) {

    const string start_time = time_to_string(e.time_start, def_section_num, def_section_val, notif);
    const string duration_time = time_to_string(e.duration, def_section_num, def_section_val, notif);

    const int buff_size = int(e.name.size()) - 15 + int(start_time.size()) - 8 + int(duration_time.size()) - 8 + 35 + 3;

    char* buff = new char[buff_size];

    sprintf(buff, "%-15s %8s (%8s)", e.name.c_str(), start_time.c_str(), duration_time.c_str());

    const string s = buff;

    return s;
}

int TimeEnd(Event e) {
    return e.time_start + e.duration;
}

void ShowDB(Event* db, int* size, const bool notif) {

    int actual_size;

    actual_size = GetLastElementIndexDB(db, size);

    for (int i = 0; i < actual_size; i++) {
        cout << i+1 << " - " << EventToString(db[i], notif) << endl;
    }
    return;
}

const string GetFreeTime(Event* db, int* size, const int time_stamp, const int day_seconds, const bool notif) {
    string result;
    string buff;

    int actual_size, free_time, period_start_time;

    actual_size = GetLastElementIndexDB(db, size);

    int i = 0;

    while (db[i].time_start < time_stamp) i++;

    period_start_time = time_stamp;

    free_time = db[i].time_start - time_stamp;

    if (i > 0) {
        if ((time_stamp < TimeEnd(db[i - 1]))) {
            free_time = db[i].time_start - TimeEnd(db[i - 1]);
            period_start_time = TimeEnd(db[i - 1]);
        }
    }

    if (free_time > 0) {
        buff = time_to_string(period_start_time, def_section_num, def_section_val, notif) + " - " + time_to_string(db[i].time_start, def_section_num, def_section_val, notif) + " (" + time_to_string(free_time, def_section_num, def_section_val, notif) + ")";
        result += buff + '\n';
    }

    for (; i < actual_size - 1; i++) {

        free_time = db[i + 1].time_start - TimeEnd(db[i]);

        if (free_time > 0) {
            buff = time_to_string(TimeEnd(db[i]), def_section_num, def_section_val, notif) + " - " + time_to_string(db[i + 1].time_start, def_section_num, def_section_val, notif) + " (" + time_to_string(free_time, def_section_num, def_section_val, notif) + ")";
            result += buff + '\n';
        }
    }

    free_time = day_seconds - TimeEnd(db[i]);

    if (free_time > 0) {
        buff = time_to_string(TimeEnd(db[i]), def_section_num, def_section_val, notif) + " - 24:00:00 (" + time_to_string(free_time, def_section_num, def_section_val, notif) + ")";
        result += buff + '\n';
    }

    return result;
}

Event* LoadFromFileDB(ifstream* inFile, int* size) {
    int saved_size = 0;
    Event* loaded_db;

    char* c_buff;
    string name_buff;
    int str_size = 1;
    int time_s_buff = 0, time_d_buff = 0;
    
    if (!inFile->read((char*)&saved_size, sizeof(int))) {
        return NULL;
    }

    if (saved_size == NULL) return NULL;

    loaded_db = CreateDB(saved_size);

    for (int i = 0; i < saved_size; i++) {

        name_buff.clear();
        
        if (!inFile->read((char*)&str_size, sizeof(int))) break;
        c_buff = new char[str_size];
        if (!inFile->read(c_buff, str_size)) break;

        name_buff.append(c_buff, str_size);

        delete[] c_buff;

        if (!inFile->read((char*)&time_s_buff, sizeof(int))) break;
        if (!inFile->read((char*)&time_d_buff, sizeof(int))) break;

        AddElementDB(loaded_db, i, { name_buff , time_s_buff , time_d_buff });
    }

    (*size) = saved_size;

    return loaded_db;
}

int SaveToFileDB(ofstream* outFile, Event* db, int* size) {

    int db_to_save_size = GetActualSizeDB(db, size);

    outFile->write((char*)&db_to_save_size, sizeof(int));

    int str_size = 1;

    for (int i = 0; i < db_to_save_size; i++) {
        str_size = int(db[i].name.size());
        outFile->write((char*)&str_size, sizeof(int));
        outFile->write(db[i].name.c_str(), str_size);

        outFile->write((char*)&db[i].time_start, sizeof(int));
        outFile->write((char*)&db[i].duration, sizeof(int));
    }

    return 1;
}

void OrderDB(Event* db, int* size) {
    Event buff;
    int actual_size;

    actual_size = GetLastElementIndexDB(db, size);

    for (int i = 0; i < actual_size - 1; i++) {
        for (int j = 0; j < actual_size - i - 1; j++) {
            if (db[j + 1].time_start < db[j].time_start) {
                buff = db[j + 1];
                db[j + 1] = db[j];
                db[j] = buff;
            }
        }
    }
}