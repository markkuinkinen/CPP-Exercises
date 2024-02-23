#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int randGen_1() {
    return rand() % 37 + 1;
}

class LottoGenerator {
public:
    int operator()() {
        int number;
        do {
            number = randGen_1();
        } while (find(numbers.begin(), numbers.end(), number) != numbers.end());
        numbers.push_back(number);
        return number;
    }
private:
    vector<int> numbers;
};

int main() {
    srand(time(NULL));

    vector<int> first_lotto(7);
    generate_n(first_lotto.begin(), first_lotto.size(), randGen_1);

    cout << "First lotto row: ";
    copy(first_lotto.begin(), first_lotto.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    vector<int> second_lotto(7);
    generate_n(second_lotto.begin(), second_lotto.size(), randGen_1);

    cout << "Second lotto row: ";
    copy(second_lotto.begin(), second_lotto.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    sort(first_lotto.begin(), first_lotto.end());   // sort both lotto vectors
    sort(second_lotto.begin(), second_lotto.end());

    vector<int> intersection;
    set_intersection(first_lotto.begin(), first_lotto.end(),
                     second_lotto.begin(), second_lotto.end(),
                     back_inserter(intersection));

    if (!intersection.empty()) {
        cout << "Same numbers:\n";
        int count = 1;
        for_each(intersection.begin(), intersection.end(),
            [&](int num) { cout << "#" << count++ << ": " << num << endl; });
    }
    else {
        cout << "No shared numbers found.\n";
    }

    return 0;
}