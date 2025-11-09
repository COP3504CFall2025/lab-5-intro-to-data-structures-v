#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T>
class ABQ : public QueueInterface<T>
{

    size_t capacity_;
    size_t curr_size_;
    T *array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ()
    {
        this->capacity_ = 1;
        this->curr_size_ = 0;
        this->array_ = new T[this->capacity_];
    }

    explicit ABQ(const size_t capacity)
    {
        this->capacity_ = capacity;
        this->curr_size_ = 0;
        this->array_ = new T[this->capacity_];
    }

    ABQ(const ABQ &other)
    {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = new T[this->capacity_];

        for (size_t i = 0; i < this->curr_size_; i++)
        {
            this->array_[i] = other.array_[i];
        }
    }

    ABQ &operator=(const ABQ &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        T *temp = new T[rhs.capacity_];
        delete[] this->array_;

        this->array_ = temp;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;

        for (size_t i = 0; i < curr_size_; i++)
        {
            this->array_[i] = rhs.array_[i];
        }

        return *this;
    }

    ABQ(ABQ &&other) noexcept
    {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }

    ABQ &operator=(ABQ &&rhs) noexcept
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

    ~ABQ() noexcept
    {
        delete[] this->array_;
        this->array_ = nullptr;
        this->capacity_ = 0;
        this->curr_size_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override { return this->curr_size_; }
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return this->capacity_; }
    [[nodiscard]] T *getData() const noexcept { return this->array_; }

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

    // Insertion
    void enqueue(const T &data) override
    {
        if (curr_size_ >= capacity_)
        {
            resize();
        }

        this->array_[curr_size_] = data;
        ++curr_size_;
    }

    // Access
    T peek() const override
    {
        if (curr_size_ > 0)
        {
            return this->array_[0];
        }
        throw std::runtime_error("Current size is 0");
    }

    // Deletion
    T dequeue() override
    {
        if (curr_size_ > 0)
        {
            T temp = this->array_[0];
            for (size_t i = 1; i < curr_size_; i++)
            {
                this->array_[i - 1] = this->array_[i];
            }
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
};
