#pragma once

#include "token.h"
#include "date.h"

#include <memory>
#include <map>
#include <vector>
#include <string>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

class Node {
public:
    virtual ~Node(){}
    virtual bool Evaluate(const Date& date, const string& event) const=0;
private:
//?
};

class EmptyNode : public Node {
public:
    EmptyNode() {}
    bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
    //DateComparisonNode() {}
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const string& event) const;
private:
    const Date date_;
    const Comparison cmp_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const string& event);
    bool Evaluate(const Date& date, const string& event) const;
private:
    const string event_;
    const Comparison cmp_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& lop, const shared_ptr<Node>& left, const shared_ptr<Node>& parsed);
    bool Evaluate(const Date& date, const string& event) const;
private:
    const LogicalOperation op_;
    const shared_ptr<Node> left_;
    const shared_ptr<Node> parsed_;
};
