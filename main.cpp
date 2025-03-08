#include "timeseries.hpp"
#include "linkedlist.hpp"
#include <iostream>

int main() {
    LinkedList llObj;

    std::string input;
    while (true) {
        std::cin >> input;
        if (input == "LOAD") {
            std::cin.ignore();
            std::string country;
            std::getline(std::cin, country);
            llObj.load(country);
        }
        else if (input == "LIST") {
            llObj.list();
        }
        else if (input == "ADD") {
            std::string Series_Code;
            double Y;
            double D;
            std::cin >> Series_Code;
            std::cin >> Y;
            std::cin >> D;
            llObj.add(Series_Code,Y,D);
        }
        else if (input == "UPDATE") {
            std::string Series_Code;
            double Y;
            double D;
            std::cin >> Series_Code;
            std::cin >> Y;
            std::cin >> D;
            llObj.update(Series_Code,Y,D);
        }
        else if (input == "PRINT") {
            std::string Series_Code;
            std::cin >> Series_Code;
            llObj.print(Series_Code);
        }
        else if (input == "DELETE") {
            std::string Series_Code;
            std::cin >> Series_Code;
            llObj.deleteTS(Series_Code);
        }
        else if (input == "BIGGEST") {
            llObj.biggest();
        }
        else if (input == "EXIT") {
            break;
        }
    }

    return 0;
}
