#pragma once

#include <iostream>
#include <sstream>
using namespace std;

class Date{
public:
    Date(int y, int m, int d) :
        year_(y), month_(m), day_(d) {}
    //    Date(bool override) :
    //        ovd_(override) {}

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    //    bool ovd() const;
private:
    const int year_=0;
    const int month_=0;
    const int day_=0;
    //    bool ovd_ = false;
};

Date ParseDate(istream& is);

bool operator < (const Date& A, const Date& B);
bool operator > (const Date& A, const Date& B);
bool operator == (const Date& A, const Date& B);
bool operator != (const Date& A, const Date& B);
bool operator <= (const Date& A, const Date& B);
bool operator >= (const Date& A, const Date& B);

ostream& operator << (ostream& ost, const Date& d);
istream& operator >> (istream& ost, const Date& d);
