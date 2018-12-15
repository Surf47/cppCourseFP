#include "node.h"

//Node::
//made virtual?
//bool Node::Evaluate(const Date& date, const string& event) const {
//    //if ()
//    return true;
//}

//EmptyNode::
bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

//DateComparisonNode::
//constructor only init-s the date & cmp members for comparison with input
DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
    : date_(date), cmp_(cmp) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    //    if(date.ovd()) return true;
    switch (cmp_)
    {
    case Comparison::Less:
        return date<date_;

    case Comparison::Equal:
        return date==date_;

    case Comparison::Greater:
        return date>date_;

    case Comparison::NotEqual:
        return !(date==date_);

    case Comparison::LessOrEqual:
        return (date<date_ || date==date_);

    case Comparison::GreaterOrEqual:
        return (date>date_ || date==date_);
    }
}
//EventComparisonNode::
EventComparisonNode::EventComparisonNode (const Comparison& cmp, const string& event)
    : event_(event), cmp_(cmp) {}
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    //    if(event == "ignore_event_") return true;
    switch (cmp_)
    {
    case Comparison::Less:
        return event<event_;

    case Comparison::Equal:
        return event==event_;

    case Comparison::Greater:
        return event>event_;

    case Comparison::NotEqual:
        return !(event==event_);

    case Comparison::LessOrEqual:
        return (event<event_ || event==event_);

    case Comparison::GreaterOrEqual:
        return (event>event_ || event==event_);
    }
}
//LogicalOperationNode::
//constructors...but weird
LogicalOperationNode::LogicalOperationNode(const LogicalOperation& lop,
                                           const shared_ptr<Node>& left,
                                           const shared_ptr<Node>& parsed)
    : op_(lop), left_(left), parsed_(parsed) {}
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    if (op_ == LogicalOperation::And) {
        bool ret = (left_->Evaluate(date, event) && parsed_->Evaluate(date,event));
        return ret;
    }
    else return (left_->Evaluate(date, event) || parsed_->Evaluate(date,event));
}
