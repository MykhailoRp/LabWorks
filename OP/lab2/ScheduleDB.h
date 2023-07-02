#pragma once

using namespace std;

struct Event {
    string name;
    int time_start = 0;
    int duration = 0;
};

extern Event* CreateDB(int size);

extern Event* ExtendDB(Event* old_db, int* size);
extern Event* OptimizeDB(Event* old_db, int* size);

extern Event GetEvent(const bool notif);
extern Event* FillDB(Event* db, int* size, const bool notif);

extern int AppendElementDB(Event* db, int* size, Event buff);
extern void AddElementDB(Event* db, int index, Event buff);
extern Event DelElementDB(Event* db, int* size, int index);

extern int GetLastElementIndexDB(Event* db, int* size);
extern int GetActualSizeDB(Event* db, int* size);

extern Event GetClosest(Event* db, int* size, int time_sec);
extern const string GetFreeTime(Event* db, int* size, int time_stamp, int day_seconds, const bool notif);

extern void ShowDB(Event* db, int* size, const bool notif);
extern const string EventToString(Event e, const bool notif);
extern int TimeEnd(Event e);

extern int SaveToFileDB(ofstream* outFile, Event* db, int* size);
extern Event* LoadFromFileDB(ifstream* inFile, int* size);

extern void OrderDB(Event* db, int* size);