#include <iostream>
#include "dynlist.h"

using namespace std;

int main() {
	LinkedList<char> list;
	int order_no;
	char to_be_searched;
	list.delete_last();
	list.insert_to_end('?');
	list.delete_last();
	list.insert_to_end('x');
	list.insert_to_end('a');
	list.insert_to_end('b');
	list.insert_to_end('c');
	list.insert_to_end('d');
	list.insert_to_end('y');
	list.print();
	cout << "Enter first character to be searched\n";
	cin >> to_be_searched;
	if (list.find_pos(to_be_searched, order_no))
		cout << "The order no is " << order_no << endl;
	else
		cout << "Not found\n";
	cout << "Enter second character to be searced\n";
	cin >> to_be_searched;
	if (list.find_pos(to_be_searched, order_no))
		cout << "The order no is " << order_no << endl;
	else
		cout << "Not found\n";
	list.delete_first();
	cout << list;
	list.delete_last();
	cout << list;
	return (EXIT_SUCCESS);
}

//int main(void) {
//	LinkedList<char> list;
//	//char to_be_searched;
//	//int order_no;
//
//	list.insert_to_end('a').insert_to_end('d').insert_to_end('e').insert_to_end('c');
//	list.insert('b');
//	list.delete_last();
//
//	/*cout << "Enter first character to be searched\n";
//	cin >> to_be_searched;
//	if (list.find_pos(to_be_searched, order_no))
//		cout << "The order no is " << order_no << endl;
//	else
//		cout << "Not found\n";*/
//
//	cout << list;
//}
