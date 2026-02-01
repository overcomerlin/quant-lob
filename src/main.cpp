#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include "OrderBook.h"
#include "ObjectPool.h"

int main()
{
    const int NUM_ORDERS = 100000;
    ObjectPool<Order> pool(NUM_ORDERS * 2); // 預分配
    OrderBook book(pool);

    // 準備隨機數據
    std::mt19937 gen(42);
    std::uniform_int_distribution<> sideDist(0, 1);
    std::uniform_real_distribution<> priceDist(100.0, 200.0);
    std::uniform_real_distribution<> qtyDist(0.1, 5.0);

    std::cout << "Starting Benchmark: Processing " << NUM_ORDERS << " orders..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_ORDERS; ++i)
    {
        Side side = (sideDist(gen) == 0) ? Side::BUY : Side::SELL;
        book.addOrder(i, priceDist(gen), qtyDist(gen), side, OrderType::LIMIT);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Done." << std::endl;
    std::cout << "Time elapsed: " << diff.count() << " s" << std::endl;
    std::cout << "Throughput: " << NUM_ORDERS / diff.count() << " orders/sec" << std::endl;

    return 0;
}