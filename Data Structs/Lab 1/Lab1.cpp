#include <iostream>
using namespace std;

//Exercise 1a

class Time {
public:
    int hours[2];
    int minutes[2];

    int h, m;

    void read(const char* sentence) {
        cout << sentence;
        string input;
        while (true)
        {
            cin >> input;
            if (input.length() == 5 && input[2] == ':') {
                hours[0] = input[0] - '0';
                hours[1] = input[1] - '0';
                minutes[0] = input[3] - '0';
                minutes[1] = input[4] - '0';

                h = (hours[0] * 10) + hours[1];
                m = (minutes[0] * 10) + minutes[1];
                break;
            }
            else {
                cout << "Incorrect format: HH:MM\nEnter time: ";
            }
        }
    }

    void display() {
        if (h < 10) {
            cout << "0";
        }
        cout << h << ':';

        if (m < 10) {
            cout << "0";
        }
        cout << m << endl;
    }

    bool lessThan(Time& other) {
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

    Time subtract(Time& other) {
        Time newTime;
        newTime.h = this->h - other.h;
        newTime.m = this->m - other.m;
        return newTime;
    }

    Time& operator= (const Time& other) {
        this->h = other.h;
        this->m = other.m;

        return *this;
    }
};

int main() {
    Time time1, time2, duration;
    time1.read("Enter time 1: ");
    time2.read("Enter time 2: ");

    time1.display();
    time2.display();
    if (time1.lessThan(time2)) {
        duration = time2.subtract(time1);
        cout << "starting time was ";
        time1.display();
    } else {
        duration = time1.subtract(time2);
        cout << "starting time was: ";
        time2.display();
    }
    cout << "duration was: ";
    duration.display();
    return 0;
}


// Exercise 1B class, needed for C      


/*class Time {
public:
    int hours[2];
    int minutes[2];

    int h, m;

    Time(int givenHours = 0, int givenMinutes = 0) {
        h = givenHours;
        m = givenMinutes;
    }

    void read() {
        string input;
        while (true)
        {
            cin >> input;
            if (input.length() == 5 && input[2] == ':') {     // this makes sure time is in HH:MM format
                hours[0] = input[0] - '0';  // converting chars to ints
                hours[1] = input[1] - '0';
                minutes[0] = input[3] - '0';
                minutes[1] = input[4] - '0';

                h = (hours[0] * 10) + hours[1];
                m = (minutes[0] * 10) + minutes[1];

                if (h < 24 && m < 60) {   // this makes sure that the time is a real time
                    if (h == 24 && m > 0) {
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

    bool operator<(Time& other) const {
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

    Time operator-(Time& other) const {
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

    Time& operator=(const Time& other) {
        this->h = other.h;
        this->m = other.m;

        return *this;
    }

    friend ostream& operator<<(ostream& out, const Time& p) {
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

    friend istream& operator>>(istream& in, Time& p) {
        p.read();
        return in;
    }

    Time operator+(Time& o) const {
        Time newTime;
        int temp_hours = this->h + o.h;
        int temp_minutes = this->m + o.m;

        if (temp_minutes > 59) {
            temp_minutes = temp_minutes - 60;
            temp_hours += 1;
        }

        newTime.h = temp_hours;
        newTime.m = temp_minutes;
        return newTime;
    }
};
*/


// 1B Main
//int main() {
//    Time start, end, duration;
//    cout << "Enter starting time: "; cin >> start;
//    cout << "Enter ending time: "; cin >> end;
//    duration = start < end ? end - start : start - end;     // this logic in the code is weird to me, because we already specify the start and the end, start-end is very different to end-start as it would go follow over to the next day
//    cout << "Duration " << duration << endl;                // and i can't think of a way to differentiate that in the operator- function (so the output is incorrect if start > end)
//    cout << "Starting time was " << end - duration << endl;
//    cout << "Ending time was " << start + duration << endl;
//    return 0;
//}



// Exercise 1C

/*void returnTimes(Time* times, int amount) {     // not a 'modification', but an addition
    cout << "Results list: \n";
    Time tempTime;

    for (int x = 0; x < amount; x++) { // find winning time
        if (x == 0) {
            tempTime = times[x];
        }
        else if (times[x] < tempTime) {
            tempTime = times[x];
        }
    }

    for (int i = 0; i < amount; i++) {      // compare times
        cout << i + 1 << ": " << times[i] << "  ";
        cout << times[i] - tempTime << endl;
    }
}*/


// 1c Main

/*
int main() {
    int times_amount = 10;
    cout << "How many times do you have? ";
    while (true) {
        cin >> times_amount;
        if (times_amount <= 10 && times_amount > 0) {
            break;
        }
        else {
            cout << "Invalid input, enter int between 1-10: ";
        }
    }
    Time* given_times = new Time[times_amount];

    for (int i = 0; i < times_amount; i++) {
        cout << "Enter time " << i + 1 << " (HH:MM): ";
        cin >> given_times[i];
    }

    returnTimes(given_times, times_amount);

    return 0;
}
*/


