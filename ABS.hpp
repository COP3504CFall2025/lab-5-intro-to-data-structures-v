#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(1),curr_size_(0), array_(new T[capacity_]) {};
    explicit ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity_]) {};
    ABS(const ABS& other) : capacity_(1),curr_size_(0), array_(new T[capacity_]) {
        for (size_t i = 0; i < capacity_; i++) {
            array_[i] = other.getData()[i];
        }
    };
    ABS& operator=(const ABS& rhs) {
        if (this != &rhs) {
            delete[] array_;
            capacity_ = rhs.getMaxCapacity();
            curr_size_ = rhs.getSize();
            array_ = new T[capacity_];
            for (size_t i = 0; i < capacity_; i++) {
                array_[i] = rhs.getData()[i];
            }
        }
        return *this;
    };
    ABS(ABS&& other) noexcept : capacity_(1),curr_size_(0), array_(new T[capacity_]) {
        capacity_ = other.getMaxCapacity();
        curr_size_ = other.getSize();
        array_ = other.getData();

        other.getMaxCapacity() = 0;
        other.getSize() = 0;
        other.getData() = nullptr;
    };
    ABS& operator=(ABS&& rhs) noexcept {
        if (this != &rhs) {
            delete[] array_;
            capacity_ = rhs.getMaxCapacity();
            curr_size_ = rhs.getSize();
            array_ = rhs.getData();

            rhs.getMaxCapacity() = 0;
            rhs.getSize() = 0;
            rhs.getData() = nullptr;
        }
        return *this;
    };
    ~ABS() noexcept override {
        delete[] array_;
        capacity_ = 0;
        curr_size_ = 0;
    };

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    };

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    };

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    };

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size_ == capacity_) {
            capacity_ *= scale_factor_;
        }
        array_[curr_size_++] = data;
    };

    T peek() const override {
        return array_[curr_size_ - 1];
    };

    T pop() override {
        T value = array_[curr_size_ -1];
        curr_size_--;
        return value;
    };
    void printForward() {
        for (size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i] << std::endl;
        }
    }
    void printBackward() {
        for (int i = static_cast<int>(curr_size_) - 1; i >= 0; i--) {
            std::cout << array_[i] << std::endl;
        }
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
