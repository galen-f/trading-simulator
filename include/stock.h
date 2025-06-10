#ifndef STOCK_TRADING_SYSTEM_STOCK_H
#define STOCK_TRADING_SYSTEM_STOCK_H

#include <string>

namespace StockTradingSystem {
    // Represnts a stock with a name and price
    class Stock {
        public:
            // Default constructor
            Stock();
            // Constructor with a price and name
            Stock(double, const std::string&);

            // Sets the price of the stock
            void setPrice(double);
            // Sets the name of the stock
            void setName(const std::string&);

            // Gets the price of the stock
            double getPrice() const;

            // Gets the name of the stock
            std::string getName() const;

        private:
            double price_;      // Price of the stock
            std::string name_;  // Name (or symbol) of the stock
    };
} // StockTradingSystem
#endif // STOCK_TRADING_SYSTEM_STOCK_H