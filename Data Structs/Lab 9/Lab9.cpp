#include <map>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
using namespace std;

int main() {
    map<string, int> phone_book;
    vector<string> split_words;

    cout << "Phonebook application\n\n";
    while (true) {
        string input;
        getline(cin, input);

        istringstream splitter(input);              // put string into isstream to split
        string single_word;                         // string to insert into vector

        split_words.clear();                        // make sure vector is empty before adding to it
        while (splitter >> single_word) {           // while there are things to split, put into single word
            split_words.push_back(single_word);     // and push the separate results into the vector
        }

        if (split_words.empty()) {
            continue;
        }
        else if (split_words[0] == "add") {
            if (split_words.size() == 3) {                                                      // if there is one name
                phone_book[split_words[1]] = stoi(split_words[2]);
            }
            else if (split_words.size() == 4) {                                                 // if there are two names
                phone_book[split_words[1] + " " + split_words[2]] = stoi(split_words[3]);
            }
        }
        else if (split_words[0] == "list") {
            cout << "phonebook contains:\n";
            for (auto& info : phone_book) {
                cout << info.first << ": " << info.second << endl;
            }
        }
        else if (split_words[0] == "delete") {
            if (split_words.size() >= 2) {                          // check if there is at least one name to delete
                string full_name;
                for (size_t i = 1; i < split_words.size(); i++) {   // concat names if needed
                    full_name += split_words[i];
                    if (i != split_words.size() - 1) {              // Add space between names if not last name
                        full_name += " ";
                    }
                }
                auto name = phone_book.find(full_name);             // find entry with full name
                if (name != phone_book.end()) {                     // if check doesnt reach end of phonebook, delete name
                    phone_book.erase(name);
                    cout << full_name << " deleted.\n";
                }
                else {
                    cout << "Entry not found: " << full_name << endl;
                }
            }

        }
        else {
            cout << "Unrecognized command: " << split_words[0] << endl;
        }
    }
}
