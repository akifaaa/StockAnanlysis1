
#include "StockAnalyzer.h"
#include "DateUtils.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm> // For std::sort

StockAnalyzer::StockAnalyzer() {
    // Member objects (csvReader, analytics, reportGenerator, allRecords)
    // are automatically value-initialized here.
}

StockAnalyzer::~StockAnalyzer() {
    // No manual memory management needed for member objects.
}

bool StockAnalyzer::loadData(const std::string& filename) {
    if (csvReader.readCSV(filename)) {
        allRecords = csvReader.getRecords();
        return true;
    }
    return false;
}

void StockAnalyzer::displayFirstNRows(int n) const {
    std::vector<StockRecord> firstN = csvReader.getFirstNRows(n);
    printRecords(firstN);
}

void StockAnalyzer::filterBySymbolAndDate(const std::string& symbol, const std::string& startDate, const std::string& endDate) const {
    std::vector<StockRecord> filtered = csvReader.getFilteredSymbolRecords(symbol, startDate, endDate);
    printRecords(filtered);
}

void StockAnalyzer::filterByDate(const std::string& startDate, const std::string& endDate) const {
    std::vector<StockRecord> filtered = csvReader.filterByDateRange(startDate, endDate);
    printRecords(filtered);
}

void StockAnalyzer::sortByDateMenu() {
    std::cout << "Sort by Date:\n";
    std::cout << "1. Ascending\n";
    std::cout << "2. Descending\n";
    std::cout << "Enter choice: ";
    int sortChoice;
    while (!(std::cin >> sortChoice)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<StockRecord> recordsForDisplay = allRecords;

    if (sortChoice == 1) {
        std::sort(recordsForDisplay.begin(), recordsForDisplay.end(), DateUtils::compareStockRecordByDateAsc);
    } else if (sortChoice == 2) {
        std::sort(recordsForDisplay.begin(), recordsForDisplay.end(), DateUtils::compareStockRecordByDateDesc);
    } else {
        std::cout << "Invalid sort choice.\n";
        return;
    }
    printRecords(recordsForDisplay);
}

void StockAnalyzer::profitLossUI() {
    std::cout << "\n===== PROFIT/LOSS CALCULATION =====\n";
    std::string symbol, startDate, endDate;
    std::cout << "Enter Symbol (leave blank for all symbols): ";
    std::getline(std::cin, symbol);
    std::cout << "Enter Start Date (DD-MM-YYYY) (leave blank for all dates): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter End Date (DD-MM-YYYY) (leave blank for all dates): ";
    std::getline(std::cin, endDate);

    std::vector<StockRecord> filteredRecords = allRecords;

    if (!symbol.empty() && !startDate.empty() && !endDate.empty()) {
        filteredRecords = csvReader.getFilteredSymbolRecords(symbol, startDate, endDate);
    } else if (!startDate.empty() && !endDate.empty()) {
        filteredRecords = csvReader.filterByDateRange(startDate, endDate);
    } else if (!symbol.empty()) {
        std::vector<StockRecord> tempFiltered;
        for(std::vector<StockRecord>::const_iterator it = allRecords.begin(); it != allRecords.end(); ++it) {
            if (it->symbol == symbol) {
                tempFiltered.push_back(*it);
            }
        }
        filteredRecords = tempFiltered;
    }

    if (filteredRecords.empty()) {
        std::cout << "No records found for the specified criteria.\n";
    } else {
        analytics.calculateProfitLoss(filteredRecords);
    }
}


void StockAnalyzer::anomalyDetectionUI() {
    std::cout << "\n===== FILTER ABOVE THRESHOLD =====\n";
    std::string symbol, startDate, endDate;
    double threshold;

    std::cout << "Enter Threshold for Close Price Anomaly: ";
    while (!(std::cin >> threshold)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Symbol (leave blank for all symbols): ";
    std::getline(std::cin, symbol);
    std::cout << "Enter Start Date (DD-MM-YYYY) (leave blank for all dates): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter End Date (DD-MM-YYYY) (leave blank for all dates): ";
    std::getline(std::cin, endDate);

    std::vector<StockRecord> filteredRecords = allRecords;

    if (!symbol.empty() && !startDate.empty() && !endDate.empty()) {
        filteredRecords = csvReader.getFilteredSymbolRecords(symbol, startDate, endDate);
    } else if (!startDate.empty() && !endDate.empty()) {
        filteredRecords = csvReader.filterByDateRange(startDate, endDate);
    } else if (!symbol.empty()) {
        std::vector<StockRecord> tempFiltered;
        for(std::vector<StockRecord>::const_iterator it = allRecords.begin(); it != allRecords.end(); ++it) {
            if (it->symbol == symbol) {
                tempFiltered.push_back(*it);
            }
        }
        filteredRecords = tempFiltered;
    }

    if (filteredRecords.empty()) {
        std::cout << "No records found for the specified criteria.\n";
    } else {
        analytics.detectAnomalies(filteredRecords, threshold);
    }
}

void StockAnalyzer::fiftyTwoWeekHighLowUI() {
    std::string symbol, date;
    std::cout << "Enter Symbol: ";
    std::getline(std::cin, symbol);
    std::cout << "Enter Start Date (DD-MM-YYYY) for 52-week period: ";
    std::getline(std::cin, date);
    
    std::vector<StockRecord> filteredRecords;
    for (std::vector<StockRecord>::const_iterator it = allRecords.begin(); it != allRecords.end(); ++it) {
        if (it->symbol == symbol && Date::parse(it->date) >= Date::parse(date)) {
            filteredRecords.push_back(*it);
        }
    }
    analytics.show52WeekHighLow(filteredRecords, symbol, date);
}

void StockAnalyzer::topGainersLosersUI() {
    std::string startDate;
    std::cout << "Enter Start Date (DD-MM-YYYY) to find Top Gainers/Losers from that date: ";
    std::getline(std::cin, startDate);
    analytics.showTopGainersLosers(allRecords, startDate);
}

void StockAnalyzer::countPositiveNegativeDaysUI() {
    std::cout << "\n===== COUNT POSITIVE/NEGATIVE DAYS =====\n";
    std::string symbol, startDate, endDate;
    std::cout << "Enter Symbol (leave blank for all symbols): ";
    std::getline(std::cin, symbol);
    std::cout << "Enter Start Date (DD-MM-YYYY) (leave blank for all dates): ";
    std::getline(std::cin, startDate); // Corrected to endDate
    std::cout << "Enter End Date (DD-MM-YYYY) (leave blank for all dates): ";
    std::getline(std::cin, endDate);

    std::vector<StockRecord> filteredRecords = allRecords;

    if (!symbol.empty() && !startDate.empty() && !endDate.empty()) {
        filteredRecords = csvReader.getFilteredSymbolRecords(symbol, startDate, endDate);
    } else if (!startDate.empty() && !endDate.empty()) {
        filteredRecords = csvReader.filterByDateRange(startDate, endDate);
    } else if (!symbol.empty()) {
        std::vector<StockRecord> tempFiltered;
        for(std::vector<StockRecord>::const_iterator it = allRecords.begin(); it != allRecords.end(); ++it) {
            if (it->symbol == symbol) {
                tempFiltered.push_back(*it);
            }
        }
        filteredRecords = tempFiltered;
    }

    if (filteredRecords.empty()) {
        std::cout << "No records found for the specified criteria.\n";
    } else {
        analytics.countGainsLosses(filteredRecords);
    }
}

void StockAnalyzer::averageVWAPUI() {
    std::cout << "\n===== AVERAGE VWAP CALCULATION =====\n";
    std::string symbol, startDate, endDate;
    std::cout << "Enter Symbol (leave blank for all symbols): ";
    std::getline(std::cin, symbol);
    std::cout << "Enter Start Date (DD-MM-YYYY) (leave blank for all dates): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter End Date (DD-MM-YYYY) (leave blank for all dates): ";
    std::getline(std::cin, endDate);

    std::vector<StockRecord> filteredRecords = allRecords;

    if (!symbol.empty() && !startDate.empty() && !endDate.empty()) {
        filteredRecords = csvReader.getFilteredSymbolRecords(symbol, startDate, endDate);
    } else if (!startDate.empty() && !endDate.empty()) {
        filteredRecords = csvReader.filterByDateRange(startDate, endDate);
    } else if (!symbol.empty()) {
        std::vector<StockRecord> tempFiltered;
        for(std::vector<StockRecord>::const_iterator it = allRecords.begin(); it != allRecords.end(); ++it) {
            if (it->symbol == symbol) {
                tempFiltered.push_back(*it);
            }
        }
        filteredRecords = tempFiltered;
    }

    if (filteredRecords.empty()) {
        std::cout << "No records found for the specified criteria.\n";
    } else {
        analytics.computeAverageVWAP(filteredRecords);
    }
}

void StockAnalyzer::cagrUI() {
    std::cout << "\n===== CAGR CALCULATION =====\n";
    std::string symbol, startDate, endDate;
    std::cout << "Enter Symbol: ";
    std::getline(std::cin, symbol);
    std::cout << "Enter Start Date (DD-MM-YYYY): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter End Date (DD-MM-YYYY): ";
    std::getline(std::cin, endDate);

    std::vector<StockRecord> filteredRecords = csvReader.getFilteredSymbolRecords(symbol, startDate, endDate);

    if (filteredRecords.empty()) {
        std::cout << "No records found for the specified symbol and date range for CAGR calculation.\n";
    } else {
        std::sort(filteredRecords.begin(), filteredRecords.end(), DateUtils::compareStockRecordByDateAsc);
        analytics.computeCAGR(filteredRecords);
    }
}

// Implementation for reportGeneratorUI
void StockAnalyzer::reportGeneratorUI() {
    std::cout << "\n===== GENERATE FINANCIAL REPORTS =====\n";
    std::string symbol, startDate, endDate, reportTypeStr, outputFilename;
    int reportTypeChoice;

    std::cout << "Enter Symbol: ";
    std::getline(std::cin, symbol);
    std::cout << "Enter Start Date (DD-MM-YYYY): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter End Date (DD-MM-YYYY): ";
    std::getline(std::cin, endDate);

    std::cout << "\nSelect Report Type:\n";
    std::cout << "1. Monthly\n";
    std::cout << "2. Quarterly\n";
    std::cout << "3. Yearly\n";
    std::cout << "Enter choice: ";
    while (!(std::cin >> reportTypeChoice)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline

    switch (reportTypeChoice) {
        case 1: reportTypeStr = "monthly"; break;
        case 2: reportTypeStr = "quarterly"; break;
        case 3: reportTypeStr = "yearly"; break;
        default:
            std::cout << "Invalid report type choice. Aborting report generation.\n";
            return;
    }

    std::cout << "Enter output CSV filename (e.g., stock_report.csv): ";
    std::getline(std::cin, outputFilename);

    // Filter records for the specified symbol and date range
    std::vector<StockRecord> filteredRecords = csvReader.getFilteredSymbolRecords(symbol, startDate, endDate);

    if (filteredRecords.empty()) {
        std::cout << "No records found for the specified symbol and date range to generate a report.\n";
        return;
    }

    // Generate the report data
    // Fix: Add space between nested template closing brackets for C++03
    std::vector<std::vector<std::string> > reportData = reportGenerator.generateReport(filteredRecords, reportTypeStr);

    // Export the report data
    if (reportGenerator.exportReportToCSV(outputFilename, reportData)) {
        // Success message is handled by exportReportToCSV
    } else {
        std::cout << "Failed to export report.\n";
    }
}


void StockAnalyzer::printRecords(const std::vector<StockRecord>& records) const {
    if (records.empty()) {
        std::cout << "No records to display.\n";
        return;
    }
    std::cout << std::left
              << std::setw(12) << "Date"
              << std::setw(8) << "Symbol"
              << std::setw(8) << "Series"
              << std::setw(12) << "Prev Close"
              << std::setw(8) << "Open"
              << std::setw(8) << "High"
              << std::setw(8) << "Low"
              << std::setw(8) << "Last"
              << std::setw(8) << "Close"
              << std::setw(8) << "VWAP"
              << std::setw(10) << "Volume"
              << std::setw(12) << "Turnover"
              << std::endl;
    std::cout << std::string(100, '-') << std::endl;

    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        std::cout << std::left
                  << std::setw(12) << it->date
                  << std::setw(8) << it->symbol
                  << std::setw(8) << it->series
                  << std::setw(12) << std::fixed << std::setprecision(2) << it->prevClose
                  << std::setw(8) << std::fixed << std::setprecision(2) << it->open
                  << std::setw(8) << std::fixed << std::setprecision(2) << it->high
                  << std::setw(8) << std::fixed << std::setprecision(2) << it->low
                  << std::setw(8) << std::fixed << std::setprecision(2) << it->last
                  << std::setw(8) << std::fixed << std::setprecision(2) << it->close
                  << std::setw(8) << std::fixed << std::setprecision(2) << it->vwap
                  << std::setw(10) << it->volume
                  << std::setw(12) << std::fixed << std::setprecision(2) << it->turnover
                  << std::endl;
    }
}

