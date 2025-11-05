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
    LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        Node* temp = list.getHead();
        if (temp && list.removeHead()) {
            return temp->data;
        } else {
            throw std::runtime_error("sldkfj");
        }
    }
    T popBack() override {
        Node* temp = list.getTail();
        if (temp && list.getTail()) {
            return temp->data;
        } else {
            throw std::runtime_error("sldkfj");
        }
    }

    // Element Accessors
    const T& front() const override {
        Node* temp = list.getHead();
        if (temp) {
            return temp->data;
        } else {
            throw std::runtime_error("sldkfj");
        }
    }
    const T& back() const override {
        Node* temp = list.getTail();
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






