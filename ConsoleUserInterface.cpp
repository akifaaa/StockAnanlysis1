
#include "ConsoleUserInterface.h"
#include <iostream>
#include <limits> // For std::numeric_limits

ConsoleUserInterface::ConsoleUserInterface()
    : analyzer(new StockAnalyzer()) {
}

ConsoleUserInterface::~ConsoleUserInterface() {
    delete analyzer;
}

void ConsoleUserInterface::run() {
    std::string filename;
    clearConsole();
    printBanner();

    std::cout << "\n\nEnter CSV filename (e.g., combined.csv): ";
    std::getline(std::cin, filename);

    if (!analyzer->loadData(filename)) {
        std::cout << "Failed to load data. Exiting.\n";
        return;
    }

    int choice;
    do {
        clearConsole();
        printMainMenu();
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        handleChoice(choice);
    } while (choice != 13); 
}

void ConsoleUserInterface::handleChoice(int choice) {
    int n; // Kept for displayFirstNRows

    switch (choice) {
        case 1: { 
            std::cout << "Enter number of rows to display: ";
            std::cin >> n;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline
            analyzer->displayFirstNRows(n);
            break;
        }
        case 2: { 
            std::string symbol, startDate, endDate; // Declare locally within the case's scope
            std::cout << "Enter Symbol: ";
            std::getline(std::cin, symbol);
            std::cout << "Enter Start Date (DD-MM-YYYY): ";
            std::getline(std::cin, startDate);
            std::cout << "Enter End Date (DD-MM-YYYY): ";
            std::getline(std::cin, endDate);
            analyzer->filterBySymbolAndDate(symbol, startDate, endDate);
            break;
        }
        case 3: { 
            std::string startDate, endDate; // Declare locally within the case's scope
            std::cout << "Enter Start Date (DD-MM-YYYY): ";
            std::getline(std::cin, startDate);
            std::cout << "Enter End Date (DD-MM-YYYY): ";
            std::getline(std::cin, endDate);
            analyzer->filterByDate(startDate, endDate);
            break;
        }
        case 4:
            analyzer->sortByDateMenu();
            break;
        case 5:
            analyzer->profitLossUI();
            break;
        case 6:
            analyzer->anomalyDetectionUI();
            break;
        case 7:
            analyzer->fiftyTwoWeekHighLowUI();
            break;
        case 8:
            analyzer->topGainersLosersUI();
            break;
        case 9:
            analyzer->countPositiveNegativeDaysUI();
            break;
        case 10:
            analyzer->averageVWAPUI();
            break;
        case 11:
            analyzer->cagrUI();
            break;
        case 12: 
            analyzer->reportGeneratorUI();
            break;
        case 13: // 13 for Exit
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
    }
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void ConsoleUserInterface::clearConsole() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleUserInterface::printBanner() {
    std::cout << "====================================================\n";
    std::cout << "              STOCK DATA ANALYSIS SYSTEM\n";
    std::cout << "====================================================\n";
}

void ConsoleUserInterface::printMainMenu() const {
    std::cout << "\n============= MENU =============\n";
    std::cout << "1.    Display First N Rows\n";
    std::cout << "2.    Filter by Symbol & Date\n";
    std::cout << "3.    Filter by Date Range\n";
    std::cout << "4.    Sort by Date\n";
    std::cout << "5.    Profit/Loss Calculation\n";
    std::cout << "6.    Filter Above Threshold\n";
    std::cout << "7.    52 Week High/Low\n";
    std::cout << "8.    Top Gainer/Loser\n";
    std::cout << "9.    Count Positive/Negative Days\n";
    std::cout << "10.   Average VWAP\n";
    std::cout << "11.   CAGR Calculation\n";
    std::cout << "12.   Generate Financial Reports\n"; 
    std::cout << "13.   Exit\n"; 
    std::cout << "Enter your choice: ";
}
