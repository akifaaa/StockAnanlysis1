

/*
#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include <string>
// Forward declaration of StockRecord to avoid circular dependency
class StockRecord;

// A simple struct to represent a parsed date
struct Date {
    int day;
    int month;
    int year;

    // Constructor
    Date();
    Date(int d, int m, int y);

    // Parses a date string in the format "DD-MM-YYYY"
    static Date parse(const std::string& dateStr);

    // Comparison operators for sorting
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator>(const Date& other) const; // Added missing operator>

    // Converts back to string format
    std::string toString() const;
};

namespace DateUtils {
    // This function needs to be implemented.
    int yearsBetween(const Date& d1, const Date& d2);

    // Comparison functions for StockRecord based on date for C++03 compatibility
    bool compareStockRecordByDateAsc(const StockRecord& a, const StockRecord& b);
    bool compareStockRecordByDateDesc(const StockRecord& a, const StockRecord& b);
}

#endif // DATE_UTILS_H
*/






#ifndef DATE_UTILS_H
#define DATE_UTILS_H
 
#include <string>
#include <vector>
 
class StockRecord;
 
namespace DateUtils {
    bool isLeap(int year);
    int daysInMonth(int month, int year);
}
 
struct Date {
    int day;
    int month;
    int year;
 
    Date();
    Date(int d, int m, int y);
    Date(const std::string& dateStr);
 
    static Date parse(const std::string& dateStr);
 
    long toDays() const;
 
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator>(const Date& other) const;
 
    int operator-(const Date& other) const;
 
    std::string toString() const;
};
 
namespace DateUtils {
    bool compareStockRecordByDateAsc(const StockRecord& a, const StockRecord& b);
    bool compareStockRecordByDateDesc(const StockRecord& a, const StockRecord& b);
}
 
#endif // DATE_UTILS_H
