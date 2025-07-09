/*
#include "FinanceProcessor.h"
#include <iostream>
#include <iomanip>

void calculateProfitLoss(const std::vector<StockRecord>& records) {
    if (records.empty()) {
        std::cout << "\nNo records to calculate Profit/Loss.\n";
        return;
    }

    double total = 0.0;
    std::cout << "\nProfit/Loss Report:\n";
    std::cout << "Date         | Open     | Close    | P/L\n";
    std::cout << "-------------|----------|----------|----------\n";
    for (int i = 0; i < (int)records.size(); ++i) {
        double pl = records[i].close - records[i].open;
        total += pl;
        std::cout << std::setw(13) << records[i].date << "| "
                  << std::setw(9) << records[i].open << "| "
                  << std::setw(9) << records[i].close << "| "
                  << std::setw(9) << pl << std::endl;
    }
    std::cout << "-------------------------------------------\n";
    std::cout << "Total Profit/Loss: " << total << std::endl;
}

void detectAnomalies(const std::vector<StockRecord>& records, double threshold) {
    if (records.empty()) {
        std::cout << "\nNo records to check anomalies.\n";
        return;
    }

    std::cout << "\nAnomalies (Close > " << threshold << "):\n";
    std::cout << "Date         | Symbol | Close\n";
    std::cout << "-------------|--------|-------\n";
    bool found = false;
    for (int i = 0; i < (int)records.size(); ++i) {
        if (records[i].close > threshold) {
            std::cout << std::setw(13) << records[i].date << "| "
                      << std::setw(6) << records[i].symbol << "| "
                      << records[i].close << std::endl;
            found = true;
        }
    }
    if (!found)
        std::cout << "No anomalies found.\n";
}
*/



//
//
//// FinanceProcessor.cpp
//#include "FinanceProcessor.h"
//#include <iostream>
//#include <iomanip>
//
//FinanceProcessor::FinanceProcessor() {}
//
//void FinanceProcessor::calculateProfitLoss(const CSVReaderBase& reader) {
//    std::string symbol, startDate, endDate;
//    std::cout << "\n===== PROFIT/LOSS CALCULATION =====\n";
//    std::cout << "Enter stock symbol: ";
//    std::getline(std::cin, symbol);
//    std::cout << "Enter Start Date (DD-MM-YYYY): ";
//    std::getline(std::cin, startDate);
//    std::cout << "Enter End Date (DD-MM-YYYY): ";
//    std::getline(std::cin, endDate);
//
//    std::vector<StockRecord> filtered = reader.getFilteredSymbolRecords(symbol, startDate, endDate);
//    if (filtered.empty()) {
//        std::cout << "No records found for the given symbol and date range.\n";
//        return;
//    }
//
//    displayProfitLossTable(filtered);
//}
//
//void FinanceProcessor::displayProfitLossTable(const std::vector<StockRecord>& filtered) {
//    double totalProfit = 0.0;
//    std::cout << "\nDate         | Open    | Close   | Profit/Loss\n";
//    std::cout << "-------------|---------|---------|-------------\n";
//    for (int i = 0; i < (int)filtered.size(); ++i) {
//        double profit = filtered[i].close - filtered[i].open;
//        totalProfit += profit;
//        std::cout << std::setw(13) << filtered[i].date << "| "
//                  << std::setw(8) << filtered[i].open << "| "
//                  << std::setw(8) << filtered[i].close << "| "
//                  << std::setw(12) << profit << std::endl;
//    }
//    std::cout << "---------------------------------------------\n";
//    std::cout << "Total Profit/Loss: " << totalProfit << std::endl;
//}
//
//void FinanceProcessor::detectAnomalies(const CSVReaderBase& reader) {
//    std::string symbol, startDate, endDate;
//    std::cout << "\n===== ANOMALY DETECTION =====\n";
//    std::cout << "Enter stock symbol: ";
//    std::getline(std::cin, symbol);
//    std::cout << "Enter Start Date (DD-MM-YYYY): ";
//    std::getline(std::cin, startDate);
//    std::cout << "Enter End Date (DD-MM-YYYY): ";
//    std::getline(std::cin, endDate);
//
//    std::vector<StockRecord> filtered = reader.getFilteredSymbolRecords(symbol, startDate, endDate);
//    if (filtered.empty()) {
//        std::cout << "No records found for the given symbol and date range.\n";
//        return;
//    }
//
//    double threshold;
//    std::cout << "Enter close price threshold: ";
//    std::cin >> threshold;
//    std::cin.ignore();
//
//    displayAnomalies(filtered, threshold);
//}
//
//void FinanceProcessor::displayAnomalies(const std::vector<StockRecord>& filtered, double threshold) {
//    std::cout << "\nAnomalies Detected (Close Price > " << threshold << "):\n";
//    std::cout << "Date         | Symbol | Close\n";
//    std::cout << "-------------|--------|--------\n";
//    bool foundAnomaly = false;
//    for (int i = 0; i < (int)filtered.size(); ++i) {
//        if (filtered[i].close > threshold) {
//            std::cout << std::setw(13) << filtered[i].date << "| "
//                      << std::setw(7) << filtered[i].symbol << "| "
//                      << std::setw(7) << filtered[i].close << std::endl;
//            foundAnomaly = true;
//        }
//    }
//    if (!foundAnomaly) {
//        std::cout << "No anomalies found based on the given threshold within the filtered data.\n";
//    }
//}
//
//


/*
#include "FinanceProcessor.h"
#include "StockRecord.h"
#include <iostream>
#include <iomanip>
#include <vector>
 
FinanceProcessor::FinanceProcessor() {}
 
void FinanceProcessor::calculateProfitLoss(const CSVReaderBase& reader) {
    std::string symbol, startDate, endDate;
 
    std::cout << "\n===== PROFIT/LOSS CALCULATION =====\n";
    std::cout << "Enter stock symbol: ";
    std::getline(std::cin, symbol);
    std::cout << "Enter Start Date (DD-MM-YYYY): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter End Date (DD-MM-YYYY): ";
    std::getline(std::cin, endDate);
 
    std::vector<StockRecord> filtered = reader.getFilteredSymbolRecords(symbol, startDate, endDate);
    if (filtered.empty()) {
        std::cout << "No records found for the given symbol and date range.\n";
        return;
    }
    displayProfitLossTable(filtered);
}
 
void FinanceProcessor::displayProfitLossTable(const std::vector<StockRecord>& filtered) {
    double totalProfit = 0.0;
 
    std::cout << "\nDate         | Open    | Close   | Profit/Loss\n";
    std::cout << "-------------|---------|---------|-------------\n";
 
    for (int i = 0; i < (int)filtered.size(); ++i) {
        double profit = filtered[i].close - filtered[i].open;
        totalProfit += profit;
        std::cout << std::setw(13) << filtered[i].date << "| "
<< std::setw(8) << filtered[i].open << "| "
<< std::setw(8) << filtered[i].close << "| "
<< std::setw(12) << profit << std::endl;
    }
    std::cout << "---------------------------------------------\n";
    std::cout << "Total Profit/Loss: " << totalProfit << std::endl;
}
 
void FinanceProcessor::detectAnomalies(const CSVReaderBase& reader) {
    std::string symbol, startDate, endDate;
    std::cout << "\n===== ANOMALY DETECTION =====\n";
    std::cout << "Enter stock symbol: ";
    std::getline(std::cin, symbol);
    std::cout << "Enter Start Date (DD-MM-YYYY): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter End Date (DD-MM-YYYY): ";
    std::getline(std::cin, endDate);
 
    std::vector<StockRecord> filtered = reader.getFilteredSymbolRecords(symbol, startDate, endDate);
    if (filtered.empty()) {
        std::cout << "No records found for the given symbol and date range.\n";
        return;
    }
    double threshold;
    std::cout << "Enter close price threshold: ";
    std::cin >> threshold;
    std::cin.ignore();
    displayAnomalies(filtered, threshold);
}
 
void FinanceProcessor::displayAnomalies(const std::vector<StockRecord>& filtered, double threshold) {
    std::cout << "\nAnomalies Detected (Close Price > " << threshold << "):\n";
    std::cout << "Date         | Symbol | Close\n";
    std::cout << "-------------|--------|--------\n";
    bool foundAnomaly = false;
 
    for (int i = 0; i < (int)filtered.size(); ++i) {
        if (filtered[i].close > threshold) {
            std::cout << std::setw(13) << filtered[i].date << "| "
<< std::setw(7) << filtered[i].symbol << "| "
<< std::setw(7) << filtered[i].close << std::endl;
            foundAnomaly = true;
        }
    }
    if (!foundAnomaly) {
        std::cout << "No anomalies found based on the given threshold within the filtered data.\n";
    }
}
*/
