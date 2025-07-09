/*


#include "AnalyticsFunctions.h"
#include "DateUtils.h"
#include "StockRecord.h" // Ensure StockRecord is included if not already
#include <iostream>
#include <iomanip>
#include <cmath> // for pow
#include <vector> // Ensure vector is included

// Dummy implementations for ConsoleUIHelpers functions.
// These need to be properly defined in your project or removed if not used.
// If you have a separate ConsoleUIHelpers.h/cpp, ensure they are linked.
void printStockHeader(const std::vector<int>& columnWidths) {
    std::cout << "Date        | Symbol | Open   | High   | Low    | Close  | Volume\n";
    std::cout << "------------|--------|--------|--------|--------|--------|--------\n";
}

void printStockRow(const StockRecord& record, const std::vector<int>& columnWidths) {
    std::cout << std::setw(12) << record.date << "|"
              << std::setw(8) << record.symbol << "|"
              << std::setw(8) << std::fixed << std::setprecision(2) << record.open << "|"
              << std::setw(8) << std::fixed << std::setprecision(2) << record.high << "|"
              << std::setw(8) << std::fixed << std::setprecision(2) << record.low << "|"
              << std::setw(8) << std::fixed << std::setprecision(2) << record.close << "|"
              << std::setw(8) << record.volume << "\n";
}

// Corrected for C++03 compatibility: No initializer list for std::vector
std::vector<int> calculateStockColumnWidths(const std::vector<StockRecord>& records) {
    // This is a placeholder. In a real scenario, this function would
    // dynamically calculate column widths based on the content.
    std::vector<int> widths;
    widths.push_back(12);
    widths.push_back(8);
    widths.push_back(8);
    widths.push_back(8);
    widths.push_back(8);
    widths.push_back(8);
    widths.push_back(8);
    return widths;
}


// Constructor for AnalyticsFunctions (if needed, otherwise remove)
// AnalyticsFunctions::AnalyticsFunctions() {} // If this causes a duplicate definition, remove it here.

void AnalyticsFunctions::calculateProfitLoss(const std::vector<StockRecord>& records) const {
    if (records.empty()) {
        std::cout << "No data available for Profit/Loss calculation.\n";
        return;
    }
    double totalProfit = 0.0;
    std::cout << "\nDate           | Open    | Close   | Profit/Loss\n";
    std::cout << "-------------|---------|---------|-------------\n";
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        double profit = it->close - it->open;
        totalProfit += profit;
        std::cout << std::setw(13) << it->date << "| "
                  << std::setw(8) << it->open << "| "
                  << std::setw(8) << it->close << "| "
                  << std::setw(12) << profit << std::endl;
    }
    std::cout << "---------------------------------------------\n";
    std::cout << "Total Profit/Loss: " << totalProfit << "\n";
}

void AnalyticsFunctions::detectAnomalies(const std::vector<StockRecord>& records, double threshold) const {
    if (records.empty()) {
        std::cout << "No data available for anomaly detection.\n";
        return;
    }
    bool foundAnomaly = false;
    std::cout << "\nAnomalies Detected (Close Price > " << threshold << "):\n";
    std::cout << "Date           | Symbol | Close\n";
    std::cout << "-------------|--------|--------\n";
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        if (it->close > threshold) {
            std::cout << std::setw(13) << it->date << "| "
                      << std::setw(7) << it->symbol << "| "
                      << std::setw(7) << it->close << "\n";
            foundAnomaly = true;
        }
    }
    if (!foundAnomaly) {
        std::cout << "No anomalies found based on the given threshold.\n";
    }
}

void AnalyticsFunctions::show52WeekHighLow(const std::vector<StockRecord>& records, const std::string& symbol, const std::string& startDateStr) const {
    if (records.empty()) {
        std::cout << "No data available.\n";
        return;
    }
    Date startDate = Date::parse(startDateStr);
    double highest = -1e9, lowest = 1e9;
    bool found = false;
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        if (it->symbol == symbol && Date::parse(it->date) >= startDate) {
            found = true;
            if (it->high > highest) highest = it->high;
            if (it->low < lowest) lowest = it->low;
        }
    }
    if (!found) {
        std::cout << "No records found for the symbol " << symbol << " after " << startDateStr << "\n";
    } else {
        std::cout << "52-Week High: " << highest << ", 52-Week Low: " << lowest << "\n";
    }
}

void AnalyticsFunctions::showTopGainersLosers(const std::vector<StockRecord>& records, const std::string& dateStr) const {
    double maxGain = -1e9, maxLoss = 1e9;
    StockRecord topGainer, topLoser;
    bool found = false;
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        if (it->date == dateStr) {
            found = true;
            double change = it->close - it->open;
            if (change > maxGain) {
                maxGain = change;
                topGainer = *it;
            }
            if (change < maxLoss) {
                maxLoss = change;
                topLoser = *it;
            }
        }
    }
    if (!found) {
        std::cout << "No data found for the date " << dateStr << "\n";
        return;
    }
    std::cout << "\nTop Gainer:\n";
    // Pass a temporary vector containing just the topGainer for width calculation
    std::vector<StockRecord> gainer_vec;
    gainer_vec.push_back(topGainer);
    printStockHeader(calculateStockColumnWidths(gainer_vec));
    printStockRow(topGainer, calculateStockColumnWidths(gainer_vec));

    std::cout << "\nTop Loser:\n";
    // Pass a temporary vector containing just the topLoser for width calculation
    std::vector<StockRecord> loser_vec;
    loser_vec.push_back(topLoser);
    printStockHeader(calculateStockColumnWidths(loser_vec));
    printStockRow(topLoser, calculateStockColumnWidths(loser_vec));
}

void AnalyticsFunctions::countGainsLosses(const std::vector<StockRecord>& records) const {
    int positive = 0, negative = 0;
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        if (it->close > it->open) ++positive;
        else if (it->close < it->open) ++negative;
    }
    std::cout << "Positive Days (Close > Open): " << positive << "\n";
    std::cout << "Negative Days (Close < Open): " << negative << "\n";
}

void AnalyticsFunctions::computeAverageVWAP(const std::vector<StockRecord>& records) const {
    if (records.empty()) {
        std::cout << "No data available to compute average VWAP.\n";
        return;
    }
    double totalVWAP = 0;
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        totalVWAP += it->vwap;
    }
    std::cout << "Average VWAP: " << totalVWAP / records.size() << "\n";
}

void AnalyticsFunctions::computeCAGR(const std::vector<StockRecord>& records) const {
    if (records.empty()) {
        std::cout << "Insufficient data for CAGR calculation.\n";
        return;
    }
    double beginning = records.front().close;
    double ending = records.back().close;
    Date start = Date::parse(records.front().date);
    Date end = Date::parse(records.back().date);

    int years = DateUtils::yearsBetween(start, end);

    if (years <= 0 || beginning <= 0) {
        std::cout << "Invalid data to compute CAGR (years <= 0 or beginning close price <= 0).\n"; // More descriptive error
        return;
    }
    double cagr = std::pow((ending / beginning), 1.0 / years) - 1.0;
    std::cout << "CAGR over " << years << " years: " << cagr * 100 << "%\n";
}

*/

#include "AnalyticsFunctions.h"
#include "DateUtils.h"
#include "StockRecord.h"
#include <iostream>
#include <iomanip>
#include <cmath> 
#include <vector>
#include <algorithm> 
#include <map> 
#include <limits> 
#include <stdexcept>


void AnalyticsFunctions::calculateProfitLoss(const std::vector<StockRecord>& records) const {
    if (records.empty()) {
        std::cout << "No data available for Profit/Loss calculation.\n";
        return;
    }
    double totalProfit = 0.0;
    std::cout << "\nDate           | Open    | Close   | Profit/Loss\n";
    std::cout << "-------------|---------|---------|-------------\n";
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        double profit = it->close - it->open;
        totalProfit += profit;
        std::cout << std::setw(13) << it->date << "| "
                  << std::setw(8) << it->open << "| "
                  << std::setw(8) << it->close << "| "
                  << std::setw(12) << profit << std::endl;
    }
    std::cout << "---------------------------------------------\n";
    std::cout << "Total Profit/Loss: " << totalProfit << "\n";
}

void AnalyticsFunctions::detectAnomalies(const std::vector<StockRecord>& records, double threshold) const {
    if (records.empty()) {
        std::cout << "No data available for anomaly detection.\n";
        return;
    }
    bool foundAnomaly = false;
    std::cout << "\nAnomalies Detected (Close Price > " << threshold << "):\n";
    std::cout << "Date           | Symbol | Close\n";
    std::cout << "-------------|--------|--------\n";
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        if (it->close > threshold) {
            std::cout << std::setw(13) << it->date << "| "
                      << std::setw(7) << it->symbol << "| "
                      << std::setw(7) << it->close << "\n";
            foundAnomaly = true;
        }
    }
    if (!foundAnomaly) {
        std::cout << "No anomalies found based on the given threshold.\n";
    }
}


void AnalyticsFunctions::showTopGainersLosers(const std::vector<StockRecord>& data, const std::string& startDateStr) const {
    std::map<std::string, double> profitMap;

    try {
        Date startDate(startDateStr); 

        for (int i = 0; i < (int)data.size(); ++i) {
            Date recordDate(data[i].date); 
            if (recordDate >= startDate) {
                double diff = data[i].close - data[i].open;
                profitMap[data[i].symbol] += diff;
            }
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error parsing date in Top Gainers/Losers: " << e.what() << std::endl;
        return;
    }

    if (profitMap.empty()) {
        std::cout << "\nNo data found to determine top gainers/losers for the given date range.\n";
        return;
    }

    std::string gainer = "", loser = "";
    double maxGain = -1e9, maxLoss = 1e9; 

    std::map<std::string, double>::iterator it;
    for (it = profitMap.begin(); it != profitMap.end(); ++it) {
        if (it->second > maxGain) {
            maxGain = it->second;
            gainer = it->first;
        }
        if (it->second < maxLoss) {
            maxLoss = it->second;
            loser = it->first;
        }
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nTop Gainer: " << gainer << " | Net Gain: " << maxGain << "\n";
    std::cout << "Top Loser : " << loser << " | Net Loss: " << maxLoss << "\n";
    std::cout << std::setprecision(6); 
}



void AnalyticsFunctions::countGainsLosses(const std::vector<StockRecord>& records) const {
    if (records.empty()) {
        std::cout << "\nNo records to count gains/losses.\n";
        return;
    }
    int gain = 0, loss = 0;
    for (int i = 0; i < (int)records.size(); ++i) {
        if (records[i].close > records[i].open)
            ++gain;
        else if (records[i].close < records[i].open)
            ++loss;
    }

    std::cout << "\nPositive Days: " << gain << "\nNegative Days: " << loss << "\n";
}


void AnalyticsFunctions::computeAverageVWAP(const std::vector<StockRecord>& records) const {
    if (records.empty()) {
        std::cout << "No records to compute VWAP.\n";
        return;
    }

    double sum = 0.0; 
    for (int i = 0; i < (int)records.size(); ++i) {
        sum += records[i].vwap;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAverage VWAP for selected range: " << sum / records.size() << "\n";
    std::cout << std::setprecision(6); 
}


void AnalyticsFunctions::computeCAGR(const std::vector<StockRecord>& records) const {
    if (records.size() < 2) {
        std::cout << "Need at least two records to compute CAGR.\n";
        return;
    }

    
    double startValue = records.front().close; 
    double endValue = records.back().close;   

    try {
        Date startDate(records.front().date);
        Date endDate(records.back().date);

        int totalDays = endDate - startDate; 

        if (totalDays <= 0) { // If start and end dates are the same or inverted
            std::cout << "Invalid date range for CAGR calculation (start date must be before end date).\n";
            return;
        }

        double years = static_cast<double>(totalDays) / 365.25; // More accurate average days per year including leap years

        if (startValue <= 0) { // Initial investment cannot be zero or negative
            std::cout << "Invalid starting close price for CAGR calculation (must be positive).\n";
            return;
        }

        // CAGR formula: ((Ending Value / Beginning Value)^(1 / Number of Years)) - 1
        double cagr = pow(endValue / startValue, 1.0 / years) - 1.0;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\nCAGR over approximately " << years << " years: " << cagr * 100 << "%\n";
        std::cout << std::setprecision(6); 
    } catch (const std::runtime_error& e) {
        std::cerr << "Error during CAGR calculation (date parsing or invalid data): " << e.what() << std::endl;
    }
}


void AnalyticsFunctions::show52WeekHighLow(const std::vector<StockRecord>& records, const std::string& symbol, const std::string& startDateStr) const {
    if (records.empty()) {
        std::cout << "\nNo records found for " << symbol << " from " << startDateStr << " to calculate 52-week high/low.\n";
        return;
    }

    double highestHigh = -std::numeric_limits<double>::max(); // Initialize with smallest possible double
    double lowestLow = std::numeric_limits<double>::max();    // Initialize with largest possible double
    std::string highDate = "", lowDate = "";

    
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        if (it->high > highestHigh) {
            highestHigh = it->high;
            highDate = it->date;
        }
        if (it->low < lowestLow) {
            lowestLow = it->low;
            lowDate = it->date;
        }
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n52-Week High for " << symbol << " from " << startDateStr << " onwards: " << highestHigh << " (on " << highDate << ")\n";
    std::cout << "52-Week Low for " << symbol << " from " << startDateStr << " onwards: " << lowestLow << " (on " << lowDate << ")\n";
    std::cout << std::setprecision(6); 
}
