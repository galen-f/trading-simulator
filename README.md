# Stock Trading Simulator 📈📉
A multithreaded C++ simulation of a stock trading system. This program allows multiple traders to place buy and sell order on a shared order book, matches those orders using a price-time priority strategy, and then displays the final unmatched orders. <br>
I am currently working on expanding this system to include a reactive pricing system, accounting for supply and demand.

---

## What It Does ⚒
- **Simulates Trader** <br> Spawns multiple trader "threads" that randomly buy or sell stocks over a series of ticks.
- **Real Market Simulation** <br> Allows traders to purchase market orders or limit orders.
- **Order Book Management** <br> Collects all incoming buy/sell orders in a thread-safe order book.
- **Matching Engine** <br> Uses price-time priority strategy to match compatible buy and sell orders.

---

## Skills 🧠
- C++17
- Object Oriented Design
- Factory design pattern
- Multithreading and concurrency

### Fin-skills 💲
- Market Microstructure
- Liquidity and Slippage Awareness
- Algorithmic trading
- Financial Simulation
- Quantitative Reasoning

---

## Getting Started </>
### Prerequisites ⚠️
- C++17 compatible compiler (e.g. `G++`, `clang++`)
- POSIX threads support

### Build ⛏️

  ```bash
  g++ -std=c++17 -pthread \
    src/*.cpp \
    -I include \
    -o stock_trading_sim
  ```
### Run 🏃🏻
`./stock_trading_sim`

