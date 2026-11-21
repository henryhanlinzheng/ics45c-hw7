#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

// Forward declaration for friend functions
template <typename T>
class Array;

template <typename T>
void swap(Array<T>& lhs, Array<T>& rhs) noexcept;

template <typename T>
class Array {
public:
    Array();
    explicit Array(int len);

    Array(const Array& other);
    Array(Array&& other) noexcept;

    friend void swap<>(Array<T>& lhs, Array<T>& rhs) noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    ~Array();

    int length() const;

    T& operator[](int index);
    const T& operator[](int index) const;

    void fill(const T& val);

private:
    int len;
    T* buf;

    bool in_bounds(int index) const;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array);

template <typename T>
std::istream& operator>>(std::istream& in, Array<T>& array);

template <typename T>
Array<T>::Array() : len{0}, buf{nullptr} {
}

template <typename T>
Array<T>::Array(int len) : len{len}, buf{new T[len]} {
}

template <typename T>
Array<T>::Array(const Array& other) : len{other.len}, buf{new T[other.len]} {
    for (int i = 0; i < len; ++i) {
        buf[i] = other.buf[i];
    }
}

template <typename T>
Array<T>::Array(Array&& other) noexcept
    : len{std::exchange(other.len, 0)}, buf{std::exchange(other.buf, nullptr)} {
}

template <typename T>
void swap(Array<T>& lhs, Array<T>& rhs) noexcept {
    std::swap(lhs.len, rhs.len);
    std::swap(lhs.buf, rhs.buf);
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    Array copy{other};
    swap(*this, copy);
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    Array moved{std::move(other)};
    swap(*this, moved);
    return *this;
}

template <typename T>
Array<T>::~Array() {
    delete[] buf;
}

template <typename T>
int Array<T>::length() const {
    return len;
}

template <typename T>
T& Array<T>::operator[](int index) {
    if (!in_bounds(index)) {
        throw "Exception operator[](" + std::to_string(index) + ") Out Of Range";
    }
    return buf[index];
}

template <typename T>
const T& Array<T>::operator[](int index) const {
    if (!in_bounds(index)) {
        throw "Exception operator[](" + std::to_string(index) + ") Out Of Range";
    }
    return buf[index];
}

template <typename T>
void Array<T>::fill(const T& val) {
    for (int i = 0; i < len; ++i) {
        buf[i] = val;
    }
}

template <typename T>
bool Array<T>::in_bounds(int index) const {
    return index >= 0 && index < len;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array) {
    std::stringstream temp;
    // We don't want to set formatting flags globally.
    temp << std::setprecision(2) << std::fixed << std::right;

    for (int i = 0; i < array.length(); ++i) {
        temp << std::setw(8) << array[i];
    }

    out << temp.str();
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Array<T>& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }

    return in;
}

#endif