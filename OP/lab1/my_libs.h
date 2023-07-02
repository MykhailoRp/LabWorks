#pragma once

using namespace std;

extern void show_stream_file_by_name(ifstream* FileToShow, string DisplayName);
extern void show_stream_file(ifstream* FileToShow);
extern void show_pointer_file_by_name(FILE* FileToShow, char* DisplayName);
extern void show_pointer_file(FILE* FileToShow);

extern int erase(char* line, int pos, int len);

extern char * insert(char* line, int pos, const char insertion[]);