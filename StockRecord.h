//
//
//
//#ifndef STOCK_RECORD_H
//#define STOCK_RECORD_H
//
//#include <string>
//
//class StockRecord {
//public:
//    std::string date;
//    std::string symbol;
//    std::string series;
//    double prevClose;
//    double open;
//    double high;
//    double low;
//    double last;
//    double close;
//    double vwap;
//    long volume;
//    double turnover;
//
//    StockRecord();  // Default constructor
//    StockRecord(
//        const std::string& date,
//        const std::string& symbol,
//        const std::string& series,
//        double prevClose,
//        double open,
//        double high,
//        double low,
//        double last,
//        double close,
//        double vwap,
//        long volume,
//        double turnover
//    );
//};
//
//#endif
//
//
//
//


#ifndef STOCK_RECORD_H
#define STOCK_RECORD_H

#include <string>

class StockRecord {
public:
    std::string date; 
    std::string symbol;  
    std::string series;  
    double prevClose;  
    double open; 
    double high;  
    double low;  
    double last;  
    double close;  
    double vwap;  
    long volume;  
    double turnover;  

    StockRecord(); // Default constructor 

    // Parametrized constructor 
    StockRecord(
        const std::string& date,
        const std::string& symbol,
        const std::string& series,
        double prevClose,
        double open,
        double high,
        double low,
        double last,
        double close,
        double vwap,
        long volume,
        double turnover
    );
};

#endif
