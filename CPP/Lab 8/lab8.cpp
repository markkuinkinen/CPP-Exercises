#include "counter.h"

// 8 MAIN
int main() {
    LimitedCounter counterA(0, 5);
    RoundupCounter counterB(0, 5);
    UseCounter(&counterA, 8);
    UseCounter(&counterB, 8);
    std::cout << "Counter A: " << counterA << std::endl; // output should be 5
    std::cout << "Counter B: " << counterB << std::endl; // output should be 2
    return 0;
}