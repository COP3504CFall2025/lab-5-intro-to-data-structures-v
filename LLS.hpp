#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        typename LinkedList<T>::Node* temp = list.getHead();
        if (temp && list.removeHead()) {
            return temp->data;
        } else {
            throw std::runtime_error("sldkfj");
        }
    }

    // Access
    T peek() const override {
        typename LinkedList<T>::Node* temp = list.getHead();
        if (temp) {
            return temp->data;
        } else {
            throw std::runtime_error("sldkfj");
        }
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};