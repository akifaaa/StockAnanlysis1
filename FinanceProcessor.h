/*






// FinanceProcessor.h
#ifndef FINANCEPROCESSOR_H
#define FINANCEPROCESSOR_H

#include "CSVReaderBase.h"
#include <string>

class FinanceProcessor {
public:
    FinanceProcessor();

    void calculateProfitLoss(const CSVReaderBase& reader);
    void detectAnomalies(const CSVReaderBase& reader);

private:
    void displayProfitLossTable(const std::vector<StockRecord>& filtered);
    void displayAnomalies(const std::vector<StockRecord>& filtered, double threshold);
};

#endif






#ifndef FINANCEPROCESSOR_H
#define FINANCEPROCESSOR_H

#include "CSVReaderBase.h"
#include "StockRecord.h"  
#include <string>
#include <vector> 

class FinanceProcessor {
public:
    FinanceProcessor(); 
    void calculateProfitLoss(const CSVReaderBase& reader);  
    void detectAnomalies(const CSVReaderBase& reader);  

private:
    void displayProfitLossTable(const std::vector<StockRecord>& filtered);  
    void displayAnomalies(const std::vector<StockRecord>& filtered, double threshold);  
};

#endif


