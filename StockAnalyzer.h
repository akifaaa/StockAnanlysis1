#ifndef STOCK_ANALYZER_H
#define STOCK_ANALYZER_H

#include <string>
#include <vector>
#include "CSVReader.h"
#include "AnalyticsFunctions.h"
#include "ReportGenerator.h" 
#include "StockRecord.h"

class StockAnalyzer {
private:
    CSVReader csvReader;
    AnalyticsFunctions analytics;
    ReportGenerator reportGenerator; 
    std::vector<StockRecord> allRecords;

public:
    StockAnalyzer();
    ~StockAnalyzer();

    bool loadData(const std::string& filename);
    void displayFirstNRows(int n) const;
    void filterBySymbolAndDate(const std::string& symbol, const std::string& startDate, const std::string& endDate) const;
    void filterByDate(const std::string& startDate, const std::string& endDate) const;
    void sortByDateMenu();
    void profitLossUI();
    void anomalyDetectionUI();
    void fiftyTwoWeekHighLowUI();
    void topGainersLosersUI();
    void countPositiveNegativeDaysUI();
    void averageVWAPUI();
    void cagrUI();
    void reportGeneratorUI(); // NEW: Declare the UI method for report generation

private:
    // Helper to print stock records
    void printRecords(const std::vector<StockRecord>& records) const;
};

#endif // STOCK_ANALYZER_H
