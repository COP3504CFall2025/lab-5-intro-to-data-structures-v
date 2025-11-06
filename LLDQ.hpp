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
    void pushFront(const T& item) override { list.addHead(item); }
    void pushBack(const T& item) override { list.addTail(item); }

    // Core Removal Operations
    T popFront() override { 
        const Node<T>* head = list.getHead();
        T headData = head->data;
        list.removeHead();
        return headData;
    }

    T popBack() override {
        const Node<T>* tail = list.getTail();
        T tailData = tail->data;
        list.removeTail();
        return tailData;
    }

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






