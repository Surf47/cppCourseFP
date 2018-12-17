#pragma once

#include "date.h"
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
//#include <functional>

using namespace std;
//e.g.
//template <typename Functor>
//bool Predicate(Functor functor)
//{
//    functor();
//}

struct Entry{
    Date date;
    string event;
};

ostream& operator<< (ostream& ost, const Entry& entry);
ostream& operator<< (ostream& ost, const vector<Entry>& events);
ostream& operator<< (ostream& ost, const vector<string>& events);

bool operator < (const Entry& A, const Entry& B);
bool operator== (const Entry& A, const Entry& B);
bool operator== (const Entry& A, const Entry& B);
bool operator!= (const Entry& A, const Entry& B);
bool operator== (const string& A, const Entry& B);
bool operator!= (const string& A, const Entry& B);

class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& out) const;
    template <typename Func>
    vector<Entry> FindIf(Func pred) const {
        vector<Entry> found;
        for (const auto& entry : eventsByDate_)
        {
            for(const auto& event : entry.second)
            {
                if (pred(entry.first, event)) found.push_back({entry.first, event});
            }
        }
        return found;
    }
    template <typename Func>
    int RemoveIf(Func pred){
        int total=0; //count1=0,
        for (auto& entry : eventsByDate_)
        {
            //const Date& d = entry.first;
            //if(pred(entry.first, "ignore_event_"))
            {
                int count=0,del=0;
                const Date& date = entry.first;
                //use partition..
                auto bound = stable_partition(entry.second.begin(),
                                              entry.second.end(),
                                              /*lambda predicate*/[date,pred](const string& event){
                    bool Erase = pred(date, event);
                    return !Erase;
                });
                if(bound!=entry.second.end()) del = entry.second.end()-bound;
                //            count1 += del;
                for(int i=0; i<del; ++i) {
                    if(!entry.second.empty()) {
                        Entry erz {date, entry.second.back()};
                        eventsUnique_.erase(erz);
                        entry.second.pop_back();
                        ++count;
                    }
                    else {
                        eventsByDate_.erase(date);
                    }
                }

                total+=count;
                // cout << "c1: " << count1 << " c2: " << count2 << endl;
                if(entry.second.empty()) eventsByDate_.erase(date);
            }
        }
        return total;
    }
    string Last(const Date& date) const;
private:
    map<Date, vector<string>> eventsByDate_;
    set<Entry> eventsUnique_;
};
