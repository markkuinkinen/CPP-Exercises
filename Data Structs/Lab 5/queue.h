/* standard array queue implementation */
#include <iostream>

using namespace std;

// The interface of queue
template <class T>
class Queue {
private:
    int queue_size;
    T*  array;
    int number_of_items;

public:
    Queue();
    ~Queue();
    bool enqueue(T item);
    bool dequeue(T& item);
    void print();
};

      ////5A/////
template <class T>
Queue<T>::~Queue() {
    delete[] array;
}

// The implementation of queue
template <class T>
Queue<T>::Queue() {
    number_of_items = 0;
    queue_size = 5;
    array = new T[queue_size];
}


/////5A//////
template <class T>
bool Queue<T>::enqueue(T item) {
    if (number_of_items >= queue_size) {      // If number exceeds space, create larger array, copy contents, delete old array
        int larger_queue_size = queue_size + 5;

        T* larger_arr = new T[larger_queue_size];

        for (int i = 0; i < number_of_items; i++) {
            larger_arr[i] = array[i];
        }

        cout << "\nSize is increased and is now " << larger_queue_size << " items.";

        delete[] array;
        array = larger_arr;
        queue_size = larger_queue_size;
    }

    array[number_of_items++] = item;
    return (true);
}


template <class T>
bool Queue<T>::dequeue(T& item) {
    int i;

    if (number_of_items == 0)
        return(false);
    else {
        item = array[0];
        for (i = 0; i < number_of_items - 1; i++)
            array[i] = array[i + 1];
        number_of_items--;
        return (true);
    }
}

template <class T>
void Queue<T>::print() {
    int i;

    cout << "\nQueue now: \n\n";
    for (i = 0; i < number_of_items; i++) {
        cout << " " << array[i] << "";
    }
    cout << "\n\n";
}
