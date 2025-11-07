#pragma once

#include "Interfaces.hpp"
#include <cstddef>
#include <stdexcept>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T> class ABQ : public QueueInterface<T> {
public:
  // -- Constructors + Big 5 --

  ABQ() : capacity_(1), curr_size_(0), array_(new T[1]) {}

  explicit ABQ(const size_t capacity)
      : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}

  ABQ(const ABQ &other)
      : capacity_(other.capacity_), curr_size_(other.size_),
        array_(new T[other.capacity_]) {
    for (size_t i = 0; i < other.size_; i++) {
      array_[i] = other.array_[i];
    }
  }

  ABQ &operator=(const ABQ &rhs) {
    if (this == &rhs) {
      return *this;
    }

    T *temp = new T[rhs.capacity_];

    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = temp;

    for (size_t i = 0; i < rhs.curr_size_; i++) {
      array_[i] = rhs.array_[i];
    }
  }

  ABQ(ABQ &&other) noexcept {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = other.array_;

    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
  }

  ABQ &operator=(ABQ &&rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }

    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = rhs.array_;

    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    rhs.array_ = nullptr;
  }

  ~ABQ() noexcept override { delete[] array_; }

  // -- Getters --

  [[nodiscard]] size_t getSize() const noexcept override { return curr_size_; }

  [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }

  [[nodiscard]] T *getData() const noexcept { return array_; }

  // Insertion
  void enqueue(const T &data) override {
    curr_size_++;
    ensureCapacity();
    array_[curr_size_] = data;
  }

  // Access
  T peek() const override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot peek from empty queue");
    }

    return array_[0];
  }

  // Deletion
  T dequeue() override {
    if (size_ == 0) {
      throw std::runtime_error("Cannot deque from empty queue");
    }

    T temp = array_[curr_size_];
    curr_size_--;
    shrinkIfNeeded();
    return temp;
  }

private:
  void ensureCapacity() {
    if (size_ <= capacity_) {
      return;
    }

    capacity_ *= scale_factor_;

    T *temp = new T[capacity_];

    for (size_t i = 0; i < curr_size_; i++) {
      temp[i] = array_[i];
    }

    delete[] data_;
    data_ = temp;
  }

  void shrinkIfNeeded() {
    if (size_ >= capacity_ / 4) {
      return;
    }

    capacity_ /= scale_factor_;

    T *temp = new T[capacity_];

    for (size_t i = 0; i < curr_size_; i++) {
      temp[i] = array_[i];
    }

    delete[] data_;
    data_ = temp;
  }

  size_t capacity_;
  size_t curr_size_;
  T *array_;
  static constexpr size_t scale_factor_ = 2;
};
