#include <iostream>
#include "HugeInteger.h"
using namespace std;

int main()
{
    HugeInteger A;
    HugeInteger B;

    cout << "Enter first number: ";
    cin >> A;

    cout << "Enter second number integer: ";
    cin >> B;
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "A+ B = " << A + B << endl;
    cout << "A - B = " << A - B << endl;
    cout << "A * B = " << A * B << endl;

    if (B != HugeInteger()){
        cout << "A / B = " << A / B << endl;
        cout << "A % B = " << A % B << endl;
    }

    cout << "Pre/Post inc and dec\n";

    HugeInteger C = A;

    cout << "C = " << C << endl;

    cout << "C++ = " << C++ << endl;
    cout << "After C++ -> " << C << endl;
    cout << "++C = " << ++C << endl;
    cout << "C-- = " << C-- << endl;
    cout << "After C-- -> " << C << endl;

    cout << "Comparisons"<<endl;

    if (A > B)
        cout << "A > B\n";
    else if (A < B)
        cout << "A < B\n";
    else
        cout << "A == B\n";

    return 0;
}
//int main(){
// 
//    HugeFraction A, B;
//
//    cout << "Enter fraction A: ";
//    cin >> A;
//    cout << "Enter fraction B: ";
//    cin >> B;
//    cout << "A = " << A << endl;
//    cout << "B = " << B << endl;
//
//    cout << "A+B = " << A + B << endl;
//    cout << "A-B = " << A - B << endl;
//    cout << "A*B = " << A * B << endl;
//    cout << "A/B = " << A / B << endl;
//
//    if (A > B)
//        cout << "A>B\n";
//    else
//        cout << "A<=B";
//    return 0;
//}