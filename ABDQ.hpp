#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                   // underlying dynamic array
    std::size_t capacity_ = 4;  // total allocated capacity
    std::size_t size_ = 0;      // number of stored elements
    std::size_t front_ = 0;     // index of front element
    std::size_t back_ = 0;      // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;
    void resize_capacity(double scale) {
        T stack_array[size_];
        for (size_t i = 0; i < size_; i++) {
            stack_array[i] = data_[i];
        }
        delete[] data_;
        capacity_ *= scale;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = stack_array[i];
        }
    }
    void insert_at(int idx, const T& item) {
        if (idx == -1) {
            idx = capacity_ - 1;

        } else if (idx == capacity_) {
            idx = 0;
        }
        data_[idx] = item;
        front_ = idx;
    }

public:
    // Big 5
    ABDQ(): data_(new T[4]) {}
    explicit ABDQ(std::size_t capacity): capacity_(capacity), data_(new T[capacity]) {}
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ() {delete[] data_;}

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            resize_capacity(2);
        }
        insert_at(front_ - 1, item);
    }
    void pushBack(const T& item) override {

    }

    // Deletion
    T popFront() override {

    }
    T popBack() override {

    }

    // Access
    const T& front() const override {return data_[front_];}
    const T& back() const override {return data_[back_];}

    // Getters
    std::size_t getSize() const noexcept override {return size_;}

    void print() {
        for (size_t i = 0; i < capacity_; i++) {
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }
};
