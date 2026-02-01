#pragma once
#include <vector>
#include <memory>
#include <iostream>

// 一個簡單高效的物件池，避免運行時的 heap allocation
template <typename T>
class ObjectPool
{
private:
    std::vector<std::unique_ptr<T>> pool;
    std::vector<T *> free_list; // 這裡存的是裸指針，用於快速存取
    size_t pool_size;

public:
    explicit ObjectPool(size_t size) : pool_size(size)
    {
        pool.reserve(size);
        free_list.reserve(size);
        for (size_t i = 0; i < size; ++i)
        {
            auto obj = std::make_unique<T>();
            free_list.push_back(obj.get());
            pool.push_back(std::move(obj));
        }
    }

    // 獲取物件 (O(1))
    T *acquire()
    {
        if (free_list.empty())
        {
            // 在實際 HFT 系統中，這裡可能會報錯或動態擴容
            // 為了演示簡單，我們回傳 nullptr
            return nullptr;
        }
        T *obj = free_list.back();
        free_list.pop_back();
        return obj;
    }

    // 歸還物件 (O(1))
    void release(T *obj)
    {
        free_list.push_back(obj);
    }
};