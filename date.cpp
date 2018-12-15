#include "date.h"

bool operator < (const Date& A, const Date& B){
    if (A.getYear()==B.getYear()) {
        if  (A.getMonth()==B.getMonth()) {
            return A.getDay()<B.getDay();
        } else return A.getMonth()<B.getMonth();
    } else return A.getYear()< B.getYear();
}

bool operator > (const Date& A, const Date& B){
    if (A.getYear()==B.getYear()) {
        if  (A.getMonth()==B.getMonth()) {
            return A.getDay()>B.getDay();
        } else return A.getMonth()>B.getMonth();
    } else return A.getYear()>B.getYear();
}

bool operator == (const Date& A, const Date& B){
    if (A.getYear()==B.getYear()) {
        if  (A.getMonth()==B.getMonth()) {
            return A.getDay()==B.getDay();
        } else return false;
    } else return false;
}

bool operator != (const Date& A, const Date& B){
    return !(A==B);
}

bool operator<= (const Date& A, const Date& B){
    return (A<B || A==B);
}

bool operator>= (const Date& A, const Date& B){
    return (A>B || A==B);
}

ostream& operator << (ostream& ost, const Date& date)
{
    char dash = '-';
    string y=to_string(date.getYear());
    string m=to_string(date.getMonth());
    string d=to_string(date.getDay());
    //add zeroes before year to make 4 digits
    for(size_t z = y.size(); z<4; ++z){
        ost << '0';
    }
    //year
    ost << y << dash;
    if(m.size()==1) ost << '0';
    //month
    ost << m << dash;
    if(d.size()==1) ost << '0';
    //day
    ost << d;

    //    ost <<  << dash <<  << dash <<  << " ";
    return ost;
}

Date ParseDate(istream& is){
    int year=0, month=0, day=0;
    char dash = '-';
    is >> year >> dash >> month >> dash >> day;
    return {year, month, day};
}

int Date::getDay() const {
    return day_;
}

int Date::getMonth() const {
    return month_;
}

int Date::getYear() const {
    return year_;
}
//bool Date::ovd() const {
//    return ovd_;
//}
