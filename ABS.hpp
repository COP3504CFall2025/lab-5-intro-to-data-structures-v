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
    ABS() {array_ = new T[capacity_];};
    explicit ABS(const size_t capacity): capacity_(capacity) {array_ = new T[capacity_];};
    ABS(const ABS& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABS& operator=(const ABS& rhs) {
        if (rhs.array_ == this->array_) {return *this;}
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = rhs.array_[i];
        }
        return *this;
    }
    ABS(ABS&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (rhs.array_ == this->array_) {return *this;}
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;
        return *this;
    }
    ~ABS() noexcept {delete[] array_;}

    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size_ + 1 > capacity_) {
            T stack_array[curr_size_];
            for (size_t i = 0; i < curr_size_; i++) {
                stack_array[i] = array_[i];
            }
            delete[] array_;
            capacity_ *= scale_factor_;
            array_ = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                array_[i] = stack_array[i];
            }
        }

        array_[curr_size_++] = data;
    }

    T peek() const override {
        if (curr_size_ == 0) {
            delete[] array_;
            throw std::runtime_error("abc");
        }
        return array_[curr_size_ - 1];
    }

    // why downsize required?
    T pop() override {
        if (curr_size_ == 0) {
            delete[] array_;
            throw std::runtime_error("abc");
        }
        if (curr_size_ - 1 <= (capacity_ / (scale_factor_ * 2))) {
            T stack_array[curr_size_];
            for (size_t i = 0; i < curr_size_; i++) {
                stack_array[i] = array_[i];
            }
            delete[] array_;
            capacity_ /= scale_factor_;
            array_ = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                array_[i] = stack_array[i];
            }
        }
        return array_[--curr_size_];
    }

private:
    size_t capacity_ = 1;
    size_t curr_size_ = 0;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
