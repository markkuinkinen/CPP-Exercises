// Lab7.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "counter.h"

Counter::Counter(int n0) {
    count = n0;
}

Counter& Counter::operator++() {
    count++;
    return *this;
}

Counter Counter::operator++(int) {
    Counter old = *this;
    count++;
    return old;
}

void Counter::reset() {
    count = 0;
}

int Counter::getCount() const {
    return count;
}

bool Counter::operator<(const Counter& c2) const {
    return count < c2.count;
}

ostream& operator<<(ostream& out, const Counter& c) {
    out << "\nCounter value is now " << c.count;
    return out;
}

// 7A LimitedCounter //
LimitedCounter::LimitedCounter(int initialValue, int limit) : counter(initialValue), upperLimit(limit) {}

LimitedCounter& LimitedCounter::operator++() {
	if (counter.getCount() < upperLimit) {
		++counter;
	}
	return *this;
}

LimitedCounter LimitedCounter::operator++(int) {
	LimitedCounter old = *this;
	if (counter.getCount() < upperLimit) {
		counter++;
	}
	return old;
}
ostream& operator<<(ostream& out, const LimitedCounter& lc) {
	out << lc.getCount();
	return out;
}


bool LimitedCounter::operator<(int value) const {
	return counter.getCount() < value;
}

void LimitedCounter::reset() {
	counter.reset();
}

int LimitedCounter::getCount() const {
	return counter.getCount();
}

void LimitedCounter::setLimit(int limit) {
	upperLimit = limit;
}


// LimitedCounter 
// 7B //
//LimitedCounter::LimitedCounter(int initialValue, int limit) : Counter(initialValue), upperLimit(limit) {}
//
//LimitedCounter& LimitedCounter::operator++() {
//    if (count < upperLimit) {
//        ++count;
//    }
//    return *this;
//}
//
//LimitedCounter LimitedCounter::operator++(int) {
//    LimitedCounter old = *this;
//    if (count < upperLimit) {
//        count++;
//    }
//    return old;
//}
//ostream& operator<<(ostream& out, const LimitedCounter& lc) {
//    out << lc.getCount();
//    return out;
//}
//
//
//bool LimitedCounter::operator<(int value) const {
//    return count < value;
//}
//
//void LimitedCounter::reset() {
//    count = 0;
//}
//
//int LimitedCounter::getCount() const {
//    return count;
//}
//
//void LimitedCounter::setLimit(int limit) {
//    upperLimit = limit;
//}

// 7A MAIN

int main() {
	LimitedCounter lc(0, 5); //initial value 0, upper limit 5
	cout << lc++ << endl; //output should be 0
	cout << ++lc << endl; //output should be 2
	lc.reset();
	for (int i = 0; i < 9; i++) {
		lc++;
		cout << lc << " "; //output is 1 2 3 4 5 5 5 5 5
	}
	cout << endl << lc.getCount() << endl; //output is 5
	cout << (lc < 7);//Testing the comparison operator //output is 1
	cout << (lc < 1);//Testing the comparison operator //output is 0
	return 0;
}


// 7B MAIN //
//int main() {
//    LimitedCounter lc(3, 5); // initial value 3, upper limit 5
//    cout << lc++ << endl;    // output should be 3
//    cout << ++lc << endl;    // output should be 5
//    lc.reset();
//    for (int i = 0; i < 9; i++) {
//        lc++;
//        cout << lc << " "; // output is 1 2 3 4 5 5 5 5 5
//    }
//    cout << endl << lc.getCount() << endl; // output is 5
//    cout << (lc < 7);              // Testing the comparison operator, output is 1
//    cout << (lc < 1);              // Testing the comparison operator, output is 0
//    return 0;
//}