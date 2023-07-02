#include <iostream>
#include <string>
#include "MyVect.h"
#include "Vec2.h"
#include "Vec3.h"
#include "EasyInputs.h"
#include "slib.h"

void Input_Vector(TVector** arr, static int arr_size) {
    double t_x = 0, t_y = 0, t_z = 0;

    for (int i = 0; i < 3; i++) {

        cout << "Intput x for vector " << i + 1 << ": ";
        t_x = GetDouble();
        cout << "Intput y for vector" << i + 1 << ": ";
        t_y = GetDouble();

        arr[i] = new Vec2(t_x, t_y);

        cout << "Result: " << arr[i]->to_str() << endl;
    }

    for (int i = 3; i < arr_size; i++) {

        cout << "Intput x for vector " << i + 1 << ": ";
        t_x = GetDouble();
        cout << "Intput y for vector" << i + 1 << ": ";
        t_y = GetDouble();
        cout << "Intput z for vector" << i + 1 << ": ";
        t_z = GetDouble();

        arr[i] = new Vec3(t_x, t_y, t_z);

        cout << "Result: " << arr[i]->to_str() << endl;
    }
}

void Calculate_Dist_Sum(TVector** arr, static int arr_size) {
    TVector* ref_vector = arr[0];

    cout << "Compairing on parallelism " << ref_vector->to_str() << ":\n";

    double dist_sum = 0;

    for (int i = 1; i < arr_size; i++) {

        cout << "Comparing to " << arr[i]->to_str() << " ==> Result: ";

        if (ref_vector->IsParallelTo(*arr[i])) {
            dist_sum += arr[i]->modul();
            cout << "TRUE, now sum = " << dist_sum;
        }
        else {
            cout << "FALSE, value will not be changed";
        }

        cout << endl;
    }

    cout << "\n================================\n" <<
        "RESULT: " << dist_sum
        << "\n================================\n";
}
void Calculate_Vect_Sum(TVector** arr, static int arr_size) {
    TVector* ref_vector = arr[3];

    cout << "Compairing on perpendicular " << ref_vector->to_str() << ":\n";

    Vec3 sum_res(0, 0, 0);

    for (int i = 0; i < arr_size; i++) {
        if (i == 3) continue;

        cout << "Comparing to " << arr[i]->to_str() << " ==> Result: ";

        if (ref_vector->IsPerpendTo(*arr[i])) {
            sum_res += *arr[i];
            cout << "TRUE, now sum = " << sum_res;
        }
        else {
            cout << "FALSE, value will not be changed";
        }

        cout << endl;
    }

    cout << "\n================================\n" <<
        "RESULT: " << sum_res.to_str()
        << "\n================================\n";
}

void ClearArr(TVector** arr, static int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        delete arr[i];
    }
}