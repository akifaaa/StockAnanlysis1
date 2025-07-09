#include "StockRecord.h"

// Default constructor implementation
StockRecord::StockRecord() :
    prevClose(0.0), open(0.0), high(0.0), low(0.0),
    last(0.0), close(0.0), vwap(0.0), volume(0), turnover(0.0) {}

// Parametrized constructor implementation
StockRecord::StockRecord(
    const std::string& date,
    const std::string& symbol,
    const std::string& series,
    double prevClose,
    double open,
    double high,
    double low,
    double last,
    double close,
    double vwap,
    long volume,
    double turnover
) : date(date), symbol(symbol), series(series),
    prevClose(prevClose), open(open), high(high), low(low),
    last(last), close(close), vwap(vwap), volume(volume), turnover(turnover) {}
