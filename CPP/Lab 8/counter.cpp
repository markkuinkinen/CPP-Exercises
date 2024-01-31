#include "counter.h"

//Counter
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

bool Counter::operator<(int value) const {
    return count < value;
}

ostream& operator<<(ostream& out, const Counter& c) {
    out << c.count;
    return out;
}

// LimitedCounter
LimitedCounter::LimitedCounter(int initialValue, int limit) : Counter(initialValue), upperLimit(limit) {}

LimitedCounter& LimitedCounter::operator++() {
    if (count < upperLimit) {
        ++count;
    }
    return *this;
}

Counter LimitedCounter::operator++(int) {
    LimitedCounter old = *this;
    if (count < upperLimit) {
        count++;
    }
    return old;
}

// RoundupCounter   // LAB 8
RoundupCounter::RoundupCounter(int first, int last) : Counter(first), limit(last) {}

RoundupCounter& RoundupCounter::operator++() {
    if (count >= limit) {
        Counter::reset();
    }
    else {
        Counter::operator++();
    }
    return *this;
}

Counter RoundupCounter::operator++(int) {
    RoundupCounter temp = *this;
    if (count >= limit) {
        Counter::reset();
    }
    else {
        Counter::operator++();
    }
    return temp;
}

// UseCounter   // LAB 8
void UseCounter(Counter* counter, int times) {
    for (int i = 0; i < times; ++i) {
        Counter old = ++(*counter);
    }
}