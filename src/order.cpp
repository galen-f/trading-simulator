#include "../include/order.h"

#include <algorithm>
#include <stdexcept>

using namespace StockTradingSystem;

// COnstructor for order
Order:: Order(int id, double p, int q)
    : traderID_{id}, price_{p}, quantity_{q}
    {
        timestamp_ = std::time(nullptr); // Set the current time as the timestamp
    }

    // Virtual destructor for safe polymorphism
    Order::~Order(){}

    // Return the ID of the trader who placed this order
    int Order::getTraderID() const
    {
        return traderID_;
    }

    // Returns the price associated with this order
    double Order::getPrice() const
    {
        return price_;
    }

    // Returns the current quantity for this order
    int Order::getQuantity() const
    {
        return quantity_;
    }

    // Returns the timestamp of when this order was created
    std::time_t Order::getTimestamp() const
    {
        return timestamp_;
    }

    // Decreases the quantity of this order by a specific amount
    void Order::reduceQuantity(int amount)
    {
        if (amount < 0 || amount > quantity_) {
            throw std::invalid_argument("Invalid quantity reduction");
        }
        quantity_ -= amount;
    }

    // Returns the type of this order (BUY or SELL)
    OrderType Order::getOrderType() const
    {
        return orderType_;
    }

    // Sets the type of this order (BUY or SELL)
    void Order::setOrderType(OrderType type)
    {
        orderType_ = type;
    }

    // Returns the label for a market order
    std::string MarketOrder::getOrderTypeString() const
    {
        return "Market Order";
    }

    // Returns the label for a limit order
    std::string LimitOrder::getOrderTypeString() const
    {
        return "Limit Order";
    }

    // Destructor for orderfactory
    OrderFactory::~OrderFactory(){}

    // Creates new market order object
    std::unique_ptr<Order> MarketOrderFactory::createOrder(int traderID, double price, int quantity)
    {
        return std::make_unique<MarketOrder>(traderID, price, quantity);
    }

    // Creates new limit order object
    std::unique_ptr<Order> LimitOrderFactory::createOrder(int traderID, double price, int quantity)
    {
        return std::make_unique<LimitOrder>(traderID, price, quantity);
    }

    // Destructor for order matching strategy
    OrderMatchingStrategy::~OrderMatchingStrategy(){}

    // Implements the Price-Time Order Matching Strategy
    void PriceTimeOrderMatchingStrategy::matchOrders(std::vector<std::shared_ptr<Order>>& buyOrders, std::vector<std::shared_ptr<Order>>& sellOrders)
    {
        std::vector<std::shared_ptr<Order>> matchedOrders;

        // Try to match each sell order with any compatible buy order
        for (auto sellOrder = sellOrders.begin(); sellOrder != sellOrders.end(); ++sellOrder) {
            for (auto it = buyOrders.begin(); it != buyOrders.end();) {
                if ((*sellOrder) -> getPrice() <= (*it) -> getPrice()) {
                    // A match is found, record and remove the buy order
                    matchedOrders.push_back(*it);
                    it = buyOrders.erase(it);
                } else {
                    ++it;
                }
            }
        }

    // Add unmatched orders mack intoo the buy list.
    buyOrders.insert(buyOrders.end(), matchedOrders.begin(), matchedOrders.end());
    
}