#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "ABS.hpp"

// // Big 5 + Parameterized Constructor
// ABS(const ABS& other);
// ABS& operator=(const ABS& rhs);
// ABS(ABS&& other) noexcept;
// ABS& operator=(ABS&& rhs) noexcept;
template <typename T>
ABS<T>::~ABS() noexcept {
    delete[] array_;
}

// // Get the number of items in the ABS
template <typename T>
[[nodiscard]] size_t ABS<T>::getSize() const noexcept {
    return curr_size_;
}

// // Get the max size of the ABS
// [[nodiscard]] size_t getMaxCapacity() const noexcept;

// // Return underlying data for the stack
template <typename T>
[[nodiscard]] T* ABS<T>::getData() const noexcept {
    return array_;
}

// // Push item onto the stack
template <typename T>
void ABS<T>::push(const T& data) {
    if (curr_size_ == capacity_) {
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

template <typename T>
T ABS<T>::peek() const {
    return array_[curr_size_];
}

template <typename T>
T ABS<T>::pop() {
    T stack_var = array_[curr_size_--];
    return stack_var;
}