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
    LLS();

    // Insertion
    void push(const T& item) override;

    // Deletion
    T pop() override;

    // Access
    T peek() const override;

    //Getters
    std::size_t getSize() const noexcept override;
};

template<typename T>
void LLS<T>::push(const T& item) {
    list.addTail(item);
}
template<typename T>
T LLS<T>::pop() {
    T tail = list.getTail()->data;
    list.removeTail();
    return tail;
}
template<typename T>
T LLS<T>::peek() const {
    return list.getTail()->data;
}