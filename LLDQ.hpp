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
    T temp = list.GetHead();
    list.RemoveHead();
    return temp;
  }

  T popBack() override {
    T temp = list.GetTail();
    list.RemoveTail();
    return temp;
  }

  // -- Element Accessors --

  const T &front() const override { list.GetHead(); }

  const T &back() const override { list.GetTail(); }

  // Getter
  std::size_t getSize() const noexcept override { return list.GetCount(); }

private:
  LinkedList<T> list;
};
