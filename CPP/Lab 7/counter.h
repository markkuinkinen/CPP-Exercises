/* Header file of Counter Class*/

#include <iostream>
using namespace std;

// Class definition
class Counter {
    friend ostream& operator<<(ostream& out, const Counter& c);

public:
    Counter(int n0 = 0);
    Counter& operator++();
    Counter operator++(int);
    bool operator<(const Counter& c2) const;
    void reset();
    int getCount() const;

protected:
    int count;
};

// LimitedCounter //          EXERCISE 7A
class LimitedCounter {
    friend ostream& operator<<(ostream& out, const LimitedCounter& c);
public:
    LimitedCounter(int first = 0, int last = 0);
    void reset();
    LimitedCounter& operator++();
    LimitedCounter operator++(int);
    int getCount() const;
    bool operator<(int value) const;
    void setLimit(int newLimit);

private:
    Counter counter;
    int limit, upperLimit;
};


//  EXERCISE 7B //
//class LimitedCounter : public Counter {
//    friend ostream& operator<<(ostream& out, const LimitedCounter& c);
//public:
//    LimitedCounter(int first = 0, int last = 0);
//    void reset();
//    LimitedCounter& operator++();
//    LimitedCounter operator++(int);
//    int getCount() const;
//    bool operator<(int value) const;
//    void setLimit(int newLimit);
//private:
//    int upperLimit;
//};
