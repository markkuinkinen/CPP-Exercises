#include <iostream>
using namespace std;

class Counter {
public:
    Counter(int n0 = 0);
    virtual void reset();
    virtual Counter& operator++(); // Pre-increment
    virtual Counter operator++(int); // Post-increment
    virtual int getCount() const;
    virtual bool operator<(int value) const;

    friend std::ostream& operator<<(std::ostream& out, const Counter& c);

protected:
    int count;
};

class LimitedCounter : public Counter {
public:
    LimitedCounter(int first = 0, int last = 0);
    LimitedCounter& operator++() override; // pre-increment
    Counter operator++(int) override;   // post-increment
private:
    int upperLimit;
};

class RoundupCounter : public Counter {
public:
    RoundupCounter(int first = 0, int last = 0);
    RoundupCounter& operator++() override; // pre
    Counter operator++(int) override;   // post
protected:
    int limit;
};

void UseCounter(Counter* counter, int times);