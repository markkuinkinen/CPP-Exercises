class Time {
public:
    int hours[2];
    int minutes[2];
    int h, m;

    /*explicit*/ Time(int givenHours = 0, int givenMinutes = 0);
    bool operator==(Time& other) const;
    void read();
    bool operator<(Time& other) const;
    bool operator>(Time& other) const;
    Time operator-(Time& other) const;
    Time& operator=(const Time& other);
    friend std::ostream& operator<<(std::ostream& out, const Time& p);
    friend std::istream& operator>>(std::istream& in, Time& p);
    Time operator+(Time& o) const;
};