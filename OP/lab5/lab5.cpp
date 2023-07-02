#include <iostream>
#include "MyVect.h"
#include "EasyInputs.h"
#include "slib.h"
//#define arr_size 7 //???

int main()
{
    const int arr_size = 7; // task requirements

    TVector * vectors[arr_size];
    
    do {
        Input_Vector(vectors, arr_size);

        cout << "\n\nNow caculating results...\n\n";

        Calculate_Dist_Sum(vectors, arr_size);

        cout << "\n\n";

        Calculate_Vect_Sum(vectors, arr_size);

        ClearArr(vectors, arr_size);

        cout << "Perform again?\n";
    } while (Y_N_Q());
    
}