#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T>
{
private:
    LinkedList<T> list;

public:
    // Constructor
    LLQ() {}

    // Insertion
    void enqueue(const T &item) override
    {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override
    {
        if (list.getCount() > 0)
        {
            T temp = list.head->data;
            list.removeHead();
            return temp;
        }
        throw std::runtime_error("Head not found");
    }

    // Access
    T peek() const override
    {
        if (list.getCount() > 0)
        {
            return list.head->data;
        }
        throw std::runtime_error("Head not found");
    }

    // Getter
    std::size_t getSize() const noexcept override { return list.getCount(); }

    void PrintForward()
    {
        list.printForward();
    }

    void PrintReverse()
    {
        list.printReverse();
    }
};