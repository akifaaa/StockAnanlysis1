#include "ReportGenerator.h"
#include "DateUtils.h" // For Date::parse and date operations
#include <iostream>    // For console output
#include <sstream>     // For std::ostringstream
#include <stdexcept>   // For std::runtime_error
#include <algorithm>   // For std::min, std::max
#include <cctype>      // For toupper

// Constructor
ReportGenerator::ReportGenerator() {
    // No specific initialization needed for this class
}

// Helper to get the period label (e.g., "Jan 2023", "Q1 2023", "2023")
std::string ReportGenerator::getPeriodLabel(const Date& date, const std::string& reportType) const {
    std::ostringstream oss;
    if (reportType == "monthly") {
        // Format: "MMM YYYY"
        const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        oss << months[date.month - 1] << " " << date.year;
    } else if (reportType == "quarterly") {
        int quarter = (date.month - 1) / 3 + 1;
        oss << "Q" << quarter << " " << date.year;
    } else if (reportType == "yearly") {
        oss << date.year;
    }
    return oss.str();
}

// Helper to aggregate data into report entries for different periods
std::vector<ReportEntry> ReportGenerator::aggregatePeriodData(
    const std::vector<StockRecord>& records,
    const std::string& reportType
) const {
    std::vector<ReportEntry> aggregatedReports;
    if (records.empty()) {
        return aggregatedReports;
    }

    ReportEntry currentPeriodEntry; // Automatically calls ReportEntry's default constructor
    Date currentPeriodStartDate; // Will be set on the first record of a period
    std::string lastPeriodLabel = "";

    // Iterate through sorted records
    for (std::vector<StockRecord>::const_iterator it = records.begin(); it != records.end(); ++it) {
        Date recordDate = Date::parse(it->date);
        std::string periodLabel = getPeriodLabel(recordDate, reportType);

        if (periodLabel != lastPeriodLabel && !lastPeriodLabel.empty()) {
            // New period started, save the previous one
            currentPeriodEntry.netProfitLoss = currentPeriodEntry.periodClose - currentPeriodEntry.periodOpen;
            // Set the start date for the period before pushing
            currentPeriodEntry.startDate = currentPeriodStartDate.toString();
            aggregatedReports.push_back(currentPeriodEntry);

            // Reset for the new period
            currentPeriodEntry = ReportEntry(); // Reset to default values
            currentPeriodEntry.periodHigh = it->high; // Initialize with current record's values
            currentPeriodEntry.periodLow = it->low;
            currentPeriodEntry.periodOpen = it->open; // First open of new period
            currentPeriodStartDate = recordDate; // Set the new period's start date
        } else if (lastPeriodLabel.empty()) {
            // First record in the entire dataset, initialize the first period entry
            currentPeriodEntry.periodHigh = it->high;
            currentPeriodEntry.periodLow = it->low;
            currentPeriodEntry.periodOpen = it->open; // First open of the first period
            currentPeriodStartDate = recordDate; // Set the start date for the very first period
        }

        // Update current period entry with current record's data
        currentPeriodEntry.periodLabel = periodLabel;
        currentPeriodEntry.endDate = it->date; // End date is always the current record's date for this period
        currentPeriodEntry.periodClose = it->close; // Close is always the current record's close for this period
        currentPeriodEntry.periodHigh = std::max(currentPeriodEntry.periodHigh, it->high);
        currentPeriodEntry.periodLow = std::min(currentPeriodEntry.periodLow, it->low);
        currentPeriodEntry.totalVolume += it->volume;
        
        lastPeriodLabel = periodLabel;
    }

    // Add the last period's entry after the loop finishes
    if (!records.empty()) {
        currentPeriodEntry.startDate = currentPeriodStartDate.toString(); // Ensure start date for the last period
        currentPeriodEntry.netProfitLoss = currentPeriodEntry.periodClose - currentPeriodEntry.periodOpen;
        aggregatedReports.push_back(currentPeriodEntry);
    }

    return aggregatedReports;
}


// Generates monthly, quarterly, or yearly reports
std::vector<std::vector<std::string> > ReportGenerator::generateReport(
    const std::vector<StockRecord>& records,
    const std::string& reportType
) const {
    std::vector<std::vector<std::string> > reportData;

    // Fix for C++03: Manually construct the vector for the header row
    std::vector<std::string> headerRow;
    headerRow.push_back("Period");
    headerRow.push_back("Start Date");
    headerRow.push_back("End Date");
    headerRow.push_back("Open Price");
    headerRow.push_back("Close Price");
    headerRow.push_back("High Price");
    headerRow.push_back("Low Price");
    headerRow.push_back("Total Volume");
    headerRow.push_back("Net Profit/Loss");
    reportData.push_back(headerRow); // Push the constructed header row

    if (records.empty()) {
        std::cout << "No records available to generate report.\n";
        return reportData;
    }
    
    // Ensure records are sorted by date ascending for correct aggregation
    // This is a defensive copy and sort. StockAnalyzer should ideally pass sorted records.
    std::vector<StockRecord> sortedRecords = records;
    std::sort(sortedRecords.begin(), sortedRecords.end(), DateUtils::compareStockRecordByDateAsc);


    std::vector<ReportEntry> aggregatedEntries = aggregatePeriodData(sortedRecords, reportType);

    // Convert aggregated entries to string format for export
    std::vector<std::vector<std::string> > formattedEntries = convertReportEntriesToExportFormat(aggregatedEntries);

    // Append formatted entries to reportData (after header)
    reportData.insert(reportData.end(), formattedEntries.begin(), formattedEntries.end());
    
    // Print to console for immediate feedback
    printReportHeader(reportType);
    for (std::vector<ReportEntry>::const_iterator it = aggregatedEntries.begin(); it != aggregatedEntries.end(); ++it) {
        printReportEntry(*it);
    }
    std::cout << std::string(115, '-') << std::endl; // Separator (adjusted width for new columns)

    return reportData;
}

// Helper to convert ReportEntry vector to a string vector suitable for CSV export
std::vector<std::vector<std::string> > ReportGenerator::convertReportEntriesToExportFormat(
    const std::vector<ReportEntry>& entries
) const {
    std::vector<std::vector<std::string> > formattedData;
    std::ostringstream oss;
    
    for (std::vector<ReportEntry>::const_iterator it = entries.begin(); it != entries.end(); ++it) {
        std::vector<std::string> row;
        row.push_back(it->periodLabel);
        row.push_back(it->startDate);
        row.push_back(it->endDate);

        oss.str(""); oss.clear(); oss << std::fixed << std::setprecision(2) << it->periodOpen; row.push_back(oss.str());
        oss.str(""); oss.clear(); oss << std::fixed << std::setprecision(2) << it->periodClose; row.push_back(oss.str());
        oss.str(""); oss.clear(); oss << std::fixed << std::setprecision(2) << it->periodHigh; row.push_back(oss.str());
        oss.str(""); oss.clear(); oss << std::fixed << std::setprecision(2) << it->periodLow; row.push_back(oss.str());
        
        oss.str(""); oss.clear(); oss << it->totalVolume; row.push_back(oss.str());
        
        oss.str(""); oss.clear(); oss << std::fixed << std::setprecision(2) << it->netProfitLoss; row.push_back(oss.str());
        
        formattedData.push_back(row);
    }
    return formattedData;
}

// Exports the generated report data to a CSV file
bool ReportGenerator::exportReportToCSV(
    const std::string& filename,
    const std::vector<std::vector<std::string> >& reportData 
) const {
    std::ofstream outFile(filename.c_str()); // .c_str() for C++03 compatibility

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return false;
    }

    for (std::vector<std::vector<std::string> >::const_iterator rowIt = reportData.begin(); rowIt != reportData.end(); ++rowIt) {
        for (std::vector<std::string>::const_iterator colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
            outFile << *colIt;
            if (colIt + 1 != rowIt->end()) { // If not the last column
                outFile << ",";
            }
        }
        outFile << "\n"; // Newline after each row
    }

    outFile.close();
    std::cout << "Report successfully exported to " << filename << std::endl;
    return true;
}

void ReportGenerator::printReportHeader(const std::string& reportType) const {
    // Capitalize first letter of report type for display
    std::string capitalizedReportType = reportType;
    if (!capitalizedReportType.empty()) {
        capitalizedReportType[0] = static_cast<char>(toupper(static_cast<unsigned char>(capitalizedReportType[0])));
    }
    std::cout << "\n===== " << capitalizedReportType << " Financial Report =====\n";
    std::cout << std::left
              << std::setw(12) << "Period"
              << std::setw(13) << "Start Date"
              << std::setw(13) << "End Date"
              << std::setw(12) << "Open Price"
              << std::setw(12) << "Close Price"
              << std::setw(12) << "High Price"
              << std::setw(12) << "Low Price"
              << std::setw(12) << "Total Volume"
              << std::setw(15) << "Net P/L"
              << std::endl;
    std::cout << std::string(115, '-') << std::endl; // Separator line
}

void ReportGenerator::printReportEntry(const ReportEntry& entry) const {
    std::cout << std::left
              << std::setw(12) << entry.periodLabel
              << std::setw(13) << entry.startDate
              << std::setw(13) << entry.endDate
              << std::setw(12) << std::fixed << std::setprecision(2) << entry.periodOpen
              << std::setw(12) << std::fixed << std::setprecision(2) << entry.periodClose
              << std::setw(12) << std::fixed << std::setprecision(2) << entry.periodHigh
              << std::setw(12) << std::fixed << std::setprecision(2) << entry.periodLow
              << std::setw(12) << entry.totalVolume
              << std::setw(15) << std::fixed << std::setprecision(2) << entry.netProfitLoss
              << std::endl;
}
