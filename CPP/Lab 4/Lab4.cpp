#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

// Exercise 1

//class String {
//public:
//	String(const char* str) {
//		int i = 0;
//		for (i; i < 10 && str[i] != '\0'; i++)
//		{
//			c_string[i] = str[i];
//		}
//		c_string[i] = '\0';
//	}
//
//	void list();
//
//private:
//	char c_string[11];
//};
//
//void String::list() 
//{
//	cout << "String: " << c_string << endl;
//}
//
//void f(String a) 
//{
//	a.list();
//}
//
//int main()
//{
//	String s("abcdefg");
//	s.list();
//	f(s);
//	s.list();
//	return 0;
//}



// Exercise 2

class String {
public:
    int i = 0;
    String(const char* str) {
        while (str[i] != '\0') 
        {
            i++;
        }

        c_string = new char[i + 1];
        i = 0;

        while (str[i] != '\0') 
        {
            c_string[i] = str[i];
            i++;
        }

        c_string[i] = '\0';
    }

    ~String() {
        delete[] c_string;
        cout << "Destructor done" << endl;
    }

    void list() {
        cout << "String: " << c_string << endl;
    }

private:
    char* c_string;
};


void f(String given_string)
{
	given_string.list();
}

int main()
{
	String s("abcdefg12345");
	s.list();       // this works as intended, printing the contents of "s"
	f(s);           // this calls a copy constructor which creates a shallow copy of "s" which has been passed to the function
                    // now "s" and "given_string" (a copy) share the same memory location 
	s.list();       // since f(s); called the destructor, now 's' points to (the previously shared) memory which is now invalid since the destructor deleted it, creating errors
	return 0;
}


// ERRORS //
//	_CrtIsValidHeapPointer(Block)
// Stack around the variable 's' was corrupted



// Exercise 3
/*
class String {
public:
    int i = 0;
    String(const char* str) {
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

    ~String() {
        delete[] c_string;
        cout << "Destructor done" << endl;
    }

    void list() {
        cout << "String: " << c_string << endl;
    }

private:
    char* c_string;
};


void f(String& given_string)      // now that it takes a reference to the String object, no copy contructor is called and no memory is shared
{
    given_string.list();
}

int main()
{
    String s("abcdefg12345");
    s.list();
    f(s);
    s.list();
    return 0;
}
*/


// Exercise 4
/*
class String {
public:
    int i = 0;
    String(const char* str) 
    {
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
        i = copy.i;                     // this copies 'i' which was used in the contructor
        c_string = new char[i + 1];     // creating memory for the copied object
        for (int j = 0; j <= i; j++)
        {
            c_string[j] = copy.c_string[j];     // this copies the chars into the new object's assigned memory
        }
    }

    ~String() {
        delete[] c_string;
        cout << "Destructor done" << endl;
    }

    void list() {
        cout << "String: " << c_string << endl;
    }

private:
    char* c_string;
};


void f(String given_string)
{
    given_string.list();
}

int main()
{
    String s("abcdefg12345");
    s.list();
    f(s);
    s.list();
    return 0;
}
*/

// the copy constructor fixes the memory issue by creating a "deep copy" of the object, giving it its own allocated memory,
// as opposed to the "shallow copy" (which shares the same memory location) it was making previously without the copy constructor


// Extra task

/*
#ifdef _DEBUG // Active only in Debug Configuration
#define _CRTDBG_MAP_ALLOC // Visual Studio Mem Leak detector activated
#include <crtdbg.h> // runtime debug functions are declared here
#endif

class String {
public:
    int i = 0;
    String(const char* str)
    {
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

    ~String() {
        delete[] c_string;
        cout << "Destructor done" << endl;
    }

    void list() {
        cout << "String: " << c_string << endl;
    }

private:
    char* c_string;
};

void f(int i) {
    String s("abcdefghijklmnopqrstuvwxyz");
    s.list();
}

int main()
{
    int i = 0;
    _CrtMemState memory; // C/C++ runtime memory management state storage
    while (i < 3) {
        f(i++);
        // dump memory management state
        _CrtMemCheckpoint(&memory); _CrtMemDumpStatistics(&memory);
    }
    _CrtDumpMemoryLeaks(); // check if there were memory leaks
    return 0;
}
*/

//    there are 27 bytes in each 'normal block', 26 for the alphabet +1 for the null terminator
//    it increases by 27 each time 'i' increases because it's creating another copy of the string object without being deallocated
//    memory thats allocated (in this case with 'new') should be deallocated or else the memory usage will increase over time
//
//    after the destructor is put back in, the dynamically created memory for each copy is cleared after every time list() is called, preventing memory leaks.
//    a special/custom constructor is required in this case because we're dynamically allocating memory and the compilers generic destructor doesn't free memory allocated with 'new'
     
