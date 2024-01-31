//Interface for ADT stack
#define MAXN 5
#include <iostream>
using namespace std;

template <class T>
class Stack {
private:
    T   array[MAXN];
    int top;
public:
	Stack();
	bool push(T item);
	bool pop(T &item);
	void print();
};


// Implementations of operation functions
template <class T>
Stack<T>::Stack() {
    top = -1;
}

template <class T>
bool Stack<T>::push(T item) {
    if (top >= MAXN - 1)
        return(false);
    else {
        array[++top] = item;
        return (true);
    }
}

template <class T>
bool Stack<T>::pop(T &item) {
    if (top == - 1)
        return(false);
    else {
        item = array[top--];
        return (true);
    }
}

template <class T>
void Stack<T>::print() {
    int i;

    cout << "\nStack is : ";
        for (i = top; i >= 0 ; i-- )
            cout << endl << array[i];

	cout << endl;
}
