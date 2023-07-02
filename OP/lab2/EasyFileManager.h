#pragma once

using namespace std;

extern ifstream* OpenBinForInput(string prompt);
extern ofstream* OpenBinForOut(string prompt);

extern ifstream* OpenForInput(string prompt);
extern ofstream* OpenForOut(string prompt);

extern void CloseFile(ifstream* F);
extern void CloseFile(ofstream* F);