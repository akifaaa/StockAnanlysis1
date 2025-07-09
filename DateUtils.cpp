#include "DateUtils.h"
#include "StockRecord.h"
#include <sstream>
#include <iomanip>
#include <cstdlib>
 
Date::Date() : day(0), month(0), year(0) {}
 
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}
 
Date::Date(const std::string& dateStr) {
    *this = parse(dateStr);
}
 
Date Date::parse(const std::string& dateStr) {
    std::istringstream iss(dateStr);
    std::string token;
    int d, m, y;
 
    std::getline(iss, token, '-');
    d = std::atoi(token.c_str());
    std::getline(iss, token, '-');
    m = std::atoi(token.c_str());
    std::getline(iss, token);
    y = std::atoi(token.c_str());
 
    return Date(d, m, y);
}
 
std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << day << "-"
<< std::setfill('0') << std::setw(2) << month << "-"
<< std::setw(4) << year;
    return oss.str();
}
 
bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}
 
bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}
 
bool Date::operator<=(const Date& other) const {
    return *this < other || *this == other;
}
 
bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}
 
bool Date::operator>(const Date& other) const {
    return other < *this;
}
 
namespace DateUtils {
    bool isLeap(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
 
    int daysInMonth(int month, int year) {
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
            case 4: case 6: case 9: case 11: return 30;
            case 2: return isLeap(year) ? 29 : 28;
            default: return 0;
        }
    }
}
 
long Date::toDays() const {
    long days = 0;
    for (int y = 1; y < year; ++y) {
        days += (DateUtils::isLeap(y) ? 366 : 365);
    }
    for (int m = 1; m < month; ++m) {
        days += DateUtils::daysInMonth(m, year);
    }
    days += day;
    return days;
}
 
int Date::operator-(const Date& other) const {
    return static_cast<int>(this->toDays() - other.toDays());
}
 
 
namespace DateUtils {
    bool compareStockRecordByDateAsc(const StockRecord& a, const StockRecord& b) {
        return Date::parse(a.date) < Date::parse(b.date);
    }
 
    bool compareStockRecordByDateDesc(const StockRecord& a, const StockRecord& b) {
        return Date::parse(a.date) > Date::parse(b.date);
    }
}
