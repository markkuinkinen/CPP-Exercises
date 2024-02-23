#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
private:
	class Node {
	public:
		T     _value;	// data
		Node* _pNext;	// pointer to the next node
		Node* _pPrevious;
		Node() : _pNext(NULL), _pPrevious(NULL) {}
		Node(T val) : _value(val), _pNext(NULL), _pPrevious(NULL) {}
		Node(T val, Node* next, Node* previous) : _value(val), _pNext(next), _pPrevious(previous) {}
	};

	Node* first;
	Node* last;

public:
	LinkedList() {
		first = nullptr;
		last = nullptr;
	}

	void insert_to_front(const T& value) {
		Node* newNode = new Node(value, first, nullptr);
		if (!last) {
			last = newNode;		// if list is empty, the new node becomes first and last
		}
		else {
			first->_pPrevious = newNode;
		}
		first = newNode;		 // update first to point to the new node
	}

	void insert_to_back(const T& value) {
		Node* newNode = new Node(value, nullptr, last);
		if (!last) {
			first = newNode;
		}
		else {
			last->_pNext = newNode;
		}
		last = newNode;	
	}

	void print() {
		Node* current = first;
		cout << "List: ";
		while (current) {		// loop until current is null
			cout << current->_value << " ";
			current = current->_pNext;
		}
		cout << endl;
	}

	void print_reverse() {
		Node* current = last;
		cout << "List: ";
		while (current) {
			cout << current->_value << " ";
			current = current->_pPrevious;
		}
		cout << endl;
	}
	
};