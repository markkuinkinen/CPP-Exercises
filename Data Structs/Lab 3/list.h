#ifndef LAB3_LIST_H
#define LAB3_LIST_H

#endif //LAB3_LIST_H

#include <stdexcept>

#define  MAX 10

//Interface of the list
template <class T>
class List {
private:
    int count;
    T   array[MAX];
    void compress(T* array, int empty_slot, int n);

public:
    List();
    bool     empty();
    int      size();
    const T& operator[](int i) const;
    bool     insert_to_end(T item);
    bool     find_pos(T item, int* pos);
    bool     del(int orderNo);
    bool     insert_to_begin(T item);   //3A FUNCTION
    bool     insert(T item);            //3B FUNCTION
};



template<class T>
bool List<T>::insert(T item) {
    if (count == MAX) {
        return false;
    }

    insert_to_begin(item);

    // the classic bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {   // -i because the largest value will always be at the end
            // compare adjacent elements
            if (array[j] > array[j + 1]) {
                // Swap elements if they are in the wrong order
                T temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    cout << "Ascending order list:\n";
    for (int i = 0; i < count; i++) {
        cout << array[i] << endl;
    }

    return true;
}

template<class T>
bool List<T>::insert_to_begin(T item) {
    if (count == MAX) {
        return false;
    }

    for (int i = count; i > 0; i--) {
        array[i] = array[i - 1];
    }
    array[0] = item;
    count++;
    return true;
}


//Implementation of list
template<class T>
List<T>::List() {
    count = 0;
}

template <class T>
bool List<T>::empty() {
    return count == 0;
}

template <class T>
int List<T>::size() {
    return count;
}

template <class T>
const T& List<T>::operator[](int i) const {
    if (count > 0 && i <= count)
        return array[i - 1];
    else
        throw range_error("Index error");
}

template <class T>
bool List<T>::insert_to_end(T item) {
    if (count < MAX) {
        array[count++] = item;
        return true;
    }
    else
        return false;
}

template <class T>
bool List<T>::find_pos(T item, int* pos) {
    int i;

    for (i = 0; i < count; i++) {
        if (array[i] == item) {
            *pos = i;
            return true;
        }
    }

    return false;
}

template <class T>
bool List<T>::del(int orderNo) {
    if (orderNo >= 0 && orderNo < count) {
        //take item out means nothing
        compress(array, orderNo, count);
        count--; 	// or should this be inside compress
        return true;
    }
    else
        return false;
}

// This is "private" low level function used to implement public
// operation function delete_item
template <class T>
void List<T>::compress(T* array, int empty_slot, int n) {
    int i;

    for (i = empty_slot + 1; i < n; i++)
        array[i - 1] = array[i];
}