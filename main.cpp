#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void TestAll();
//void TestDatabase();

string ParseEvent(istream& is)
{
    //can use getline...
    string event;
    std::getline(is, event);
    //event+=" ";
    for(size_t i = 0; i<event.size(); ++i){
        if(event[0] == ' ') event.erase(0, 1);
        else return event;
    }
    //    string event (std::istreambuf_iterator<char>(is), {});
    return event;
}

//void TestAll();

int main() {
   TestAll();
//    TestDatabase();

    Database db;

//    cout << "Database starts; Enter commands:" << endl;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const Date date = ParseDate(is);
            const string event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }
    return 0;
}

int DoRemove (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    return db.RemoveIf(predicate);
}

string DoFind (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    ostringstream os;
    for (const auto& entry : entries) {
        os << entry << endl;
    }
    os << entries.size();
    return os.str();
}

string DoPrint(Database& db){
    ostringstream os;
    db.Print(os);
    return os.str();
}


void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}
void TestRemove()
{
       Database db;
       db.Add({2017, 1, 1}, "first");
       db.Add({2017, 1, 1}, "second");
       db.Add({2017, 1, 1}, "third");
       db.Add({2017, 1, 1}, "fourth");
       db.Add({2017, 1, 1}, "five");
       AssertEqual(2, DoRemove(db, R"(event == "second" OR event == "fourth")"), "Remove several");
       AssertEqual("2017-01-01 first\n2017-01-01 third\n2017-01-01 five\n", DoPrint(db), "Check print after remove several- 3");
       cout << "TestRemove OK" << endl;
   }


void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
  TestRemove();
}
