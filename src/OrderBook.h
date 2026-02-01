#pragma once
#include <map>
#include <list>
#include <iostream>
#include "Order.h"
#include "ObjectPool.h"

// 使用 map 自動排序價格: O(log N) 查找
// Key: Price, Value: Order Linked List (FIFO)
using PriceLevel = std::list<Order *>;

class OrderBook
{
private:
    std::map<double, PriceLevel, std::greater<double>> bids; // 買單：價格高優先
    std::map<double, PriceLevel, std::less<double>> asks;    // 賣單：價格低優先
    ObjectPool<Order> &orderPool;

public:
    OrderBook(ObjectPool<Order> &pool) : orderPool(pool) {}

    // 核心撮合邏輯
    void addOrder(uint64_t id, double price, double quantity, Side side, OrderType type)
    {
        // 1. 嘗試撮合 (Matching)
        if (side == Side::BUY)
        {
            match(id, price, quantity, side, asks, bids);
        }
        else
        {
            match(id, price, quantity, side, bids, asks);
        }
    }

    template <typename OppositeBook, typename MyBook>
    void match(uint64_t id, double price, double &quantity, Side side, OppositeBook &oppositeBook, MyBook &myBook)
    {
        auto it = oppositeBook.begin();

        while (it != oppositeBook.end() && quantity > 0)
        {
            double bestPrice = it->first;

            // 如果是買單，bestPrice (賣價) 必須 <= 我的出價
            // 如果是賣單，bestPrice (買價) 必須 >= 我的出價
            if ((side == Side::BUY && bestPrice > price) ||
                (side == Side::SELL && bestPrice < price))
            {
                break;
            }

            PriceLevel &level = it->second;
            auto orderIt = level.begin();

            while (orderIt != level.end() && quantity > 0)
            {
                Order *oppOrder = *orderIt;
                double tradeQty = std::min(quantity, oppOrder->quantity);

                // executeTrade(id, oppOrder->id, tradeQty, bestPrice); // 模擬成交

                quantity -= tradeQty;
                oppOrder->quantity -= tradeQty;

                if (oppOrder->quantity <= 0)
                {
                    orderPool.release(oppOrder); // 歸還記憶體池
                    orderIt = level.erase(orderIt);
                }
                else
                {
                    ++orderIt;
                }
            }

            if (level.empty())
            {
                it = oppositeBook.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // 2. 如果還有剩餘量，掛單 (Resting Order)
        if (quantity > 0)
        {
            Order *newOrder = orderPool.acquire();
            if (newOrder)
            {
                newOrder->reset(id, price, quantity, side, OrderType::LIMIT);
                myBook[price].push_back(newOrder);
            }
        }
    }
};