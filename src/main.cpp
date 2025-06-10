#include "include/orderBook.h"
#include "include/trader.h"

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace StockTradingSystem;

// FUnction to simulate placing buy/sell orders
//define a trader function to simulate traders placing orders
void traderFunction(Trader& trader, OrderBook& orderBook) {
    // create two sample stocks and add them to the traders portfolio
    Stock appleStock(145, "APPL");
    Stock googleStock(200, "GOOGL");
    trader.addStock(appleStock);
    trader.addStock(googleStock);
    int quantity = 25;

    // Place buy and sell orders
    std::shared_ptr<Order> buyOrder = std::make_shared<MarketOrder>(trader.getID(), googleStock.getPrice(), quantity);
    buyOrder->setOrderType(OrderType::BUY);
    std::shared_ptr<Order> sellOrder = std::make_shared<LimitOrder>(trader.getID(), appleStock.getPrice(), quantity);
    sellOrder->setOrderType(OrderType::SELL);

    // Excecute a trade based of price thresholds
    trader.trade(150, 160, 12, 13);

    // Add orders to the order book
    orderBook.addOrder(buyOrder);
    orderBook.addOrder(sellOrder);
}

int main() {
    // Create an order book
    OrderBook orderBook;

    //Create and start multiple trader threads
    std::vector<std::thread> traderThreads;
    int numTraders = 5;

    std::vector<Trader> traders;
	traders.reserve(numTraders);

    for (int i = 0; i < numTraders; ++i) {
        traders.emplace_back("Trader " + std::to_string(i + 1));
        traderThreads.emplace_back(traderFunction, std::ref(traders.back()), std::ref(orderBook));
    }

    // Join trader threads (wait for all threads to finish)
    for (auto& thread : traderThreads) {
        thread.join();
    }

    // Print the orderbook after all trading is done
    orderBook.printOrderBook();

    return 0;
}