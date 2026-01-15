#ifndef NDARRAY_HPP
#define NDARRAY_HPP

#pragma once
#include <vector>
#include <stdexcept>


template <class T>
struct nd2array {
    size_t shape[2];
    std::vector<T> data;

    nd2array() = default;
    nd2array(const size_t &r, const size_t &c) : shape{r, c}, data(r * c) {}

    T& operator()(const size_t &r, const size_t &c);

    const T& operator()(const size_t &r, const size_t &c) const;

    nd2array operator*(const nd2array& array);
};



template <class T>
struct ndarray {
    std::vector<T> data;
    std::vector<size_t> shape;

    template <class... Args>
    ndarray(Args... dims) : shape{static_cast<size_t>(dims)...} {
        size_t total = 1;
        ((total *= dims), ...);
        data.resize(total);
    }

    template <class... Args>
    T& operator()(Args... idxs) {
        std::vector<size_t> _shape{static_cast<size_t>(idxs)...};
        if (_shape.size() != this->shape.size()) {
            throw std::invalid_argument("Invalid shape");
        }

        size_t idx = 0;
        for (size_t i = 0; i < this->shape.size(); ++i) {
            if (_shape[i] >= this->shape[i]) throw std::invalid_argument("Too many dimensions");
            idx += this->shape[i] * _shape[i];
        }
        return data[idx];
    }

    template <class... Args>
    ndarray& reshape(Args... dims) {
        size_t total = 1;
        for (size_t d : std::initializer_list<size_t>{static_cast<size_t>(dims)...}) {
            total *= d;
        }
        if (total != this->data.size()) throw std::invalid_argument("Wrong shape");
        this->shape = {static_cast<size_t>(dims)...};
        return *this;
    }

    ndarray operator*(const ndarray& array) {

    }
};


#endif
