#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T> class LLDQ : public DequeInterface<T> {

public:
  // -- Core Insertion Operations --

  void pushFront(const T &item) override { list.AddHead(item); }

  void pushBack(const T &item) override { list.AddTail(item); }

  // -- Core Removal Operations --

  T popFront() override {
    T temp = list.getHead()->data;
    list.RemoveHead();
    return temp;
  }

  T popBack() override {
    T temp = list.getTail()->data;
    list.RemoveTail();
    return temp;
  }

  // -- Element Accessors --

  const T &front() const override { return list.getHead()->data; }

  const T &back() const override { return list.getTail()->data; }

  // Getter
  std::size_t getSize() const noexcept override { return list.getCount(); }

private:
  LinkedList<T> list;
};
