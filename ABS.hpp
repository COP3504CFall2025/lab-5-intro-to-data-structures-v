#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(0), curr_size_(0), array_(nullptr) {}
    explicit ABS(const size_t capacity) {
        array_ = new T[capacity];
        capacity_ = capacity;
        curr_size_ = 0;
    }

    ABS(const ABS& other) {
        array_ = other.array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
    }

    ABS& operator=(const ABS& rhs) {
        if (this == rhs) { return *this; }
        T* newArr = rhs.array_;
        size_t newCap = rhs.capacity_;
        size_t newSize = rhs.curr_size_;

        delete[] array_;

        array_ = newArr;
        capacity_ = newCap;
        curr_size_ = newSize;

        return *this;
    }

    ABS(ABS&& other) noexcept {
        T* newArr = other.array_;
        size_t newCap = other.capacity_;
        size_t newSize = other.curr_size_;

        delete[] array_;

        array_ = newArr;
        capacity_ = newCap;
        curr_size_ = newSize;

        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs) { return *this; }
        T* newArr = rhs.array_;
        size_t newCap = rhs.capacity_;
        size_t newSize = rhs.curr_size_;

        delete[] array_;

        array_ = newArr;
        capacity_ = newCap;
        curr_size_ = newSize;

        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;

        return *this;
    }  

    ~ABS() noexcept {
        delete[] array_;
        curr_size_ = 0;
        capacity_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override { return curr_size_; }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept { return array_; }

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size_ == capacity_) {
            T* newArr = new T[capacity_*scale_factor_];
            std::copy(array_, array_+ curr_size_, newArr);
            delete[] array_;
            array_ = newArr;
        }

        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override {
        return array_[curr_size_];
    }

    T pop() override {
        T value = array_[curr_size_];
        curr_size_--;
        return value;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
