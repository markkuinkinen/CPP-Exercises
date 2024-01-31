using namespace std;

class Measurements {
public:
    double* arr;
    int measurements_amount;
    ~Measurements();
    bool read(const char* filename);
    void print();
    double mean();
    void inc(double increment);
    Measurements& operator=(const Measurements& other);
}; 