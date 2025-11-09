#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T>
{
private:
    T *data_;              // underlying dynamic array
    std::size_t capacity_; // total allocated capacity
    std::size_t size_;     // number of stored elements
    std::size_t front_;    // index of front element
    std::size_t back_;     // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ()
    {
        this->capacity_ = 4;
        this->size_ = 0;
        this->front_ = 0;
        this->back_ = 0;
        this->data_ = new T[this->capacity_];
    }

    explicit ABDQ(std::size_t capacity)
    {
        this->capacity_ = capacity;
        this->size_ = 0;
        this->front_ = 0;
        this->back_ = 0;
        this->data_ = new T[this->capacity_];
    }

    ABDQ(const ABDQ &other)
    {
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->data_ = new T[this->capacity_];

        for (size_t i = 0; i < this->size_; i++)
        {
            this->data_[i] = other.data_[i];
        }
    }

    ABDQ(ABDQ &&other) noexcept
    {
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->data_ = other.data_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
    }

    ABDQ &operator=(const ABDQ &other)
    {
        if (this == &other)
        {
            return *this;
        }

        T *temp = new T[other.capacity_];
        delete[] this->data_;
        this->data_ = temp;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        for (size_t i = 0; i < size_; i++)
        {
            this->data_[i] = other.data_[i];
        }
    }
    ABDQ &operator=(ABDQ &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] this->data_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->data_ = other.data_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
    }

    ~ABDQ() override
    {
        delete[] this->data_;
        this->data_ = nullptr;
        this->capacity_ = 0;
        this->size_ = 0;
        this->front_ = 0;
        this->back_ = 0;
    }

    // Insertion
    void pushFront(const T &item) override
    {
        if (size_ > capacity_)
        {
            //     resize();
        }

        // this->data_[front_ - 1] = item;
        // --front_;
        // ++size_;
    }

    void pushBack(const T &item) override
    {
    }

    /*void resize()
    {
        T *temp = new T[capacity_ * 2];
        this->capacity_ *= 2;

        for (size)
    }*/

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T &front() const override;
    const T &back() const override;

    // Getters
    std::size_t getSize() const noexcept override;
};
