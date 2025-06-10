#include "../include/orderBook.h"
#include <iostream>

using namespace StockTradingSystem;

// Constructor initializes the matching strategy pointer to null
OrderBook::OrderBook() : strategy(nullptr) {}

// Adds new order to the book
void OrderBook::addOrder(std::shared_ptr<Order> order) {
    if (!order) {
        // If the order is null, print an error message
        // This is a safeguard against adding null orders
        std::cerr << "Error: Attempted to add a null order." << std::endl;
        return;
	}
	std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex to ensure thread safety
    book.push_back(order);
}

// Matches buy and sell orders using the current strategy
void OrderBook::matchOrders() {
    std::vector<std::shared_ptr<Order>> buyOrders, sellOrders;
    {
        std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex to ensure thread safety

        //Create vectors of shared pointers to orders
            // Seperate orders into buy and sell vectors
        for (const auto& order : book) {
            if (order->getOrderType() == BUY) {
                buyOrders.push_back(order);
            }
            else {
                sellOrders.push_back(order);
            }
            book.clear(); // Clear the book to avoid duplication
        }
    }

	// Match outside ock to avoid deadlock issues
    if (strategy) {
        strategy->matchOrders(buyOrders, sellOrders);
    } else {
		std::cerr << "Error: No matching strategy set for the order book." << std::endl;
    }


    //update the order book with remaining orders (under Lock)
	std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex to ensure thread safety
    book.insert(book.end(), buyOrders.begin(), buyOrders.end());
    book.insert(book.end(), sellOrders.begin(), sellOrders.end());
}

// Prints the current order book content in a readable format
void OrderBook::printOrderBook() const {
    std::cout << "Current Book content...\n";
    std::cout << "Trader ID\tPrice\tQuantity\tType\n\n";
	std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex to ensure thread safety
    for (const auto& order : book) {
        std::string orderTypeName = (order -> getOrderType() == BUY) ? "BUY" : "SELL";
        std::cout << order->getTraderID() << "\t\t"
                  << order->getPrice() << "\t"
                  << order->getQuantity() << "\t\t"
                  << orderTypeName << "\n";
    }
    std::cout << "\n";
}

// Sets the order matching strategy to be used during matching
void OrderBook::setStrategy(OrderMatchingStrategy* newStrategy) {
    strategy = newStrategy;
}