#ifndef NDARRAY_HPP
#define NDARRAY_HPP

#pragma once
#include <vector>
#include <stdexcept>
#include <random>
#include <ctime>
#include <exceptions.hpp>


template<class T>
struct narray {
    virtual ~narray() = default;
    virtual size_t size() const = 0;
    virtual T& operator[](size_t i) = 0;
    virtual const T& operator[](size_t i) const = 0;
    
    virtual void randomize(const T &min = T(-1), const T &max = T(1)) = 0;
};


// template <class T>
// struct ndarray : public narray<T> {
//     std::vector<size_t> shape;
//     std::vector<T> data;

//     size_t size() const override { return data.size(); }
//     T& operator[](size_t i) override { return data[i]; }
//     const T& operator[](size_t i) const override { return data[i]; }

//     ndarray() = default;

//     template <class... Args>
//     ndarray(Args... dims) : shape{static_cast<size_t>(dims)...} {
//         size_t total = 1;
//         ((total *= dims), ...);
//         this->data.resize(total);
//     }

//     explicit ndarray(const std::vector<size_t>& shape_) : shape(shape_), data(1) {
//         size_t total = 1;
//         for (auto dim : this->shape) total *= dim;
//         this->data.resize(total);
//     }

//     template <class... Args>
//     T& operator()(Args... idxs) {
//         std::vector<size_t> _idxs{static_cast<size_t>(idxs)...};
//         if (_idxs.size() != shape.size()) {
//             throw std::invalid_argument("Invalid number of indices");
//         }

//         size_t idx = 0;
//         size_t stride = 1;

//         // liczymy indeks liniowy w row-major order
//         for (int i = shape.size(); i > 0; --i) {
//             if (_idxs[i] >= shape[i]) throw std::out_of_range("Index out of bounds");
//             idx += _idxs[i] * stride;
//             stride *= shape[i];
//         }

//         return data[idx];
//     }

//     template <class... Args>
//     const T& operator()(Args... idxs) const {
//         std::vector<size_t> _idxs{static_cast<size_t>(idxs)...};
//         if (_idxs.size() != shape.size()) {
//             throw std::invalid_argument("Invalid number of indices");
//         }

//         size_t idx = 0;
//         size_t stride = 1;

//         for (int i = shape.size(); i > 0; --i) {
//             if (_idxs[i] >= shape[i]) throw std::out_of_range("Index out of bounds");
//             idx += _idxs[i] * stride;
//             stride *= shape[i];
//         }

//         return data[idx];
//     }

//     template <class... Args>
//     ndarray& reshape(Args... dims) {
//         size_t total = 1;
//         for (size_t d : {static_cast<size_t>(dims)...}) total *= d;
//         if (total != data.size()) throw std::invalid_argument("Wrong total size for reshape");
//         shape = {static_cast<size_t>(dims)...};
//         return *this;
//     }

//     ndarray operator*(const T& a) const;
//     ndarray operator/(const T& a) const;
//     ndarray operator+(const T& a) const;
//     ndarray operator-(const T& a) const;

//     void randomize(const T &min = T(-1), const T &max = T(1)) override;
// };


template <class T>
struct nd2array : public narray<T> {
    std::vector<size_t> shape;
    std::vector<T> data;

    size_t size() const { return this->data.size(); }
    T& operator[](size_t i) { return this->data[i]; }
    const T& operator[](size_t i) const { return this->data[i]; }

    nd2array() = default;
    nd2array(const size_t &r, const size_t &c) : shape{r, c}, data(r * c) {}
    explicit nd2array(const std::vector<size_t>& shape_) : shape(shape_), data(1) {
        if (shape_.size() != 2) throw std::invalid_argument("To many dim");
        size_t total = 1;
        for (const auto& dim : this->shape) total *= dim;
        this->data.resize(total);
    }

    // nd2array& operator=(const nd2array& other) {
    //     if (this != &other) {
    //         shape = other.shape;
    //         data = other.data; // <- std::vector robi deep copy, więc ok
    //     }
    //     return *this;
    // }

    T& operator()(const size_t &r, const size_t &c) {
        if (r >= this->shape[0] || c >= this->shape[1]){
            throw std::out_of_range("Index out of range");
        }
        return this->data[r * this->shape[1] + c];
    }

    const T& operator()(const size_t &r, const size_t &c) const {
        if (r >= this->shape[0] || c >= this->shape[1]){
            throw std::out_of_range("Index out of range");
        }
        return this->data[r * this->shape[1] + c];
    }

    nd2array operator*(const T& a) const {
        nd2array<T> result(*this);
        for (size_t i = 0; i < result.data.size(); ++i) {
            result[i] *= a;
        }
        return result;
    }
    nd2array operator/(const T& a) const {
        nd2array<T> result(*this);
        for (size_t i = 0; i < result.data.size(); ++i) {
            result[i] /= a;
        }
        return result;
    }
    nd2array operator+(const T& a) const {
        nd2array<T> result(*this);
        for (size_t i = 0; i < result.data.size(); ++i) {
            result[i] += a;
        }
        return result;
    }
    nd2array operator-(const T& a) const {
        nd2array<T> result(*this);
        for (size_t i = 0; i < result.data.size(); ++i) {
            result[i] -= a;
        }
        return result;
    }

    // nd2array& operator=(const nd2array& array);

    nd2array operator*(const nd2array& array) const {
        if (this->shape[1] != array.shape[0]) {
            throw WrongMatrixSize(this->shape[0], this->shape[1], array.shape[0], array.shape[1]);
        }
        nd2array result(this->shape[0], array.shape[1]);
        for (size_t i = 0; i < this->shape[0]; ++i) {
            for (size_t j = 0; j < array.shape[1]; ++j) {
                T sum{};
                for (size_t k = 0; k < this->shape[1]; ++k) {
                    sum += (*this)(i, k) * array(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }
    nd2array transpose() const {
        nd2array<T> transposed(this->shape[1], this->shape[0]);
        for (size_t i = 0; i < this->shape[0]; ++i) {
            for (size_t j = 0; j < this->shape[1]; ++j) {
                transposed(j, i) = (*this)(i, j);
            }
        }
        return transposed;
    }
    nd2array _T() const { return this->transpose(); };

    void randomize(const T &min = T(-1), const T &max = T(1)) {
        std::random_device rd;
        std::mt19937 gen(rd());

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(min, max);
            for (size_t i = 0; i < this->size(); ++i) this->data[i] = dist(gen);
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(min, max);
            for (size_t i = 0; i < this->size(); ++i) this->data[i] = dist(gen);
        }
    }
};


#endif
