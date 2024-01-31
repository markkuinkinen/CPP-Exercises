/* simple test program to test the queue implementation */
#include <iostream>
#include <conio.h>
#include "queue.h"

using namespace std;


// Application
int main() {
    Queue<char> queue;
    bool        succeed;
    char        chr;

    cout << "\nEnter a letter to be queued ";
    cout << "\nor digit 1 to dequeue a letter";
    cout << "\nor Return to quit a program\n";

    chr = _getche();
    while (chr != '\n' && chr != '\r') {
        if (isalpha(chr)) {
            succeed = queue.enqueue(chr);
            queue.print();
            if (!succeed)
                printf("\n Enqueue operation failed\n");
        }
        if (chr == '1') {
            succeed = queue.dequeue(chr);
            if (succeed) {
                cout << "\na letter dequeued " << chr << " ";
                queue.print();
            }
            else
                cout << "\nDequeue operation failed\n ";
        }
        chr = _getche();
    }

    return 0;
}
