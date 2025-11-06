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
        const typename LinkedList<T>::Node* temp = list.getTail();
        if (temp && list.getTail()) {
            return temp->data;
        } else {
            throw std::runtime_error("sldkfj");
        }
    }

    // Access
    T peek() const override {
        const typename LinkedList<T>::Node* temp = list.getTail();
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