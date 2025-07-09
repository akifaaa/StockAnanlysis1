/*

#ifndef ANALYTICS_FUNCTIONS_H
#define ANALYTICS_FUNCTIONS_H

#include "CSVReader.h" // Provides StockRecord struct, indirectly includes DateUtils.h
#include <vector>
#include <string>

// Forward declaration of StockRecord is now unnecessary as CSVReader.h is included

void show52WeekHighLow(const std::vector<StockRecord>& data, const std::string& symbol, const std::string& startDateStr);
void showTopGainersLosers(const std::vector<StockRecord>& data, const std::string& startDateStr);
void countGainsLosses(const std::vector<StockRecord>& records);
void computeAverageVWAP(const std::vector<StockRecord>& records);
void computeCAGR(const std::vector<StockRecord>& records);

#endif
*/




//// AnalyticsFunctions.h
//#ifndef ANALYTICSFUNCTIONS_H
//#define ANALYTICSFUNCTIONS_H
//
//#include <vector>
//#include <string>
//#include "StockRecord.h"
//
//class AnalyticsFunctions {
//public:
//    void calculateProfitLoss(const std::vector<StockRecord>& records);
//    void detectAnomalies(const std::vector<StockRecord>& records, double threshold);
//    void show52WeekHighLow(const std::vector<StockRecord>& records, const std::string& symbol, const std::string& fromDate);
//    void showTopGainersLosers(const std::vector<StockRecord>& records, const std::string& onDate);
//    void countGainsLosses(const std::vector<StockRecord>& records);
//    void computeAverageVWAP(const std::vector<StockRecord>& records);
//    void computeCAGR(const std::vector<StockRecord>& records);
//};
//
//#endif // ANALYTICSFUNCTIONS_H
//
//






#ifndef ANALYTICS_FUNCTIONS_H
#define ANALYTICS_FUNCTIONS_H

#include <vector>
#include <string>
#include <iostream> 
#include <iomanip>  
#include <map>      


struct StockRecord;

class AnalyticsFunctions {
public:
    void calculateProfitLoss(const std::vector<StockRecord>& records) const;
    void detectAnomalies(const std::vector<StockRecord>& records, double threshold) const;
    void showTopGainersLosers(const std::vector<StockRecord>& data, const std::string& startDateStr) const;
    void countGainsLosses(const std::vector<StockRecord>& records) const;
    void computeAverageVWAP(const std::vector<StockRecord>& records) const;
    void computeCAGR(const std::vector<StockRecord>& records) const;
    void show52WeekHighLow(const std::vector<StockRecord>& records, const std::string& symbol, const std::string& startDateStr) const;
};

#endif 
