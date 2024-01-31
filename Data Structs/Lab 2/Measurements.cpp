#include <iostream>
#include <fstream>
#include "Measurements.h"
using namespace std;

Measurements& Measurements::operator=(const Measurements& other) {

    if (this == &other) {
        return *this;
    }

    arr = new double[other.measurements_amount];
    measurements_amount = other.measurements_amount;

    for (int i = 0; i <= other.measurements_amount; i++) {
        arr[i] = other.arr[i];
    }

    return *this;
}

Measurements::~Measurements() {
    //cout << "destructor called " << endl;
    delete[] arr;
}

bool Measurements::read(const char* filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return false;
    }

    if (file.bad()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        return false;
    }

    int count = 0;
    double value;
    while (file >> value) {
        count++;
    }

    arr = new double[count];
    measurements_amount = count;

    file.clear();
    file.seekg(0, ios::beg);

    for (int i = 0; i < count; ++i) {
        file >> arr[i];
    }

    file.close();
    return true;
}

void Measurements::print() {
    for (int i = 0; i < measurements_amount; i++) {
        cout << i << ":  " << arr[i] << endl;
    }
}

double Measurements::mean() {
    double total = 0;
    for (int i = 1; i < measurements_amount; i++) {
        total += arr[i];
    }
    return total / (measurements_amount - 1);
}

void Measurements::inc(double increment) {
    for (int i = 1; i < measurements_amount; i++) {
        arr[i] += increment;
    }
}
