///*
//
//#ifndef CSVREADER_H
//#define CSVREADER_H
//
//#include <string>
//#include <vector>
//#include "DateUtils.h" // NEW: Include the centralized Date struct
//
//struct StockRecord {
//    std::string date, symbol, series;
//    float prevClose, open, high, low, last, close, vwap;
//    long volume;
//    double turnover;
//};
//
//// CSVReader handles reading and filtering
//class CSVReader {
//private:
//    std::vector<StockRecord> records;
//
//public:
//    bool readCSV(const std::string& filename);
//    // Changed return types to vector for consistent main.cpp display
//    std::vector<StockRecord> getFirstNRows(int n) const;
//    std::vector<StockRecord> filterByDateRange(const std::string& s, const std::string& e) const;
//    void sortByDate(bool asc);
//    std::vector<StockRecord> getFilteredSymbolRecords(const std::string& symbol, const std::string& s, const std::string& e) const;
//    std::vector<StockRecord> getRecords() const;
//};
//
//// Global helper display functions (kept in main.cpp for centralization)
//// void printStockHeader(); // REMOVED from here
//// void printStockRow(const StockRecord& r); // REMOVED from here
//
//#endif
// 
//*/
//
//
//
//
//
//
//#ifndef CSVREADER_H
//#define CSVREADER_H
//
//#include "CSVReaderBase.h"
//#include "StockRecord.h"
//#include <vector>
//#include <string>
//
//class CSVReader : public CSVReaderBase {
//private:
//    std::vector<StockRecord> records;
//
//public:
//    bool readCSV(const std::string& filename);
//    std::vector<StockRecord> getRecords() const;
//
//    // For sorting/filtering interface compatibility
//    std::vector<StockRecord> getFirstNRows(int n) const;
//    std::vector<StockRecord> filterByDateRange(const std::string& start, const std::string& end) const;
//    std::vector<StockRecord> getFilteredSymbolRecords(const std::string& symbol, const std::string& start, const std::string& end) const;
//    void sortByDate(bool ascending);
//};
//
//#endif
//
//
//
//



//#ifndef CSVREADER_H
//#define CSVREADER_H
//
//#include "CSVReaderBase.h"
//#include "StockRecord.h" // Already present 
//#include <vector>
//#include <string>
//
//class CSVReader : public CSVReaderBase {
//private:
//    std::vector<StockRecord> records; // 
//
//public:
//    bool readCSV(const std::string& filename); // 
//    std::vector<StockRecord> getRecords() const; // 
//    // For sorting/filtering interface compatibility
//    std::vector<StockRecord> getFirstNRows(int n) const; // 
//    std::vector<StockRecord> filterByDateRange(const std::string& start, const std::string& end) const; // 
//    std::vector<StockRecord> getFilteredSymbolRecords(const std::string& symbol, const std::string& start, const std::string& end) const; // 
//    void sortByDate(bool ascending); // 
//};
//
//#endif



#ifndef CSVREADER_H
#define CSVREADER_H
 
#include "CSVReaderBase.h"
#include "StockRecord.h"
#include <vector>
#include <string>
 
class CSVReader : public CSVReaderBase {
private:
    std::vector<StockRecord> records;
 
public:
    bool readCSV(const std::string& filename);
    std::vector<StockRecord> getRecords() const;
    std::vector<StockRecord> getFirstNRows(int n) const;
    std::vector<StockRecord> filterByDateRange(const std::string& start, const std::string& end) const;
    std::vector<StockRecord> getFilteredSymbolRecords(const std::string& symbol, const std::string& start, const std::string& end) const;
    void sortByDate(bool ascending);
};
 
#endif
