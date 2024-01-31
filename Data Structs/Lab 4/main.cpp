
#include <iostream>
#include <ctype.h>
#include "stack.h"

using namespace std;

int main() {
    Stack<int> input_list;
    char input = ' ';
    cout << "This is a RPN calculator. Enter operands and operators:\n";
    while (input != 'Q') {
        cout << "enter input: ";
        cin >> input;
        if (isdigit(input)) {
            input_list.push(input - '0');
        }
        else if (input == '+' || input == '-') {
            int first, second;
            if (input == '+') {
                input_list.pop(first);
                input_list.pop(second);
                input_list.push(first + second);
            }
            else {
                input_list.pop(first);
                input_list.pop(second);
                input_list.push(second - first);
            }
        }
        else if (input == '=') {
            input_list.print();
        }
        else if (!isdigit(input) && input != 'Q') {
            cout << "Not a digit! ";
        }
    }
    input_list.print();
}

