#ifndef STOCK_TRADING_SYSTEM_TRADER_H
#define STOCK_TRADING_SYSTEM_TRADER_H

#include <string>
#include <memory>
#include <vector>
#include "stock.h"
#include "order.h"
#include "orderBook.h"

namespace StockTradingSystem {

    // Custom exception class for trader-related errors
    class TraderException : public std::exception {
    public:
        explicit TraderException(const std::string& message) : msg_(message) {}

        // Override the what() method to return the error message
        virtual const char* what() const noexcept override;
    private:
        std::string msg_; // Error message
    };

    class Trader {
        public:
            // default constructor
            Trader();

            //Constructor with trader name
            Trader(const std::string&);

            // Constructor with trader name, stocks, order factory, and order book
            Trader(const std::string&, const std::vector<Stock>&, OrderFactory*, OrderBook*);
            
            // Create a buy order for a given stock and quantity
            void buy(const Stock&, int);

            // Create a sell order for a given stock and quantity
            void sell(const Stock&, int);

            // Perform custom trade logic
            void trade(double, double, int, int);

            //Unique ID of trader
            int getID() const;

            // Accessor for the trader's order list
            const std::vector<std::shared_ptr<Order>>& getOrders() const;
            
            // Add a new stock to the trader's portfolio
            void addStock(const Stock&);

            // Return a copy of the trader's holdings
            std::vector<Stock> getStocks() const;

            // Destructor
            ~Trader();
        
        private:
            static int id_counter;      // Static counter to assign unique IDs
            int id;                     // Unique ID for the trader    
            std::string name;           // Name of the trader
            std::vector<Stock> stocks;  // Portfolio of stocks owned
            
            OrderFactory* orderFactory;                 // Create an order
            OrderBook* orderBook;                       // Manage orders

            std::vector<std::shared_ptr<Order>> orders;   // ALl orders placed by trader
    };
} //StockTradingSystem

#endif //STOCK_TRADING_SYSTEM_TRADER_H