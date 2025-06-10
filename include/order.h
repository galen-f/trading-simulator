#ifndef STOCK_TRADING_SYSTEM_ORDER_H
#define STOCK_TRADING_SYSTEM_ORDER_H

#include <string>
#include <memory>
#include <vector>
#include <ctime>

namespace StockTradingSystem {
    enum OrderType {
        BUY,    // Buy order
        SELL    // Sell order
    };

    class Order {
    public:
        // Constructor to initialize with an ID, price, quantity
        Order(int, double, int);
        // Virtual destructor for safe polymorphism
        virtual ~Order();
        // Pure virtual method to get the order type as a string
        virtual std::string getOrderTypeString() const = 0;

        // Accessors
        int getTraderID() const;
        double getPrice() const;
        int getQuantity() const;
        std::time_t getTimestamp() const;
        OrderType getOrderType() const;

        // Mutators
        void reduceQuantity(int);
        void setOrderType(OrderType);

    private:
        int traderID_;          // Unique ID of the trader who placed the order
        double price_;          // Price at which the order is placed
        int quantity_;          // Quantity of stocks in the order
        std::time_t timestamp_; // Timestamp when the order was created
        OrderType orderType_;   // Type of the order (BUY or SELL)
    };

    // Represents a market order (excecute immediately at the best availible price)
    class MarketOrder : public Order {
    public:
        MarketOrder(int trader_id, double price, int quantity) : Order(trader_id, price, quantity) {}
        std::string getOrderTypeString() const override;
    };

    // Represents a limit order (excecute at a specific price or better)
    class LimitOrder : public Order {
    public:
        LimitOrder(int trader_id, double price, int quantity) : Order(trader_id, price, quantity) {}
        std::string getOrderTypeString() const override;
    };

    // Factory interface to create orders
    class OrderFactory {
    public:
        virtual std::unique_ptr<Order> createOrder(int, double, int) = 0;
        // Virtual destructor for safe polymorphism
        virtual ~OrderFactory();
    };

    // Factory for creating market order objects
    class MarketOrderFactory : public OrderFactory {
    public:
        std::unique_ptr<Order> createOrder(int, double, int) override;
    };

    // Factory for creating limit order objects
    class LimitOrderFactory : public OrderFactory {
    public:
        std::unique_ptr<Order> createOrder(int, double, int) override;
    };

    // Abstract strateg interface for matching buy/sell orders
    class OrderMatchingStrategy {
    public:
        // Pure virtual match buy and sell orders
        virtual void matchOrders(std::vector<std::shared_ptr<Order>>&, std::vector<std::shared_ptr<Order>>&) = 0;
        virtual ~OrderMatchingStrategy();
    };

    // Implements a price-time priority matching strategy
    class PriceTimeOrderMatchingStrategy : public OrderMatchingStrategy {
    public:
        void matchOrders(std::vector<std::shared_ptr<Order>>&, std::vector<std::shared_ptr<Order>>&) override;
    };
}// StockTradingSystem
#endif // STOCK_TRADING_SYSTEM_ORDER_H