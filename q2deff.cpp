#include "q2.h"
Time Time::operator+(const Time& t)
{
    int h = this->hrs + t.hrs;
    int m = mins + t.mins;
    int s = secs + t.secs;
    if (s > 59)
    {
        s -= 60;
        m += 1;
    }
    if (m > 59)
    {
        m -= 60;
        h += 1;
    }
    return Time(h, m, s);
}
Time Time::operator-(const Time& t)
{
    int h = this->hrs - t.hrs;
    int m = mins - t.mins;
    int s = secs - t.secs;

    return Time(h, m, s);
}
Time Time::operator*(int n)
{
    this->hrs* n;
    return Time(hrs, mins, secs);
}
void Time::operator++()
{
    this->secs += 1;
    if (secs > 59)
    {
        secs -= 60;
        mins += 1;
        if (mins > 59)
        {
            mins -= 60;
            hrs += 1;
        }
    }
}
bool Time::operator==(const Time& t)
{
    if (hrs == t.hrs && mins == t.mins && secs == t.secs)
        return true;
    return false;
}
bool Time::operator<(const Time& t)
{
    if (hrs < t.hrs)
        return true;
    else if (hrs == t.hrs)
    {
        if (mins < t.mins)
            return true;
        else if (mins == t.mins)
        {
            if (secs < t.secs)
                return true;
            return false;
        }
        return false;
    }
    return false;
}
ostream& operator<<(ostream& out, const Time& t)
{
    out << "Hrs: " << t.hrs << " Mins: " << t.mins << " Secs: " << t.secs;
    return out;
}
istream& operator>>(istream& i, Time& t)
{
    cout << "Enter Hrs: ";
    i >> t.hrs;
    cout << endl;
    cout << "Enter Mins: ";
    i >> t.mins;
    cout << endl;cout << "Enter Sec: ";
    i >> t.secs;
    cout << endl;
    return i;
}