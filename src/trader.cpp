#include "../include/trader.h"
#include <iostream>

using namespace StockTradingSystem;

// Constructor for TraderException, sets error message
//TraderException::TraderException(const std::string& message)
//    : msg_(message) {}

    // Returns the exception message as a c style sting
const char* TraderException::what() const noexcept {
    return msg_.c_str();
}

// Initialize the static trader ID counter
int Trader::id_counter = 0;

// Default constructor with default name and null pointers
Trader::Trader()
    : name("Unknown Trader"),
    id{++id_counter},
    orderFactory(nullptr),
    orderBook(nullptr) 
    {}

// Constructor with trader name
Trader::Trader(const std::string& n)
    : name(n),
    id{++id_counter},
    orderFactory(nullptr),
    orderBook(nullptr) 
    {}

// Constructor with trader name, stocks, order factory, and order book
Trader::Trader(const std::string& n, const std::vector<Stock>& s, OrderFactory* of, OrderBook* ob)
    : name(n),
    id{++id_counter},
    stocks(s),
    orderFactory(of),
    orderBook(ob) 
    {}

// Attempts to buy a stock if a factory and book are availibile
void Trader::buy(const StockTradingSystem::Stock& stock, int quantity)
{
        try{
            if (orderFactory != nullptr && orderBook != nullptr) {
                std::shared_ptr<Order> ord = orderFactory -> createOrder(id, stock.getPrice(), quantity);
                orders.push_back(ord);
                if (ord != nullptr) {
                    orderBook->addOrder(ord);
                }
            }
        }
        catch (const TraderException& e) {
            std::cerr << "Trader Error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Unknown Error: " << e.what() << std::endl;
        }
}


// Attempts to sell a stock if a factory and book are availibile
void Trader::sell(const StockTradingSystem::Stock& stock, int quantity)
{
    try {
        if (orderFactory != nullptr && orderBook != nullptr) {
            std::shared_ptr<Order> ord = orderFactory->createOrder(id, stock.getPrice(), quantity);
            orders.push_back(ord);
            if (ord != nullptr) {
                orderBook->addOrder(ord);
            }
        }
    } catch (const TraderException& e) {
        std::cerr << "Trader Error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Unknown Error: " << e.what() << std::endl;
    }
}

// Basic trading strat: buy if below a threshold and sell if above
void Trader::trade(double buyThreshold, double sellThreshold, int buyQuantity, int sellQuantity)
{
    // Buy when stock is lower than threshole and sell when higher than threshold
    for (const auto& stock : stocks) {
        if (stock.getPrice() < buyThreshold) {
            buy(stock, buyQuantity);
        } else if (stock.getPrice() > sellThreshold) {
            sell(stock, sellQuantity);
        }
    }
}

// Returns the traders ID, unique
int Trader::getID() const {
    return id;
}

// Returns a list of all orders placed by trader
const std::vector<std::shared_ptr<Order>>& Trader::getOrders() const {
    return orders;
}

// Adds new stock to the traders portfolio
void Trader::addStock(const Stock& stock) {
    stocks.push_back(stock);
}

// Returns a copy of the trader's portfolio
std::vector<Stock> Trader::getStocks() const {
    return stocks;
}

// Destructs the trader, cleaning up resources
Trader::~Trader() {
    /*delete orderFactory;
    delete orderBook;*/
    // No need to delete stocks, as they are managed by the vector
}