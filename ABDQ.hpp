#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)
    T* data_;                 // underlying dynamic array

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : capacity_(4), size_(0), front_(0), back_(0), data_(new T[capacity_]) {};
    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0), data_(new T[capacity_]) {};
    ABDQ(const ABDQ& other) {
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        size_ = other.getSize();
        data_ = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }
    };
    ABDQ(ABDQ&& other) noexcept : capacity_(4), size_(0), front_(0), back_(0), data_(nullptr) {
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        size_ = other.getSize();
        data_ = other.data_;

        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.size_ = 0;
        other.data_ = nullptr;
    };
    ABDQ& operator=(const ABDQ& other) {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            front_ = other.front_;
            back_ = other.back_;
            size_ = other.getSize();
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    };
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            front_ = other.front_;
            back_ = other.back_;
            size_ = other.getSize();
            data_ = other.data_;

            other.capacity_ = 0;
            other.front_ = 0;
            other.back_ = 0;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    };
    ~ABDQ() override {
        capacity_ = 0;
        front_ = 0;
        back_ = 0;
        size_ = 0;
        delete[] data_;
    };

    void ensureCapacity() {
        size_t old_capacity = capacity_;
        capacity_ *= SCALE_FACTOR;
        T* temp = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            temp[i] = data_[(front_ + i) % old_capacity];
        }
        delete[] data_;
        data_ = temp;
        front_ = 0;
        back_ = size_;
    }

    void shrinkIfNeeded() {
        size_t old_capacity = capacity_;
        capacity_ /= SCALE_FACTOR;
        T* temp = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            temp[i] = data_[(front_ + i) % old_capacity];
        }
        delete[] data_;
        data_ = temp;
        front_ = 0;
        back_ = size_;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
        }
        front_ = (front_ - 1 + capacity_) % capacity_;
        data_[front_] = item;
        size_++;
    };
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    };

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty queue");
        }
        T value = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        if (capacity_ / SCALE_FACTOR > size_) {
            shrinkIfNeeded();
        }
        return value;
    };
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty queue");
        }
        back_ = (back_ - 1 + capacity_) % capacity_;
        T value = data_[back_];
        size_--;
        if (capacity_ / SCALE_FACTOR > size_) {
            shrinkIfNeeded();
        }
        return value;
    };

    // Access
    const T& front() const override {
        return data_[front_];
    };
    const T& back() const override {
        return data_[back_];
    };

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    };

    void printForward() {
        for (size_t i = 0; i < size_; i++) {
            std::cout << data_[(front_ + i) % capacity_] << std::endl;
        }
    };
    void printBackward() {
        for (int i = static_cast<int>(size_) - 1; i >= 0; i--) {
            std::cout << data_[(back_ - 1 - i + capacity_) % capacity_] << std::endl;
        }
    };

};
