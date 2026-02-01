#pragma once
#include <cstdint>

enum class OrderType
{
    LIMIT,
    MARKET
};
enum class Side
{
    BUY,
    SELL
};

struct Order
{
    uint64_t id;
    double price;
    double quantity;
    Side side;
    OrderType type;

    // 用於鏈結同一價格層級的訂單 (Intrusive Linked List 概念，比 std::list 快)
    Order *next = nullptr;
    Order *prev = nullptr;

    void reset(uint64_t _id, double _price, double _qty, Side _side, OrderType _type)
    {
        id = _id;
        price = _price;
        quantity = _qty;
        side = _side;
        type = _type;
        next = nullptr;
        prev = nullptr;
    }
};