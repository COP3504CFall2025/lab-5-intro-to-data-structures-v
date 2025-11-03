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
    T temp = list.GetHead();
    list.RemoveHead();
    return temp;
  }

  // Access
  T peek() const override { return list.GetHead(); }

  // Getters
  std::size_t getSize() const noexcept override { return list.GetCount(); }

private:
  LinkedList<T> list;
};