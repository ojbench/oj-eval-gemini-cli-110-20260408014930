#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date
{
private:
    int _year;
    int _month;
    int _day;

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int getDaysInMonth(int year, int month) const {
        if (month == 2 && isLeapYear(year)) return 29;
        return month_days[month];
    }

    bool isValid(int year, int month, int day) const {
        if (year < 1) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > getDaysInMonth(year, month)) return false;
        return true;
    }

public:
    Date() : _year(1900), _month(1), _day(1) {}

    Date(int yy, int mm, int dd) {
        if (isValid(yy, mm, dd)) {
            _year = yy;
            _month = mm;
            _day = dd;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }

    Date& operator++() {
        _day++;
        if (_day > getDaysInMonth(_year, _month)) {
            _day = 1;
            _month++;
            if (_month > 12) {
                _month = 1;
                _year++;
            }
        }
        return *this;
    }

    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }

    Date& operator--() {
        _day--;
        if (_day < 1) {
            _month--;
            if (_month < 1) {
                _month = 12;
                _year--;
            }
            _day = getDaysInMonth(_year, _month);
        }
        return *this;
    }

    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }

    Date operator+(int days) const {
        Date res = *this;
        if (days < 0) return res - (-days);
        while (days > 0) {
            int daysInMonth = res.getDaysInMonth(res._year, res._month);
            if (res._day + days <= daysInMonth) {
                res._day += days;
                days = 0;
            } else {
                days -= (daysInMonth - res._day + 1);
                res._day = 1;
                res._month++;
                if (res._month > 12) {
                    res._month = 1;
                    res._year++;
                }
            }
        }
        return res;
    }

    Date operator-(int days) const {
        Date res = *this;
        if (days < 0) return res + (-days);
        while (days > 0) {
            if (res._day > days) {
                res._day -= days;
                days = 0;
            } else {
                days -= res._day;
                res._month--;
                if (res._month < 1) {
                    res._month = 12;
                    res._year--;
                }
                res._day = res.getDaysInMonth(res._year, res._month);
            }
        }
        return res;
    }

    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }

    int operator-(const Date& other) const {
        Date d1 = *this;
        Date d2 = other;
        if (d1 < d2) {
            swap(d1, d2);
        }
        // Now d1 >= d2
        int days = 0;
        while (d2._year < d1._year || d2._month < d1._month) {
            int daysInMonth = d2.getDaysInMonth(d2._year, d2._month);
            days += daysInMonth - d2._day + 1;
            d2._day = 1;
            d2._month++;
            if (d2._month > 12) {
                d2._month = 1;
                d2._year++;
            }
        }
        days += d1._day - d2._day;
        return days;
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d._year << "-" << d._month << "-" << d._day;
        return os;
    }
};

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main()
{
    Test();
    return 0;
}
