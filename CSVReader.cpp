

#include "CSVReader.h"
#include "DateUtils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> 

bool CSVReader::readCSV(const std::string& filename) {
    records.clear();
    std::ifstream file(filename.c_str());

    if (!file.is_open()) return false;
    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        StockRecord record;
        std::string token;

        std::getline(ss, record.date, ',');
        std::getline(ss, record.symbol, ',');
        std::getline(ss, record.series, ',');
        std::getline(ss, token, ','); record.prevClose = std::atof(token.c_str());
        std::getline(ss, token, ','); record.open = std::atof(token.c_str());
        std::getline(ss, token, ','); record.high = std::atof(token.c_str());
        std::getline(ss, token, ','); record.low = std::atof(token.c_str());
        std::getline(ss, token, ','); record.last = std::atof(token.c_str());
        std::getline(ss, token, ','); record.close = std::atof(token.c_str());
        std::getline(ss, token, ','); record.vwap = std::atof(token.c_str());
        std::getline(ss, token, ','); record.volume = std::atoi(token.c_str());
        std::getline(ss, token, ','); record.turnover = std::atof(token.c_str());
        records.push_back(record);
    }
    file.close();
    return true;
}

std::vector<StockRecord> CSVReader::getRecords() const {
    return records;
}

std::vector<StockRecord> CSVReader::getFirstNRows(int n) const {
    std::vector<StockRecord> result;
    for (int i = 0; i < n && i < (int)records.size(); ++i)
        result.push_back(records[i]);
    return result;
}

std::vector<StockRecord> CSVReader::filterByDateRange(const std::string& start, const std::string& end) const {
    std::vector<StockRecord> result;
    for (int i = 0; i < (int)records.size(); ++i) {
        Date d = Date::parse(records[i].date);
        if (d >= Date::parse(start) && d <= Date::parse(end))
            result.push_back(records[i]);
    }
    return result;
}

std::vector<StockRecord> CSVReader::getFilteredSymbolRecords(const std::string& symbol, const std::string& start, const std::string& end) const {
    std::vector<StockRecord> result;
    for (int i = 0; i < (int)records.size(); ++i) {
        if (records[i].symbol == symbol) {
            Date d = Date::parse(records[i].date);
            if (d >= Date::parse(start) && d <= Date::parse(end))
                result.push_back(records[i]);
        }
    }
    return result;
}

void CSVReader::sortByDate(bool ascending) {
    if (ascending) {
        std::sort(records.begin(), records.end(), DateUtils::compareStockRecordByDateAsc);
    } else {
        std::sort(records.begin(), records.end(), DateUtils::compareStockRecordByDateDesc);
    }
}
