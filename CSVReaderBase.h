
#ifndef CSVREADERBASE_H
#define CSVREADERBASE_H

#include <string>
#include <vector>
#include "StockRecord.h"  

class CSVReaderBase {
public:
    virtual bool readCSV(const std::string& filename) = 0; 
    virtual std::vector<StockRecord> getRecords() const = 0;  
    virtual std::vector<StockRecord> getFirstNRows(int n) const = 0; 
    virtual std::vector<StockRecord> filterByDateRange(const std::string& start, const std::string& end) const = 0; 
    virtual std::vector<StockRecord> getFilteredSymbolRecords(const std::string& symbol, const std::string& start, const std::string& end) const = 0; 
    virtual void sortByDate(bool ascending) = 0; 
    virtual ~CSVReaderBase() {} 
};

#endif
