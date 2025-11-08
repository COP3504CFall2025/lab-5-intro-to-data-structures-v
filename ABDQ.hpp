#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    std::size_t capacity_;    // total allocated capacity
    T* data_; 
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

    void ensureCapacity() {
        if (size_ < capacity_) { return; }

        size_t oldCapacity = capacity_;
        capacity_ *= SCALE_FACTOR;
        T* temp = new T[capacity_];

        for (size_t i = 0; i < size_; i++) {
            size_t index = (front_ + i) % oldCapacity;
            temp[i] = data_[index];
        }

        delete[] data_;
        data_ = temp;
        front_ = 0;
        back_ = size_;
    }

    void shrinkIfNeeded() {
        if (size_ >= capacity_/4) { return; }

        size_t oldCapacity = capacity_;
        capacity_ /= SCALE_FACTOR;
        T* temp = new T[capacity_];

        for (size_t i = 0; i < size_; i++) {
            size_t index = (front_ + i) % capacity_;
            temp[i] = data_[index];
        }

        delete[] data_;
        data_ = temp;
        front_ = 0;
        back_ = size_;
    }

public:
    // Big 5
    ABDQ() : capacity_(4), data_(new T[capacity_]), size_(0), front_(0), back_(0) {}
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        data_ = new T[capacity];
        front_ = 0;
        back_ = 0;
        size_ = 0;
    }
    
    ABDQ(const ABDQ& other) {
        data_ = new T[other.capacity_];

        for (size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }

        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
    }

    ABDQ(ABDQ&& other) noexcept {
        T* newArr = other.data_;
        size_t newCap = other.capacity_;
        size_t newSize = other.size_;
        size_t newFront = other.front_;
        size_t newBack = other.back_;

        data_ = newArr;
        capacity_ = newCap;
        size_ = newSize;
        front_ = newFront;
        back_ = newBack;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;

        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; ++i)
            data_[i] = other.data_[i];

        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) { return *this; }
        T* newArr = other.data_;
        size_t newCap = other.capacity_;
        size_t newSize = other.size_;
        size_t newFront = other.front_;
        size_t newBack = other.back_;

        delete[] data_;

        data_ = newArr;
        capacity_ = newCap;
        size_ = newSize;
        front_ = newFront;
        back_ = newBack;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.back_ = 0;
        other.front_ = 0;

        return *this;
    }

    ~ABDQ() {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        ensureCapacity();

        front_ = (front_ - 1 + capacity_) % capacity_;
        data_[front_] = item;
        size_++;

    }
    void pushBack(const T& item) override {
        ensureCapacity();

        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) { throw std::runtime_error("Array is empty!"); }

        T front = data_[front_];
        front_ = (front_ + capacity_) % capacity_;
        size_--;

        shrinkIfNeeded();
        return front;
    }

    T popBack() override {
        if (size_ == 0) { throw std::runtime_error("Array is empty!"); }
        
        T back = data_[back_-1];
        back_ = (back_ - 1 + capacity_) % capacity_;
        size_--;
        
        shrinkIfNeeded();
        return back;
    }

    // Access
    const T& front() const override { 
        if (size_ == 0) { throw std::runtime_error("Array is empty!"); }
        return data_[front_];
    }
    const T& back() const override { 
        if (size_ == 0) { throw std::runtime_error("Array is empty!"); }
        size_t lastIndex = (back_ - 1 + capacity_) % capacity_;
        return data_[lastIndex];
    }

    // Getters
    std::size_t getSize() const noexcept override { return size_; }
};