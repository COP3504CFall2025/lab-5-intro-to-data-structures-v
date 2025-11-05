#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.getCount() > 0) {
            T temp = list.head->data;
            list.removeHead();
            return temp;
        }
        throw std::out_of_range("No head found");
    }

    T popBack() override {
        if (list.getCount() > 0) {
            T temp = list.tail->data;
            list.removeTail();
            return temp;
        }
        throw std::out_of_range("No tail found");
    }

    // Element Accessors
    const T& front() const override {
        if (list.getCount() > 0) {
            return list.head->data;
        }
        throw std::out_of_range("No head found");
    }
    const T& back() const override {
        if (list.getCount() > 0) {
            return list.tail->data;
        }
        throw std::out_of_range("No tail found");
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return static_cast<size_t>(list.getCount());
    }
};






