#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "timeseries.hpp"
#include "linkedlist.hpp"

/*
https://www.geeksforgeeks.org/how-to-dynamically-allocate-an-array-in-cpp/
https://www.geeksforgeeks.org/different-methods-to-initialize-a-linked-list/
https://www.w3schools.com/cpp/cpp_encapsulation.asp
https://www.tutorialspoint.com/cplusplus-program-to-implement-singly-linked-list
https://www.geeksforgeeks.org/binary-tree-in-cpp/
*/

void LinkedList::load(std::string country) {
    if (head != nullptr) {
        TimeSeries* current = head;
        while (current != nullptr) {
            TimeSeries* temp = current;
            current = current->getNext();
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }

    TimeSeries timeSeriesObj;

    std::ifstream file("lab2_multidata.csv");
    //read line of file into a string
    std::string line;
    int lineIndex = 0;
    
    while(std::getline(file, line)) {
        std::stringstream s_stream(line);
        std::string firstStr;
        std::getline(s_stream, firstStr, ',');

        lineIndex++;
        if (firstStr == country) {
            //add time series to a new node at the end of the LL:

            //new node has data = timeSeriesObj and next = nullptr
            TimeSeries* timeSeriesNode = new TimeSeries();
            timeSeriesNode->load(lineIndex);
            timeSeriesNode->setNext(nullptr);
            //if LL is empty, head and tail both point to new node
            if (tail == nullptr) {
                head = timeSeriesNode;
                tail = timeSeriesNode;
            }
            else {
                //current last node points to timeSeriesNode
                tail->setNext(timeSeriesNode);
                //tail also points to timeSeriesNode since it's the new last node in the LL
                tail = timeSeriesNode;
            }
        }
    }

    std::cout << "success" << std::endl;
}

void TimeSeries::load(int lineIndex) {
    std::ifstream file("lab2_multidata.csv");
    //read line of file into a string
    std::string line;

    //assign separate vars for index in the row of a file (fileIndex) and index in the time series (seriesIndex)
    int fileIndex = 0;
    int seriesIndex = 0;
    int year = 1960;
    int count = 0;
    if (lineIndex <= 0) {
        return;
    }
    while (std::getline(file, line)) {
        count++;
        if (count == lineIndex) {
            //create string stream from the string
            std::stringstream s_stream(line);
            //read each substring of the line separated by commas into a string
            std::string subLine;
            fileIndex = 0;
            while (std::getline(s_stream, subLine, ',')) {
                if (fileIndex == 0) {
                    countryName = subLine;
                }
                else if (fileIndex == 1) {
                    countryCode = subLine;
                }
                else if (fileIndex == 2) {
                    seriesName = subLine;
                }
                else if (fileIndex == 3) {
                    seriesCode = subLine;
                }
                else if (fileIndex > 3) {
                    if (seriesIndex >= dCap) {
                    int newCap = dCap * 2;

                    //double years array
                    double* newYears = new double[newCap];
                    for (int j = 0; j < dCap; j++) {
                        newYears[j] = years[j];
                    }
                    delete[] years;
                    years = newYears;

                    //double data array
                    double* newData = new double[newCap];
                    for (int j = 0; j < dCap; j++) {
                        newData[j] = data[j];
                    }
                    delete[] data;
                    data = newData;
                    dCap = newCap;
                    }
                    if (std::stod(subLine) != -1) { //ignore if data value is invalid
                        years[seriesIndex] = year; //fill in years array with values 1960 to 2023
                        data[seriesIndex] = std::stod(subLine); //convert string to double
                        seriesIndex++;
                    }
                    year++;
                }
                fileIndex++;
            }
        }
    }

    size = seriesIndex;

    //close file
    file.close();
}

void LinkedList::list() {
    if (head == nullptr) {
        return;
    }
    TimeSeries* current = head;
    std::cout << current->getCountryName() << " " << current->getCountryCode() << " ";
    while (current != nullptr) {
        std::cout << current->getSeriesName() << " ";
        current = current->getNext();
    }
    std::cout << std::endl;
}

void LinkedList::print(std::string Series_Code) {
    TimeSeries* current = head;
    int numberOfNodes = 0;
    int count = 0;
    while (current != nullptr) {
        if (current->getSeriesCode() == Series_Code) {
            current->print();
        }
        else {
            count++;
        }
        current = current->getNext();
        numberOfNodes++;
    }
    if (count == numberOfNodes) {
        std::cout << "failure" << std::endl;
        return;
    }
}

void TimeSeries::print() {
    if (size == 0) {
        std::cout << "failure" << std::endl;
    }
    else {
        for (int i = 0; i < size; i++) {
            if (data[i] != -1) {
                std::cout << "(" << years[i] << "," << data[i] << ") ";
            }
        }
        std::cout << "" << std::endl;
    }
}

void LinkedList::add(std::string Series_Code, double Y, double D) {
    TimeSeries* current = head;
    int numberOfNodes = 0;
    int count = 0;
    while (current != nullptr) {
        if (current->getSeriesCode() == Series_Code) {
            current->add(Y,D);
        }
        else {
            count++;
        }
        current = current->getNext();
        numberOfNodes++;
    }
    if (count == numberOfNodes) {
        std::cout << "failure" << std::endl;
        return;
    }
}

void TimeSeries::add(double y, double d) {
    bool existingData = false;
        //check if that year already exists in time series
        for (int i = 0; i < size; i++) {
            if (years[i] == y) {
                existingData = true;
            }
        }
        //if year doesn't already exist, create new arrays and copy elements in
        if (!existingData) {
            if (size == dCap) {
                int newCap = dCap + 1;
                double* newYears = new double[newCap];
                double* newData = new double[newCap];

                for (int i = 0; i < size; i++) {
                newYears[i] = years[i];
                newData[i] = data[i];
                }

                delete[] years;
                delete[] data;
                years = newYears;
                data = newData;
                dCap = newCap;
            }

            int index = 0;
            if (index >= size) {
                index = size - 1;
            }
            while (y > years[index] && index < size) {
                index++;
            }
            for (int i = size; i > index; i--) {
                years[i] = years[i - 1];
                data[i] = data[i - 1];
            }
            years[index] = y;
            data[index] = d;
            if (d != -1) {
                size++;
            }
            std::cout << "success" << std::endl;
        }
        else {
            std::cout << "failure" << std::endl;
        }
}

void LinkedList::update(std::string Series_Code, double Y, double D) {
    if (head == nullptr) {
        std::cout << "failure" << std::endl;
        return;
    }
    TimeSeries* current = head;
    int numberOfNodes = 0;
    int count = 0;
    while (current != nullptr) {
        if (current->getSeriesCode() == Series_Code) {
            current->update(Y,D);
        }
        else {
            count++;
        }
        current = current->getNext();
        numberOfNodes++;
    }
    if (count == numberOfNodes) {
        std::cout << "failure" << std::endl;
        return;
    }
}

void TimeSeries::update(double y, double d) {
    bool existingData = false;
    //check if that year already exists in time series
    for (int i = 0; i < size; i++) {
        if (years[i] == y) {
            existingData = true;

            //remove element if user inputs invalid data
            if (d == -1) {
                for (int j = i; j < size - 1; j++) { //shift everything to the left
                    years[j] = years[j + 1];
                    data[j] = data[j + 1];
                }
                size--;

                //resize array to be 1/2 of original capacity if number of elements in array is less than or equal to 1/4 of the original capacity
                if (size <= dCap / 4) {
                    int newCap = dCap / 2;
                    double* newYears = new double[newCap];
                    double* newData = new double[newCap];

                    for (int j = 0; j < size; j++) {
                        newYears[j] = years[j];
                        newData[j] = data[j];
                    }

                    delete[] years;
                    delete[] data;

                    years = newYears;
                    data = newData;
                    dCap = newCap;
                }
            }
            else {
                years[i] = y;
                data[i] = d;
            }
            std::cout << "success" << std::endl;
        }
    }
    if (!existingData) {
        std::cout << "failure" << std::endl;
    }
}

void LinkedList::deleteTS(std::string Series_Code) {
    if (head == nullptr) {
        std::cout << "failure" << std::endl;
        return;
    }

    //delete head node
    if (head->getSeriesCode() == Series_Code) {
        TimeSeries* temp = head;
        head = head->getNext();
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        std::cout << "success" << std::endl;
        return;
    }

    //delete a node elsewhere
    TimeSeries* current = head;
    while (current->getNext() != nullptr) {
        if (current->getNext()->getSeriesCode() == Series_Code) {
            TimeSeries* temp = current->getNext();
            current->setNext(current->getNext()->getNext());
            if (temp == tail) {
                tail = current;
            }
            delete temp;
            std::cout << "success" << std::endl;
            return;
        }
        current = current->getNext();
    }
    std::cout << "failure" << std::endl;
}

void LinkedList::biggest() {
    if (head == nullptr) {
        std::cout << "failure" << std::endl;
        return;
    }
    TimeSeries* current = head;
    std::string seriesCode;
    double biggestMean = -1;
    bool validData = false;

    while (current != nullptr) {
        double currentMean = current->mean();
        if (currentMean != 0) {
            validData = true;
            if (biggestMean < currentMean) {
                biggestMean = currentMean;
                seriesCode = current->getSeriesCode();
            }
        }
        current = current->getNext();
    }

    if (validData == false) {
        std::cout << "failure" << std::endl;
    } else {
        std::cout << seriesCode << std::endl;
    }
}

double TimeSeries::mean() {
    double M = 0;
    if (size == 0) {
        return 0;
    }
    else {
        for (int i = 0; i < size; i++) { //sum up all elements of array and divide by array size
            M += data[i];
        }
        M /= size;
        return M;
    }
}

bool TimeSeries::is_monotonic() {
    if (size == 0) {
        std::cout << "failure" << std::endl;
        return false;
    }
    bool increasing = true;
    bool decreasing = true;
    for (int i = 0; i < size - 1; i++) {
        if (data[i] >= data[i+1]) { //check if data is increasing
            increasing = false;
        }
        else if (data[i] <= data[i+1] ){ //check if data is decreasing
            decreasing = false;
        }
    }
    if (increasing || decreasing) {
        std::cout << "series is monotonic" << std::endl;
        return true;
    }
    else {
        std::cout << "series is not monotonic" << std::endl;
        return false;
    }
}

void TimeSeries::best_fit (double &m, double &b) {
    if (size == 0) {
        std::cout << "failure" << std::endl;
        m = 0;
        b = 0;
    }
    else {
        //m is slope, b is y-intercept
        double term1 = 0;
        double term2 = 0;
        double term3 = 0;
        double term4 = 0;
        double term5 = 0;

        for (int i = 0; i < size; i++) {
            term1 += years[i] * data[i];
            term2 += years[i];
            term3 += data[i];
            term4 += years[i] * years[i];
        }
        term5 =  term2;
        term1 *= size;
        term4 *= size;
        term5 *= term5;

        if (term4 - term5 == 0) {
            std::cout << "failure" << std::endl;
            m = 0;
            b = 0;
        }

        m = (term1 - (term2 * term3)) / (term4 - term5);
        b = (term3 - (m * term2)) / size;

        std::cout << "slope is " << m << " intercept is " << b << std::endl;
    }
}
