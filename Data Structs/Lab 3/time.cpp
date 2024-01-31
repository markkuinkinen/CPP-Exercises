#include <iostream>
#include "time.h"
using namespace std;

Time::Time(int givenHours, int givenMinutes) {
    h = givenHours;
    m = givenMinutes;
}

bool Time::operator==(Time& other) const {
    if (this->h == other.h && this->m == other.m) {
        return true;
    }
    else {
        return false;
    }
}

void Time::read() {
    string input;
    while (true)
    {
        cin >> input;
        if (input.length() == 5 && input[2] == ':') {
            hours[0] = input[0] - '0';  // converting chars to ints
            hours[1] = input[1] - '0';
            minutes[0] = input[3] - '0';
            minutes[1] = input[4] - '0';

            h = (hours[0] * 10) + hours[1];
            m = (minutes[0] * 10) + minutes[1];

            if (h <= 24 && m <= 60) {   // this makes sure that the time is a real time
                if (h == 24 && m > 60) {
                    cout << "Incorrect format: HH:MM\nEnter time: ";
                }
                else {
                    break;
                }
            }
            else {
                cout << "Incorrect format: HH:MM\nEnter time: ";
            }
        }
        else {
            cout << "Incorrect format: HH:MM\nEnter time: ";
        }
    }
}


bool Time::operator<(Time& other) const {
    if (this->h < other.h) {
        return true;
    }
    else if (this->h > other.h) {
        return false;
    }
    else {
        if (this->m < other.m) {
            return true;
        }
        else if (this->m > other.m) {
            return false;
        }
        else {
            cout << "The times are the same." << endl;
            return false;
        }
    }
}

bool Time::operator>(Time& other) const {
    if (this->h > other.h) {
        return true;
    }
    else if (this->h < other.h) {
        return false;
    }
    else {
        if (this->m > other.m) {
            return true;
        }
        else if (this->m < other.m) {
            return false;
        }
        else {
            cout << "The times are the same." << endl;
            return false;
        }
    }
}

Time Time::operator-(Time& other) const {
    Time newTime;
    int temp_hours = this->h - other.h;
    int temp_minutes = this->m - other.m;

    if (temp_minutes < 0) {
        temp_minutes = 60 + temp_minutes;
        temp_hours -= 1;
    }

    newTime.h = temp_hours;
    newTime.m = temp_minutes;
    return newTime;
}

Time& Time::operator=(const Time& other) {
    if (this != &other) {   // might work don't know
        this->h = other.h;
        this->m = other.m;

        return *this;
    }
}

ostream& operator<<(ostream& out, const Time& p) {
    if (p.h < 10) {
        out << "0";
    }
    out << p.h << ":";
    if (p.m < 10) {
        out << "0";
    }
    out << p.m;
    return out;
}

istream& operator>>(istream& in, Time& p) {
    p.read();
    return in;
}

Time Time::operator+(Time& o) const {
    Time newTime;
    int temp_hours = this->h + o.h;
    int temp_minutes = this->m + o.m;

    if (temp_minutes > 60) {
        temp_minutes = temp_minutes - 60;
        temp_hours += 1;
    }

    newTime.h = temp_hours;
    newTime.m = temp_minutes;
    return newTime;
}