#include <iostream>
#include "Polinom.h"
#include "EasyInputs.h"

const unsigned int term = 5;

void Perform() {

    double change_val = 0, X_val = 0;

    Polinom P1(term);

    cout << "1rst + 2nd * X + 3rd * X^2 + 4th * X^3 ..." << endl;

    for (unsigned int i = 0; i < term; i++) {
        printf("Provide %dth coefficient for first polinominal: ", i+1);
        if(!P1.SetCoeff(GetDouble(), i)) i--;
    }

    cout << "P1: " << P1 << endl;

    double coefs2[term];

    for (unsigned int i = 0; i < term; i++) {
        printf("Provide %dth coefficient for second polinominal: ", i + 1);
        coefs2[i] = GetDouble();
    }

    Polinom P2(term, coefs2);

    cout << "P2: " << P2 << endl;

    Polinom P3(P2);

    for (unsigned int i = 0; i < term; i++) {
        printf("Provide %dth coefficient for third polinominal: ", i + 1);
        if (!P3.SetCoeff(GetDouble(), i)) i--;
    }

    cout << "P3: " << P3 << endl << endl;

    cout << "P1: " << P1 << "\nP2: " << P2 << "\nP3: " << P3 << '\n';

    cout << "Value to change P1 and P2: ";
    change_val = GetDouble();

    P1 += change_val;
    P2 -= change_val;

    cout << "X value for P3: ";
    X_val = GetDouble();

    cout << P3 << ", X = " << X_val << ": " << P3.PutX(X_val) << '\n';

    cout << "P1: " << P1 << "\nP2: " << P2 << "\nP3: " << P3 << '\n';

    Polinom P4 = P1 + P2;
    P4 = P3;
    cout << "P4: " << P4 << endl;

}

int main()
{
    bool resp = true;
    do {
        Perform();
        cout << "Perform again?" << endl;
        resp = Y_N_Q();
    } while (resp);
}
