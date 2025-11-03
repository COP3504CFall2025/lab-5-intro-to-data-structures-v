#pragma once

#include "Interfaces.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T> class ABDQ : public DequeInterface<T> {

public:
  // -- Big 5 --

  ABDQ() : data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0) {}

  explicit ABDQ(std::size_t capacity)
      : data_(new T[capacity]), capacity_(capacity), size_(0), front_(0),
        back_(0) {}

  ABDQ(const ABDQ &other)
      : data_(new T[other.capacity_]), size_(other.size_), front_(other.front_),
        back_(other.back_) {
    for (size_t i = 0; i < other.size_; i++) {
      data_[i] = other.data_[i];
    }
  }

  ABDQ(ABDQ &&other) noexcept
      : data_(other.data_), size_(other.size_), front_(other.front_),
        back_(other.back_) {
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
    other.front_ = 0;
    other.back_ = 0;
  }

  ABDQ &operator=(const ABDQ &other) {
    if (this == &other) {
      return *this;
    }

    T *temp = new T[other.capacity_];

    for (size_t i = 0; i < other.size_; i++) {
      temp[i] = other.data_[i];
    }

    delete[] data_;

    data_ = temp;
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;

    return *this;
  }

  ABDQ &operator=(ABDQ &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    data_ = other.data_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;

    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
    other.front_ = 0;
    other.back_ = 0;

    return *this;
  }

  ~ABDQ() { delete[] data_; }

  // -- Insertion --

  void pushFront(const T &item) override {
    ensureCapacity();

    for (size_t i = size_ - 1; i > 0; i--) {
      data_[i] = data_[i - 1];
    }

    data_[0] = item;
    size_++;
  }

  void pushBack(const T &item) override {
    ensureCapacity();
    data_[size_] = item;
    size_++;
  }

  // -- Deletion --

  T popFront() override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot pop from empty deque");
    }

    shrinkIfNeeded();

    T temp = data_[0];

    for (size_t i = 0; i < size_ - 1; i++) {
      data_[i] = data_[i + 1];
    }

    size_--;

    return temp;
  }

  T popBack() override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot pop from empty deque");
    }

    shrinkIfNeeded();
    size_--;

    return data_[size_];
  }

  // -- Access --

  const T &front() const override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot access elements from empty deque");
    }

    return data_[0];
  }

  const T &back() const override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot access elements from empty deque");
    }

    return data_[size_];
  }

  // -- Extremities --

  void ensureCapacity() {
    if (size_ < capacity_) {
      return;
    }

    capacity_ *= SCALE_FACTOR;

    T *temp = new T[capacity_];

    for (size_t i = 0; i < size_; i++) {
      temp[i] = data_[i];
    }

    delete[] data_;
    data_ = temp;
  }

  void shrinkIfNeeded() {
    if (size_ * 4 > capacity_) {
      return;
    }

    capacity_ /= SCALE_FACTOR;

    T *temp = new T[capacity_];

    for (size_t i = 0; i < size_; i++) {
      temp[i] = data_[i];
    }

    delete[] data_;
    data_ = temp;
  }

  // Getters
  std::size_t getSize() const noexcept override { return size_; }

private:
  T *data_;              // underlying dynamic array
  std::size_t capacity_; // total allocated capacity
  std::size_t size_;     // number of stored elements
  std::size_t front_;    // index of front element
  std::size_t back_;     // index after the last element (circular)

  static constexpr std::size_t SCALE_FACTOR = 2;
};
