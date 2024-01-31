#include <iostream>
#include <fstream>
#include "Measurements.h"
using namespace std;

//// Phase 1 main

const static char *filename = "C:/Users/MACHINE/Desktop/CPP Metro/DataStructs/Lab2/mea.dat";
int main(int argc, char *argv[]) {
    Measurements m;
    if (m.read(filename)) {
        m.print();
        cout << "Mean is " << m.mean() << endl;
    }
    else
        cout << "Can't open the file '" << filename << "'" << endl;
    return 0;
}

//// Phase 2 main

//int main(int argc, char* argv[]) {
//    const static char* filename = "C:/Users/MACHINE/Desktop/CPP Metro/DataStructs/Lab2/mea.dat";
//    Measurements m1, m2;
//    if (m1.read(filename)) {
//        m1.print();
//
//        m2 = m1;
//        m2.inc(0.1);
//
//        cout << "Mean m1 is " << m1.mean() << endl;
//        cout << "Mean m2 is " << m2.mean() << endl;
//    }
//    else
//        cout << "Can't open the file '" << filename << "'" << endl;
//
//    //m2.print();
//    return 0;
//}
