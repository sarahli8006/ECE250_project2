#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>
#include <string>
#include "timeseries.hpp"

class LinkedList {
    private:
    TimeSeries* head;
    TimeSeries* tail;

    public:
    //constructor
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    //destructor
    ~LinkedList() {
        TimeSeries* current = head;
        while (current != nullptr) {
            TimeSeries* temp = current;
            current = current->getNext();
            delete temp;
        }
    }

    void load(std::string country);

    void list();

    void add(std::string Series_Code, double Y, double D);

    void update(std::string Series_Code, double Y, double D);

    void print(std::string Series_Code);

    void deleteTS(std::string Series_Code);

    void biggest();
};

#endif
