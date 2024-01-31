#include <iostream>
using namespace std;

#include "time.h"
#include <conio.h>
#include "list.h"

void returnTimes(Time* times, int amount) {     // not a 'modification', but an addition
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
}


int main() {
    List<Time> list;
    Time       item, t;
    int        i = 0;

    cout << "(00:00 - Exit) Enter times (HH:MM):  ";
    cin >> item;

    while (!(item == Time(0, 0))) {
        //list.insert_to_end(item);
        //list.insert_to_begin(item);
        list.insert(item);
        cout << "(00:00 - Exit) Enter times (HH:MM):  ";

        cin >> item;
    }
    //Print the contents of the list
    for (i = 1; i <= list.size(); i++) {
        cout << "\n Item " << i << ": " << list[i];
    }
        
    cout << "\n(00:00 - Exit) Enter time to delete (HH:MM): ";
    cin >> item;
    while (!(item == Time(0, 0))) {
        if (list.find_pos(item, &i)) {
            cout << "\nList position: " << i << " - Time: " << list[i + 1] << " deleted.\n(00:00 - Exit) Enter time to delete (HH:MM): ";
            list.del(i);
        }
        else {
            cout << "\nItem not found\n(00:00 - Exit) Enter time to delete (HH:MM): ";
        }
        cin >> item;
    }

    //Print the contents of the list
    for (i = 1; i <= list.size(); i++) {
        cout << "\n Item " << i << ": " << list[i];
    }
    cout << endl;

    return 0;
}