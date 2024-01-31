// Lab5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
using namespace std;

class String {
public:
    int i = 0;
    String(const char* str = "") {
        while (str[i] != '\0') {
            i++;
        }

        c_string = new char[i + 1];
        i = 0;

        while (str[i] != '\0') {
            c_string[i] = str[i];
            i++;
        }

        c_string[i] = '\0';
    }

    String(const String& copy)
    {
        i = copy.i;
        c_string = new char[i + 1];
        for (int j = 0; j <= i; j++)
        {
            c_string[j] = copy.c_string[j];
        }
    }

    ~String() 
    {
        delete[] c_string;
        cout << "Destructor done" << endl;
    }

    void list() 
    {
        cout << "String: " << c_string << endl;
    }

    String operator+(const String& str) const {     // +
        int newLength = i + str.i;
        char* new_cstring = new char[newLength + 1];

        strcpy(new_cstring, c_string);
        strcat(new_cstring, str.c_string);

        String temp(new_cstring);
        return temp;
    }

    String& operator=(const String& str) {      // =
        if (this != &str) {
            delete[] c_string;
            c_string = new char[strlen(str.c_string) + 1];
            strcpy(c_string, str.c_string);
        }
        return *this;
    }

    String& operator++() {      // pre increment
        int new_length = i + 1;
        char* new_cstring = new char[new_length + 1];

        strcpy(new_cstring, c_string);
        new_cstring[i] = 'X';
        new_cstring[i + 1] = '\0';

        delete[] c_string;
        c_string = new_cstring;
        i++;
        return *this;
    }

    String operator++(int) {    // post increment
        String temp(*this);
        int new_length = i + 1;
        char* new_cstring = new char[new_length + 1];

        strcpy(new_cstring, c_string);
        new_cstring[i] = 'X';
        new_cstring[i + 1] = '\0';

        delete[] c_string;
        c_string = new_cstring;
        i++;

        return temp;
    }
    //String operator++(int) { // post inc
    //    String old = *this;

    //    *this = *this + String("X");

    //    return old;
    //}

    friend ostream& operator<<(ostream& out, const String& s) {     // << 
        cout << s.c_string;
        return out;
    }

    char& operator[](int index) {   // Indexing
        if (index < 0 || index > strlen(c_string) - 1) {
            cout << "Index out of bounds: Returning nothing" << endl;
            static char dummy = '\0';
            return dummy;
        }
        else {
            return c_string[index];
        }
    }

private:
    char* c_string;
};

void f(String& given_string)
{
    given_string.list();
}


// Exercise A main

//int main() {
//    String s1("abcedf");
//    String s2("ghijklmn");
//    String sum;
//    cout << "String 1 is: " << s1 << endl;
//    cout << "String 2 is: " << s2 << endl;
//    sum = s1 + s2;
//    cout << "Sum is: " << sum << endl;          // output should be abcdefghijklmn 
//    sum = sum;                                  // This should also work
//    cout << "Sum is still: " << sum << endl;    // output should still be abcdefghijklmn
//    return 0;
//}


// Exercise B1
 
int main() {
    String s("abcdefg");
    cout << s++ << endl;
    cout << ++s << endl;
    return 0;
}


// Exercise B2 
//int main() {
//    String s("abcdefg");
//    for (int i = 0; i < 7; i++)
//        cout << s[i] << " ";
//    cout << endl;
//    s[4] = 'X';
//    for (int i = 0; i < 7; i++)
//        cout << s[i] << " ";
//    return 0;
//}
