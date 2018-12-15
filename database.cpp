#include "database.h"
//operator overloads for custom classes/structs used in database;

ostream& operator<< (ostream& ost, const Entry& entry)
{
    ost << entry.date << ' ' << entry.event;
    return ost;
}

ostream& operator<< (ostream& ost, const vector<Entry>& events){
    for (const Entry& e : events) {
        ost << e << endl;
    }
    return ost;
}

ostream& operator<< (ostream& ost, const vector<string>& events)
{
    for (const string& ev : events){
        ost << ev << " ";
    }
    return ost;
}

bool operator < (const Entry& A, const Entry& B){
    if (A.date==B.date) return (A.event<B.event);
    else return (A.date<B.date);
}
bool operator== (const Entry& A, const Entry& B){
    return (A.date==B.date)&&(A.event==B.event);
}
bool operator!= (const Entry& A, const Entry& B){
    return !(A==B);
}
bool operator== (const string& A, const Entry& B){
    stringstream ss;
    ss << B.date << ' ' << B.event;
    return (A==B.event || A==ss.str());
}
bool operator!= (const string& A, const Entry& B){
    return !(A==B);
}

//Database::

void Database::Add(const Date& date, const string& event)
{
    ///checking the set is probably sufficient
    if(/*eventsByDate_.count(date)==0 && */eventsUnique_.count({date, event})==0)
    {
        eventsByDate_[date].push_back(event);
        eventsUnique_.insert({date, event});
    }
    /* else if (! any_of(eventsByDate_[date].begin(),eventsByDate_[date].end(),
                        [event](const string& existing) {
                        return event == existing;}))
    {
        eventsByDate_[date].push_back(event);
    }*/
    //    else cout << "already in db" << endl;
}

void Database::Print(ostream& out) const
{
    for (const auto& Day : eventsByDate_){
        if(!Day.second.empty()) {
            for(const string& event : Day.second){
                //output date each time
                out << Day.first;
                //then the event
                out << " " << event << endl;
            }
        }
    }
}

string Database::Last(const Date& date) const
{
    string s="";
    if (date == Date{0,0,0}) throw std::invalid_argument("No entries");;
    //Find first greater than "date" and take prev
    auto firstGreaterIt = eventsByDate_.upper_bound(date);
    //    auto d = firstGreaterIt->first;
    //return no entries if empty or if no entries <=(before or at) "date"
    if (firstGreaterIt!=begin(eventsByDate_))
    {
        //the last date less or equal to date:
        auto lastNotGreaterIt = prev(firstGreaterIt);
        //if there are events at this date...(opposite should never occur)
        if ( ! lastNotGreaterIt->second.empty() ) {
            //            auto d2 = lastNotGreaterIt->first;
            stringstream ss;
            ss << lastNotGreaterIt->first;
            s = ss.str() + " " + lastNotGreaterIt->second.back();
        }
        return s;
    } else throw std::invalid_argument("No entries");
}
