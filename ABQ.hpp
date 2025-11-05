#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_ = 1;
    size_t curr_size_ = 0;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ(): array_(new T[capacity_]) {}
    explicit ABQ(const size_t capacity): capacity_(capacity), array_(new T[capacity]) {}
    ABQ(const ABQ& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
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
    ABQ(ABQ&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (rhs.array_ == this->array_) {return *this;}
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;
        return *this;
    }
    ~ABQ() noexcept {
        delete[] array_;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // Insertion
    void enqueue(const T& data) override {
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
        for (size_t i = curr_size_; i > 0; i--) {
            array_[i] = array_[i - 1];
        }
        array_[0] = data;
        curr_size_++;
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) {throw std::runtime_error("abc");}
        return array_[curr_size_ - 1];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) {throw std::runtime_error("abc");}
        if (curr_size_ - 1 <= (capacity_ / scale_factor_)) {
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

};
