#include "../include/stock.h"

using namespace StockTradingSystem;
// Default constructor
Stock::Stock() = default;

// Constructor with price and name
Stock::Stock(double p, const std::string& n)
    : price_{p}, name_{n} {}

    // Set the price of a stock
void Stock::setPrice(double p) {
    price_ = p;
}

// Set name / symbol of a stock
void Stock::setName(const std::string& n) {
    name_ = n;
}

// Returns the price of a stock
double Stock::getPrice() const {
    return price_;
}

// Returns the name / symbol of a stock
std::string Stock::getName() const {
    return name_;
}