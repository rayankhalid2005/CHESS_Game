#pragma once
#include <iostream>
using namespace std;
class Time
{
private:
    int hrs, mins, secs;
public:
    Time() :hrs(0), mins(0), secs(0) {}
    Time(int h, int m, int s) :hrs(h), mins(m), secs(s) {}
    Time operator+(const Time& t);
    Time operator-(const Time& t);
    Time operator*(int n);
    void operator++();
    bool operator==(const Time& t);
    bool operator<(const Time& t);
    int getHrs()const { return hrs; }
    int getMins()const { return mins; }
    int getSecs()const { return secs; }
    friend ostream& operator<<(ostream& out, const Time& t);
    friend istream& operator>>(istream& i, Time& t);

};