#ifndef TIMESERIES_HPP
#define TIMESERIES_HPP
#include <iostream>
#include <string>

class TimeSeries {
    private:
    std::string countryName;
    std::string countryCode;
    std::string seriesName;
    std::string seriesCode;
    int yCap = 2;
    int dCap = 2;
    double* years;
    double* data;
    int size = 0;
    TimeSeries* next;

    public:
    //constructor
    TimeSeries() {
        years = new double[yCap];
        data  = new double[dCap];
        next = nullptr;
    }

    //destructor
    ~TimeSeries() {
        delete[] years;
        delete[] data;
        years = nullptr;
        data = nullptr;
    }

    //getters to get time series pointer, country name, country code, series name, and series code
    TimeSeries* getNext() const {
        return next;
    }
    std::string getCountryName() const {
        return countryName;
    }
    std::string getCountryCode() const {
        return countryCode;
    }
    std::string getSeriesName() const {
        return seriesName;
    }
    std::string getSeriesCode() const {
        return seriesCode;
    }

    //setter to set time series pointer
    void setNext(TimeSeries* n) {
        next = n;
    }

    void load(int lineIndex);

    void print();

    void add(double y, double d);

    void update(double y, double d);

    double mean();

    bool is_monotonic();

    void best_fit (double &m, double &b);
};

#endif
