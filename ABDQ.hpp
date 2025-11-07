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

        T begin_part[size_ / 2];
        T end_part[size_ / 2];
        std::size_t front_disp;
        if (front_ < back_) {
            for (size_t i = 0; i < size_; i++) {
                stack_array[i] = data_[i];
            }
        } else {
            front_disp = capacity_ - front_;
            for (size_t i = 0; i < back_; i++) {
                begin_part[i] = data_[i];
            }
            for (size_t i = front_; i < capacity_; i++) {
                end_part[i - front_] = data_[i];
            }
        }

        delete[] data_;
        capacity_ *= scale;
        data_ = new T[capacity_];

        // std::cout << "front disp: " << front_disp << std::endl;
        // for (size_t i = 0; i < size_ / 2; i++) {
        //     std::cout << end_part[i] << " ";
        // }
        // std::cout << std::endl;

        if (front_ < back_) {
            for (size_t i = 0; i < size_; i++) {
                data_[i] = stack_array[i];
            }
        } else {
            for (size_t i = 0; i < back_; i++) {
                data_[i] = begin_part[i];
            }
            // std::cout << "end index: " << capacity_ - front_disp << std::endl;
            // std::cout << "cap: " << capacity_ << std::endl;
            for (size_t i = capacity_ - front_disp; i < capacity_; i++) {
                // std::cout << "accessing end part idx: " << i - (capacity_ - front_disp) << std::endl;
                data_[i] = end_part[i - (capacity_ - front_disp)];
            }
        }

    }
    size_t get_wrapped_idx(int idx) {
        if (idx == -1) {
            idx = capacity_ - 1;

        } else if (idx == capacity_) {
            idx = 0;
        }
        return idx;
    }

public:
    // Big 5
    ABDQ(): data_(new T[4]) {}
    explicit ABDQ(std::size_t capacity): capacity_(capacity), data_(new T[capacity]) {}
    ABDQ(const ABDQ& other): capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++) {
            data_[i] = other.data[i];
        }
    }

    ABDQ(ABDQ&& other) noexcept {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
    }

    ABDQ& operator=(const ABDQ& other) {
        if (data_ == other.data_) {return *this;}
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++) {
            data_[i] = other.data[i];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (data_ == other.data_) {return *this;}
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
        return *this;
    }
    ~ABDQ() {delete[] data_;}

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            resize_capacity(2);
        }
        size_++;
        size_t idx = get_wrapped_idx(front_ - 1);
        data_[idx] = item;

        front_ = idx;
        if (size_ == 1) {back_ = idx;}
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            resize_capacity(2);
        }
        size_++;
        size_t idx = get_wrapped_idx(back_ + 1);
        data_[idx] = item;

        back_ = idx;
        if (size_ == 1) {front_ = idx;}
    }

    // Deletion
    T popFront() override {
        T return_val = data_[front_];
        front_ = get_wrapped_idx(front_ + 1);
        return return_val;
    }
    T popBack() override {
        T return_val = data_[back_];
        back_ = get_wrapped_idx(back_ - 1);
        return return_val;
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
