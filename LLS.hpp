#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>
#include <stdlib.h>

template <typename T> class LLS : public StackInterface<T> {
public:
  // Insertion
  void push(const T &item) override { list.addHead(item); }

  // Deletion
  T pop() override {
    auto *head = list.getHead();

    if (!head) {
      throw std::runtime_error("Cannot pop in empty list");
    }

    T temp = head->data;
    list.removeHead();
    return temp;
  }

  // Access
  T peek() const override {
    auto *head = list.getHead();

    if (!head) {
      throw std::runtime_error("Cannot peek in empty list");
    }

    return head->data;
  }

  // Getters
  std::size_t getSize() const noexcept override { return list.getCount(); }

private:
  LinkedList<T> list;
};
