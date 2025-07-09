#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include "StockRecord.h" // For StockRecord struct
#include "DateUtils.h"   // For Date struct and utilities
#include <vector>        // For std::vector
#include <string>        // For std::string
#include <map>           // For std::map (though not directly used for period grouping in current approach, good to include if thinking of other aggregations)
#include <fstream>       // For std::ofstream (file output)
#include <iomanip>       // For std::setprecision, etc.
#include <limits>        // For std::numeric_limits

// Struct to hold aggregated data for a single reporting period (Month, Quarter, Year)
struct ReportEntry {
    std::string periodLabel;    // e.g., "Jan 2023", "Q1 2023", "2023"
    std::string startDate;      // Actual start date of the data in this period
    std::string endDate;        // Actual end date of the data in this period
    double periodOpen;          // Opening price of the first record in the period
    double periodClose;         // Closing price of the last record in the period
    double periodHigh;          // Highest price within the period
    double periodLow;           // Lowest price within the period
    long totalVolume;           // Sum of volume within the period
    double netProfitLoss;       // periodClose - periodOpen

    // Default constructor - Initializing periodHigh and periodLow in the body for C++03 compatibility
    ReportEntry() : periodOpen(0.0), periodClose(0.0), totalVolume(0), netProfitLoss(0.0) {
        periodHigh = -std::numeric_limits<double>::max();
        periodLow = std::numeric_limits<double>::max();
    }
};

class ReportGenerator {
public:
    ReportGenerator();

    // Generates monthly, quarterly, or yearly reports based on the reportType
    // The input records are expected to be for a single symbol and sorted by date ascending.
    std::vector<std::vector<std::string> > generateReport( // Fixed >> for C++03
        const std::vector<StockRecord>& records,
        const std::string& reportType // "monthly", "quarterly", "yearly"
    ) const;

    // Exports the generated report data to a CSV file
    bool exportReportToCSV(
        const std::string& filename,
        const std::vector<std::vector<std::string> >& reportData // Fixed >> for C++03
    ) const;

private:
    // Helper to aggregate data into report entries for different periods
    std::vector<ReportEntry> aggregatePeriodData(
        const std::vector<StockRecord>& records,
        const std::string& reportType
    ) const;

    // Helper to get the period label (e.g., "Jan 2023", "Q1 2023")
    std::string getPeriodLabel(const Date& date, const std::string& reportType) const;

    // Helper to convert ReportEntry vector to a string vector suitable for CSV export
    std::vector<std::vector<std::string> > convertReportEntriesToExportFormat( // Fixed >> for C++03
        const std::vector<ReportEntry>& entries
    ) const;

    // Helper to print report headers to console
    void printReportHeader(const std::string& reportType) const;
    // Helper to print a single report entry to console
    void printReportEntry(const ReportEntry& entry) const;
};

#endif // REPORT_GENERATOR_H
