// Lab3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <iostream>

using namespace std;

// Exercise 1

int* allocate_table(int n)
{
    int* array = new int[n];
    return array;
}


// Exercise 2

void read_values(int* t, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Write int " << i + 1 << "/" << n << ": ";
        cin >> t[i];
    }
}

int main() 
{
    const int arraySize = 3;
    int newArr[arraySize];
    read_values(newArr, arraySize);

    cout << "The array contains ints: ";
    for (int j = 0; j < arraySize; j++)
    {
        cout << newArr[j] << " ";
    }

    return 0;
}


// Exercise 3

void reverse(int* t, int n) 
{
    for (int i = 0; i < n / 2; i++) 
    {
        int temp = t[i];
        t[i] = t[n - i - 1];
        t[n - i - 1] = temp;
    }
}
/*
int main()
{
    int numbers[] = { 1, 2, 3, 4, 5, 6, 7 };

    reverse(numbers, sizeof(numbers)/sizeof(int));

    for (int i = 0; i < sizeof(numbers) / sizeof(int); i++) 
    {
        cout << numbers[i];
    }

    return 0;
}
*/

//Exercise 4

void print_values(const int* t, int n) 
{
    for (auto index = 0; index < n; index++)
    {
        cout << t[index];
    }
}
/*
int main() 
{
    int newArray[] = { 1, 3, 5, 7 };
    print_values(newArray, 4);

    return 0;
}
*/


//Exercise 5
/*
int main()
{
    int arraySize;
    cout << "Type integer size of array: ";
    cin >> arraySize;

    int* newArray = allocate_table(arraySize);
    read_values(newArray, arraySize);
    reverse(newArray, arraySize);
    print_values(newArray, arraySize);
    
    return 0;
}
*/


// Exercise 6

//global variables
const int global_arraySize = 5;
int global_array[global_arraySize];

//Modified functions
void new_read_values()
{
    for (int i = 0; i < global_arraySize; i++)
    {
        cout << "Write int " << i + 1 << "/" << global_arraySize << ": ";
        cin >> global_array[i];
    }
}

void new_reverse()
{
    for (int i = 0; i < global_arraySize / 2; i++)
    {
        int temp = global_array[i];
        global_array[i] = global_array[global_arraySize - i - 1];
        global_array[global_arraySize - i - 1] = temp;
    }
}

void new_print_values()
{
    for (auto index = 0; index < global_arraySize; index++)
    {
        cout << global_array[index] << " ";
    }
}
/*
int main()
{
    read_values();
    reverse();
    cout << "The array in reverse is: ";
    print_values();
    return 0;
}
*/

// Exercise 7

class Node 
{
    public:
        int data;
        Node* next;
};

void print_list(const Node *head) 
{
    while (head != nullptr) 
    {
        cout << head->data;
        head = head->next;
        cout << " ";
    }
}
/*
int main()
{
    Node* s4 = new Node;
    s4->data = 1; s4->next = nullptr;
    Node* s3 = new Node;
    s3->data = 2; s3->next = s4;
    Node* s2 = new Node;
    s2->data = 10; s2->next = s3;
    Node* s1 = new Node;
    s1->data = 3; s1->next = s2;
    Node* head = s1;

    print_list(head);
    return 0;
}
*/

// Exercise 8

Node* insert_first(Node* head, int value) 
{
    if (head == nullptr) 
    {
        head = new Node;
        head->data = value;
        head->next = nullptr;
    }
    else 
    {
        Node* newHead = new Node;
        newHead->data = value;
        newHead->next = head;
        head = newHead;
    }
    
    return head;
}
/*
int main() 
{
    Node* s4 = new Node;
    s4->data = 1; s4->next = nullptr;
    Node* s3 = new Node;
    s3->data = 2; s3->next = s4;
    Node* s2 = new Node;
    s2->data = 10; s2->next = s3;
    Node* s1 = new Node;
    s1->data = 3; s1->next = s2;
    Node* head = s1;

    print_list(head);
    cout << endl;

    head = insert_first(head, 22);

    print_list(head);
    return 0;
}
*/

// Exercise 9

void delete_list(Node* head)
{
    while (head != nullptr)
    {
        Node* tempNode = head;
        head = head->next;
        delete tempNode;
    }
    head = nullptr;
}
/*
int main()
{
    Node* s4 = new Node;
    s4->data = 1; s4->next = nullptr;
    Node* s3 = new Node;
    s3->data = 2; s3->next = s4;
    Node* s2 = new Node;
    s2->data = 10; s2->next = s3;
    Node* s1 = new Node;
    s1->data = 3; s1->next = s2;
    Node* head = s1;

    print_list(head);
    cout << endl;

    head = insert_first(head, 22);

    print_list(head);

    delete_list(head);
    return 0;
}
*/