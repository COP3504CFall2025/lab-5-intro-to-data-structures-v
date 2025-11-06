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
    LLDQ() : list(new LinkedList<T>()) {}

    // Core Insertion Operations
    void pushFront(const T& item) override { list.addHead(); }
    void pushBack(const T& item) override { list.addTail(); }

    // Core Removal Operations
    T popFront() override { list.removeHead(); }
    T popBack() override { list.removeTail(); }

    // Element Accessors
    const T& front() const override { list.getHead(); }
    const T& back() const override { list.getTail(); }

    // Getter
    std::size_t getSize() const noexcept override { list.getCount(); }

    void printForward() const {
        list.printForward();
    }

    void printReverse() const {
        list.printReverse();
    }
};






