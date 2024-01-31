/* dynlist.h -- Dynamic linked linear list */
#include <iostream>
using namespace std;

// Interface of list
template <class T>
class LinkedList {
private:
	// definition of the list node class
	class Node {
	public:
		T     _value;	// data
		Node* _pNext;	// pointer to the next node
		Node() : _pNext(NULL) {}
		Node(T val) : _value(val), _pNext(NULL) {}
		Node(T val, Node* next) : _value(val), _pNext(next) {}
	};

	Node* first;
	//Node* last;

public:
	LinkedList();
	~LinkedList();
	LinkedList<T>& insert_to_end(T data);
	void print(std::ostream& out = std::cout) const;
	
	////////EXERCISE 7A/////////
	void delete_first();
	void delete_last();
	bool find_pos(T item, int& pos);

	//////EXERCISE 7B///////
	bool insert(T item);
};

//////EXERCISE 7A////////
template <class T>
void LinkedList<T>::delete_first() {
	if (first != NULL) {
		Node* old_first = first;
		first = old_first->_pNext;

		delete old_first;
	}
}

template <class T>
void LinkedList<T>::delete_last() {
	if (first != NULL) {
		Node* current_node = first;
		Node* previous_node = NULL;						// second node to point to null after last is deleted

		while (current_node->_pNext != NULL) {			// cycles through nodes while keeping track of the second last one
			previous_node = current_node;				
			current_node = current_node->_pNext;
		}
		delete current_node;							// deletes final node and sets second last to point to null

		if (previous_node != NULL) {					
			previous_node->_pNext = NULL;				// update previous->_pNext to NULL IF there is a previous node
		}
		else {
			first = NULL;								// if NO previous node, that means there was only 1 node in the list
		}
	}
	else {
		cout << "List contains nothing.";				// if list is empty
	}
}

template <class T>
bool LinkedList<T>::find_pos(T item, int& pos) {
	int counter = 0;									// set up counter and node
	Node* search_node = first;
	
	while (search_node != NULL) {
		if (search_node->_value == item) {				// while list isnt empty, check if node value == item
			pos = counter;
			return true;
		}
		search_node = search_node->_pNext;				// cycle through nodes and increase counter
		counter++;
	}
	
	return false;
}

////////////END OF 7A//////////////

////////////EXERCISE 7B///////////

template <class T>
bool LinkedList<T>::insert(T item) {
	int counter = 0;
	insert_to_end(item);

	Node* counter_node = first;
	while (counter_node != NULL) {					// count all the nodes
		counter_node = counter_node->_pNext;
		counter++;
	}
	delete counter_node;							

	Node* current_node;
	Node* next_node;
	Node* temp_node = NULL;

	for (int i = 0; i < counter - 1; i++) {						// sorting through pairs of nodes
		current_node = first;
		next_node = current_node->_pNext;

		for (int x = 0; x < counter - 1 - i; x++) {				// sorts through unsorted nodes

			if (current_node->_value > next_node->_value) {		// compares current and next node values, if {current > next} swap;
				if (temp_node != NULL) {						// check if temp points to node
					temp_node->_pNext = next_node;				// if it does, make it point to the next 
				}												
				else {
					first = next_node;							// if temp is NULL then we're at the beginning of the list, so we update the first pointer
				}

				current_node->_pNext = next_node->_pNext;		// swap current and next node pointers
				next_node->_pNext = current_node;

				temp_node = next_node;							// update temp and next for following loop
				next_node = current_node->_pNext;
			}
			else {												// else nodes are in the correct order
				temp_node = current_node;
				current_node = next_node;						// update temp, current, next for next loop
				next_node = next_node->_pNext;
			}
		}
	}
	return true;
}

////////////END OF 7B///////////////

// Implementation of list
template <class T>
LinkedList<T>::LinkedList() {
	first = NULL;
	//last = NULL;
}

template <class T>
LinkedList<T>::~LinkedList() {
	Node* aux1, * aux2;

	aux1 = first;
	while (aux1 != NULL) {
		aux2 = aux1->_pNext;
		delete aux1;
		printf("\nDeleted"); //for testing purposes
		aux1 = aux2;
	}
}


template <class T>
LinkedList<T>& LinkedList<T>::insert_to_end(T data) {
	Node* newnode = new Node(data);
	if (first == NULL)
		first = newnode;		//first node
	else {
		Node* current = first;
		while (current->_pNext != nullptr) {
			current = current->_pNext;
		}
		current->_pNext = newnode;
	}
	return *this;
}

template <class T>							// Didn't work with this
void LinkedList<T>::print(std::ostream& out /* = std::cout*/) const {
	Node* what;

	out << "\nList:";
	what = first;
	while (what != NULL) {
		out << " " << what->_value << " ";
		what = what->_pNext;
	}
	out << endl;
}

template <class T>
std::ostream& operator<<(std::ostream& out, LinkedList<T> const& data) {
	data.print(out);
	return out;
}