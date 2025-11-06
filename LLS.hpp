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
    LLS() : list(new LinkedList<T>()) {}

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        T head = list.getHead();
        list.removeHead();
        return head;
    }

    // Access
    T peek() const override {
        Node<T>* head = list.getHead();
        return head->getData();
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void printForward() const {
        list.printForward();
    }

    void printReverse() const {
        list.printReverse();
    }
};