#ifndef STOCK_TRADING_SYSTEM_ORDERBOOK_H
#define STOCK_TRADING_SYSTEM_ORDERBOOK_H

#include "order.h"

#include <vector>
#include <memory>
#include <mutex>

namespace StockTradingSystem {

    // Manages all outstanding orders and handles matchoiing logic
    class OrderBook {
        public:
            // Contructor for empty order book
            OrderBook();

            // Add new order to the order book
            void addOrder(std::shared_ptr<Order>);

            // Match buy and sell orders using the current strategy
            void matchOrders();

            // Print all current orders (debugging and display)
            void printOrderBook() const;

            // Set the order matching strat (e.g., price-time priority)
            void setStrategy(OrderMatchingStrategy*);
        
        private:
            std::vector<std::shared_ptr<Order>> book;       // List of orders in the order book
			mutable std::mutex mutex_;                   // Mutex for thread-safe access
            OrderMatchingStrategy* strategy;                // Strategy for matching orders
        };
} // StockTradingSystem
#endif // STOCK_TRADING_SYSTEM_ORDERBOOK_H