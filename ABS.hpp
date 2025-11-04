// #pragma once

// #include <cstddef>
// #include <stdexcept>
// #include "Interfaces.hpp"

// // Technically bad, but size_t isn't likely to conflict with any client code.
// using std::size_t;

// template<typename T>
// class ABS : public StackInterface<T> {
// public:
//     // Big 5 + Parameterized Constructor
//     ABS() {array_ = new T[capacity_];};
//     explicit ABS(const size_t capacity): capacity_(capacity) {array_ = new T[capacity_];};
//     ABS(const ABS& other) {
//         capacity_ = other.capacity_;
//         curr_size_ = other.curr_size_;
//         array_ = new T[capacity_];
//         for (size_t i = 0; i < curr_size_; i++) {
//             array_[i] = other.array_[i];
//         }
//     }
//     ABS& operator=(const ABS& rhs);
//     ABS(ABS&& other) noexcept;
//     ABS& operator=(ABS&& rhs) noexcept;
//     ~ABS() noexcept {delete[] array_;}

//     // Get the number of items in the ABS
//     [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}

//     // Get the max size of the ABS
//     [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}

//     // Return underlying data for the stack
//     [[nodiscard]] T* getData() const noexcept {return array_;}

//     // Push item onto the stack
//     void push(const T& data) override {
//         if (curr_size_ == capacity_) {
//             T stack_array[curr_size_];
//             for (size_t i = 0; i < curr_size_; i++) {
//                 stack_array[i] = array_[i];
//             }
//             delete[] array_;
//             capacity_ *= scale_factor_;
//             array_ = new T[capacity_];
//             for (size_t i = 0; i < curr_size_; i++) {
//                 array_[i] = stack_array[i];
//             }
//         }

//         array_[curr_size_++] = data;
//     }

//     T peek() const override {return array_[curr_size_ - 1];}

//     T pop() override {return array_[--curr_size_];}

// private:
//     size_t capacity_ = 1;
//     size_t curr_size_ = 0;
//     T* array_;
//     static constexpr size_t scale_factor_ = 2;
// };
