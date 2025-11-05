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
    LLS() {}

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        if (list.getCount() > 0) {
            T temp = list.head->data;
            list.removeHead();
            return temp;
        }
        throw std::out_of_range("No head found");
    }

    // Access
    T peek() const override {
        if (list.getCount() > 0) {
            return list.head->data;
        }
        throw std::out_of_range("No head found");
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return static_cast<size_t>(list.getCount());
    }

    void PrintForward() {
        list.printForward();
    }

    void PrintReverse() {
        list.printReverse();
    }
};