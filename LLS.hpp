#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>
#include <stdlib.h>

template <typename T> class LLS : public StackInterface<T> {
public:
  // Insertion
  void push(const T &item) override { list.AddHead(item); }

  // Deletion
  T pop() override {
    T temp = list.getHead();
    list.RemoveHead();
    return temp;
  }

  // Access
  T peek() const override { return list.getHead(); }

  // Getters
  std::size_t getSize() const noexcept override { return list.getCount(); }

private:
  LinkedList<T> list;
};