#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;

    // Insertion
    void enqueue(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T dequeue() override {
        T temp = list.getTail()->data;
        if (list.removeTail()) {
            return temp;
        } else {
            throw std::runtime_error("sldkfj");
        }
    }

    // Access
    T peek() const override {
        T temp = list.getTail();
        if (temp) {
            return temp->data;
        } else {
            throw std::runtime_error("sldkfj");
        }
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

};