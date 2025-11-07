#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>
#include <stdlib.h>

template <typename T> class LLQ : public QueueInterface<T> {

public:
  // Insertion
  void enqueue(const T &item) override { list.addTail(item); }

  // Deletion
  T dequeue() override {
    auto *head = list.getHead();

    if (!head) {
      throw std::runtime_error("Cannot dequeue in empty queue");
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

  // Getter
  std::size_t getSize() const noexcept override { return list.getCount(); }

private:
  LinkedList<T> list;
};
