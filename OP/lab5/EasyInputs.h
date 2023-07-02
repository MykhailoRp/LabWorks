#pragma once

typedef void (*MenuOption) ();
typedef void (*ShowMenu) ();

extern const bool Menu(ShowMenu show_prompt, const MenuOption choices[], const unsigned int menu_size);

extern int GetInt();
extern double GetDouble();

bool Y_N_Q();