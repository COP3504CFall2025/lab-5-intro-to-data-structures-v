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
      : data_(new T[other.capacity_]), capacity_(other.capacity_),
        size_(other.size_) {
    for (size_t i = 0; i < other.size_; i++) {
      size_t other_index = (other.front_ + i) % other.capacity_;
      data_[i] = other.data_[other_index];
    }

    front_ = 0;
    back_ = size_;
  }

  ABDQ(ABDQ &&other) noexcept
      : data_(other.data_), capacity_(other.capacity_), size_(other.size_),
        front_(other.front_), back_(other.back_) {
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
      size_t other_index = (other.front_ + i) % other.capacity_;
      temp[i] = other.data_[other_index];
    }

    delete[] data_;

    data_ = temp;
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = 0;
    back_ = size_;

    return *this;
  }

  ABDQ &operator=(ABDQ &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    data_ = other.data_;
    capacity_ = other.capacity_;
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
    front_ = (front_ - 1 + capacity_) % capacity_;
    data_[front_] = item;
    size_++;
  }

  void pushBack(const T &item) override {
    ensureCapacity();
    data_[back_] = item;
    back_ = (back_ + 1) % capacity_;
    size_++;
  }

  // -- Deletion --

  T popFront() override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot pop from empty deque");
    }

    shrinkIfNeeded();
    size_--;

    T temp = data_[front_];
    front_ = (front_ + 1) % capacity_;
    return temp;
  }

  T popBack() override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot pop from empty deque");
    }

    shrinkIfNeeded();
    size_--;

    back_ = (back_ - 1 + capacity_) % capacity_;
    T temp = data_[back_];
    return temp;
  }

  // -- Access --

  const T &front() const override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot access elements from empty deque");
    }

    return data_[front_];
  }

  const T &back() const override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot access elements from empty deque");
    }

    size_t index = (back_ - 1 + capacity_) % capacity_;
    return data_[index];
  }

  // Getters
  std::size_t getSize() const noexcept override { return size_; }

private:
  // -- Extremities --

  void ensureCapacity() {
    if (size_ < capacity_) {
      return;
    }

    size_t old_capacity = capacity_;

    capacity_ *= SCALE_FACTOR;

    T *temp = new T[capacity_];

    for (size_t i = 0; i < size_; i++) {
      size_t index = (front_ + i) % old_capacity;
      temp[i] = data_[index];
    }

    delete[] data_;
    data_ = temp;
    front_ = 0;
    back_ = size_;
  }

  void shrinkIfNeeded() {
    if (size_ * 4 > capacity_) {
      return;
    }

    size_t old_capacity = capacity_;

    capacity_ /= SCALE_FACTOR;

    T *temp = new T[capacity_];

    for (size_t i = 0; i < size_; i++) {
      size_t index = (front_ + i) % old_capacity;
      temp[i] = data_[index];
    }

    delete[] data_;
    data_ = temp;
    front_ = 0;
    back_ = size_;
  }

  T *data_;              // underlying dynamic array
  std::size_t capacity_; // total allocated capacity
  std::size_t size_;     // number of stored elements
  std::size_t front_;    // index of front element
  std::size_t back_;     // index after the last element (circular)

  static constexpr std::size_t SCALE_FACTOR = 2;
};
