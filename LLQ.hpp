#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>
#include <stdlib.h>

template <typename T> class LLQ : public QueueInterface<T> {

public:
  // Insertion
  void enqueue(const T &item) override { list.AddTail(item); }

  // Deletion
  T dequeue() override {
    T temp = list.getHead()->data;
    list.RemoveHead();
    return temp;
  }

  // Access
  T peek() const override { return list.getHead()->data; }

  // Getter
  std::size_t getSize() const noexcept override { return list.getCount(); }

private:
  LinkedList<T> list;
};