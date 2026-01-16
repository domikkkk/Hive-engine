#ifndef NDARRAY_HPP
#define NDARRAY_HPP

#pragma once
#include <vector>
#include <stdexcept>


template<class T>
struct narray {
    virtual ~narray() = default;

    virtual size_t size() const = 0;
    virtual T& operator[](size_t i) = 0;
    virtual const T& operator[](size_t i) const = 0;
    
    virtual void randomize(const T &min = T(-1), const T &max = T(1)) = 0;
};


template <class T>
struct ndarray : public narray<T> {
    std::vector<size_t> shape;
    std::vector<T> data;

    size_t size() const override { return data.size(); }
    T& operator[](size_t i) override { return data[i]; }
    const T& operator[](size_t i) const override { return data[i]; }

    ndarray() = default;

    template <class... Args>
    ndarray(Args... dims) : shape{static_cast<size_t>(dims)...} {
        size_t total = 1;
        ((total *= dims), ...);
        data.resize(total);
    }

    template <class... Args>
    T& operator()(Args... idxs) {
        std::vector<size_t> _idxs{static_cast<size_t>(idxs)...};
        if (_idxs.size() != shape.size()) {
            throw std::invalid_argument("Invalid number of indices");
        }

        size_t idx = 0;
        size_t stride = 1;

        // liczymy indeks liniowy w row-major order
        for (int i = shape.size(); i > 0; --i) {
            if (_idxs[i] >= shape[i]) throw std::out_of_range("Index out of bounds");
            idx += _idxs[i] * stride;
            stride *= shape[i];
        }

        return data[idx];
    }

    template <class... Args>
    const T& operator()(Args... idxs) const {
        std::vector<size_t> _idxs{static_cast<size_t>(idxs)...};
        if (_idxs.size() != shape.size()) {
            throw std::invalid_argument("Invalid number of indices");
        }

        size_t idx = 0;
        size_t stride = 1;

        for (int i = shape.size(); i > 0; --i) {
            if (_idxs[i] >= shape[i]) throw std::out_of_range("Index out of bounds");
            idx += _idxs[i] * stride;
            stride *= shape[i];
        }

        return data[idx];
    }

    template <class... Args>
    ndarray& reshape(Args... dims) {
        size_t total = 1;
        for (size_t d : {static_cast<size_t>(dims)...}) total *= d;
        if (total != data.size()) throw std::invalid_argument("Wrong total size for reshape");
        shape = {static_cast<size_t>(dims)...};
        return *this;
    }

    void randomize(const T &min = T(-1), const T &max = T(1)) override;
};


template <class T>
struct nd2array : public narray<T> {
    size_t shape[2];
    std::vector<T> data;

    size_t size() const override { return data.size(); }
    T& operator[](size_t i) override { return data[i]; }
    const T& operator[](size_t i) const override { return data[i]; }

    nd2array() = default;
    nd2array(const size_t &r, const size_t &c) : shape{r, c}, data(r * c) {}

    T& operator()(const size_t &r, const size_t &c);
    const T& operator()(const size_t &r, const size_t &c) const;

    nd2array operator*(const nd2array& array) const;
    nd2array transpose() const;

    void randomize(const T &min = T(-1), const T &max = T(1)) override;
};


#endif
