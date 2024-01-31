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

    ///////     EXERCISE 5a       ////////
    operator const char*() const {
        return c_string;
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


// Exercise 5a main

void main() {
    String s;
    char name[30];
    s = "Matti"; //Conversion c-string -> String
    cout << s << endl;
    strcpy(name, s); //Conversion String -> c-string
    cout << name;
}


// Exercise 5b

/*
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string find_field(const string& xml, const string& field) {
    size_t start_tag_pos = xml.find("<" + field + ">");
    if (start_tag_pos == string::npos) {
        return "";
    }

    size_t start = start_tag_pos + field.length() + 2;  // Move past the start tag
    size_t end_tag_pos = xml.find("</" + field + ">", start);

    if (end_tag_pos == string::npos) {
        return "";
    }

    return xml.substr(start, end_tag_pos - start);
}

int main() {
    string page, line, location, temperature;
    ifstream inputFile("weather.xml");

    while (getline(inputFile, line)) {
        page.append(line);
        line.erase();
    }

    // Now page is a string that contains the whole xml page
    // Here you need to write something that finds and 
    // extracts location and temperature from the XML
    // data in the string page and stores them in 
    // the strings location and temperature respectively

    location = find_field(page, "location");
    temperature = find_field(page, "temp_c");

    cout << "Location: " << location << endl;
    cout << "Temperature: " << temperature << endl;
}
*/
