// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <climits>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Task 1
/*
int main()
{
	int userInput;
	cout << "Playing number game!\n";
	while (true) 
	{
		cout << "Enter a number: ";
		cin >> userInput;
		cout << "I won, mine is " << userInput + 1 << "!\n";
	}
}
*/

// Task 2
/*
int main()
{
	int userInput;
	cout << "Playing number game!\n";
	while (true) 
	{
		cout << "Enter a number: ";
		cin >> userInput;
		if (userInput == 0) 
		{
			break;
		}
		cout << "I won, mine is " << userInput + 1 << "!\n";
	}
	return 0;
}
*/

// Task 3
/*
int main()
{
	int userInput;
	cout << "Playing number game!\n";
	while (true)
	{
		cout << "Enter a number: ";
		cin >> userInput;
		if (userInput == 0)
		{
			break;
		}
		else if (userInput == INT_MAX)
		{
			cout << "It's a tie!\n";
			continue;
		}
		else
		{
			cout << "I won, mine is " << userInput + 1 << "!\n";
		}
	}
	return 0;
}
*/

// Task 4
/*
int main()
{
	int random_number, user_guess, guess_counter = 0;
	srand(time(NULL));
	random_number = rand() % 100 + 1;

	while (true) 
	{
		cout << "Guess a number (1-100): ";
		cin >> user_guess;
		guess_counter++;
		if (user_guess == random_number) 
		{
			cout << "Right! You made " << guess_counter << " guesses.";
			break;
		}
		else if (user_guess < random_number)
		{
			cout << "Too small!\n";
		}
		else
		{
			cout << "Too large!\n";
		}
	}
	return 0;
}
*/

// Task 5
/*
int main()
{
	int random_number, user_guess, guess_counter = 0, min_range, max_range;

	cout << "Type two numbers to determine the random range (min max): ";
	cin >> min_range >> max_range;

	srand(time(NULL));
	random_number =  rand() % max_range + min_range;

	while (true)
	{
		cout << "Guess a number (" << min_range << " - " << max_range << "): ";
		cin >> user_guess;
		guess_counter++;
		if (user_guess == random_number)
		{
			cout << "Right! You made " << guess_counter << " guesses.";
			break;
		}
		else if (user_guess < random_number)
		{
			cout << "Too small!\n";
		}
		else
		{
			cout << "Too large!\n";
		}
	}
	return 0;
}
*/

// Task 6
/*
int main() 
{
	cout << "An int has a size of " << sizeof(int) << " bytes\n";
	cout << "An unsigned int has a size of " << sizeof(unsigned int) << " bytes\n";
	cout << "A float has a size of " << sizeof(float) << " bytes\n";
	cout << "A double has a size of " << sizeof(double) << " bytes\n";
	cout << "A char has a size of " << sizeof(char) << " byte\n";
	cout << "A bool has a size of " << sizeof(bool) << " byte\n";

	return 0;
}
*/

// Task 7
/*
int main()
{
	int x = 10;
	int* y = &x;

	cout << "X memory address: " << y << endl;
	cout << "Y memory address: " << &y << endl;
	cout << "X value: " << x << endl;
	cout << "Y value: " << *y;

	return 0;
}
*/

// Task 8
/*
int main()
{
	char str[] = "Hello";
	int counter = 0;

	while (true) 
	{
		if (str[counter] == '\0')
		{
			cout << "The string is " << counter << " characters long.";
			break;
		}
		else
		{
			counter++;
		}
	}
	return 0;
}
*/

 //Task 9

int* find_largest(const int* table, int table_len)
{
	const int* largest = &table[0];

	for (int i = 0; i < table_len; i++)
	{
		if (table[i] > *largest)
		{
			largest = &table[i];
		}
	}
	return const_cast<int *>(largest);
}

int main()
{
	int table[] = { 2, 1, 10, 4, 3 };
	int* largest = find_largest(table, 5);

	cout << *largest;
}


// Task 10

//int main()
//{
//	int x = 15;
//	cout << "Line 1: " << x << endl;
//	int* y;
//	cout << "Line 2: " << x << endl;
//	y = &x;
//	cout << "Line 3: " << x << endl;
//	*y = *y + 3;
//	cout << "Line 4: " << x << endl;
//	int z = 2;
//	cout << "Line 5: " << x << endl;
//	int* w;
//	cout << "Line 6: " << x << endl;
//	w = y;
//	cout << "Line 7: " << x << endl;
//	y = 0;
//	cout << "Line 8: " << x << endl;
//	y = &z;
//	cout << "Line 9: " << x << endl;
//	*w = *w + *y;
//	cout << "Line 10: " << x << endl;
//	int t[] = { 9, 10 };
//	cout << "Line 11: " << x << endl;
//	y = t;
//	cout << "Line 12: " << x << endl;
//	*w += *y;
//	cout << "Line 13: " << x << endl;
//	y++;
//	cout << "Line 14: " << x << endl;
//	*w += *y;
//	cout << "Final line 15: " << x;
//}
