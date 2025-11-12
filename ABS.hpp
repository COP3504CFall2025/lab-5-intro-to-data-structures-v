#pragma once

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T>
class ABS : public StackInterface<T>
{
public:
    // Big 5 + Parameterized Constructor
    ABS()
    {
        this->capacity_ = 1;
        this->curr_size_ = 0;
        this->array_ = new T[this->capacity_];
    }

    explicit ABS(const size_t capacity)
    {

        this->capacity_ = capacity;
        this->curr_size_ = 0;
        this->array_ = new T[this->capacity_];
    }

    ABS(const ABS &other)
    {

        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = new T[other.capacity_];

        for (size_t i = 0; i < curr_size_; i++)
        {
            this->array_[i] = other.array_[i];
        }
    }

    ABS &operator=(const ABS &rhs)
    {

        if (this == &rhs)
        {
            return *this;
        }

        T *temp = new T[rhs.capacity_];
        delete[] this->array_;

        this->array_ = temp;
        this->curr_size_ = rhs.curr_size_;
        this->capacity_ = rhs.capacity_;

        for (int i = 0; i < curr_size_; i++)
        {
            this->array_[i] = rhs.array_[i];
        }

        return *this;
    }

    ABS(ABS &&other) noexcept
    {

        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }

    ABS &operator=(ABS &&rhs) noexcept
    {

        if (this == &rhs)
        {
            return *this;
        }

        delete[] this->array_;

        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;

        return *this;
    }

    ~ABS() noexcept
    {

        delete[] this->array_;
        this->array_ = nullptr;
        this->capacity_ = 0;
        this->curr_size_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override { return curr_size_; }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }

    // Return underlying data for the stack
    [[nodiscard]] T *getData() const noexcept { return array_; }

    // Resize capacity of the stack
    void resize()
    {

        T *temp = new T[capacity_ * scale_factor_];
        this->capacity_ *= scale_factor_;

        for (size_t i = 0; i < this->curr_size_; i++)
        {
            temp[i] = this->array_[i];
        }

        delete[] this->array_;
        this->array_ = temp;
    }

    void shrink()
    {
        if (capacity_ > 1 && curr_size_ <= capacity_ / 4)
        {
            T *temp = new T[capacity_ / 2];
            this->capacity_ /= 2;

            for (size_t i = 0; i < this->curr_size_; i++)
            {
                temp[i] = this->array_[i];
            }

            delete[] this->array_;
            this->array_ = temp;
        }
    }

    // Push item onto the stack
    void push(const T &data) override
    {
        if (curr_size_ >= capacity_)
        {
            resize();
        }

        this->array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override
    {
        if (curr_size_ > 0)
        {
            return this->array_[curr_size_ - 1];
        }
        throw std::runtime_error("Current size is 0");
    }

    T pop() override
    {
        if (curr_size_ > 0)
        {
            T temp = this->array_[curr_size_ - 1];
            --curr_size_;

            shrink();

            return temp;
        }
        throw std::runtime_error("Current size is 0");
    }

    void PrintForward()
    {
        for (size_t i = 0; i < curr_size_; i++)
        {
            std::cout << array_[i] << std::endl;
        }
    }

    void PrintReverse()
    {
        for (size_t i = curr_size_; i > 0; i--)
        {
            std::cout << array_[i - 1] << std::endl;
        }
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T *array_;
    static constexpr size_t scale_factor_ = 2;
};
