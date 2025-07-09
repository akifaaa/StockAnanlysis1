


#ifndef CONSOLE_USER_INTERFACE_H
#define CONSOLE_USER_INTERFACE_H

#include "StockAnalyzer.h"
#include <string>
#include <vector>

class ConsoleUserInterface {
private:
    StockAnalyzer* analyzer;

    void printMainMenu() const;
    void clearConsole() const;
    void handleChoice(int choice);

public:
    ConsoleUserInterface();
    ~ConsoleUserInterface();
    void run();
    void printBanner();
};

#endif // CONSOLE_USER_INTERFACE_H

