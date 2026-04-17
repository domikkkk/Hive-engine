#ifndef NDARRAY_HPP
#define NDARRAY_HPP

#pragma once
#include <vector>
#include <stdexcept>
#include <random>
#include <ctime>
#include <exceptions.hpp>
#include <iostream>


template<class T>
struct narray {
    virtual ~narray() = default;
    virtual size_t size() const = 0;
    virtual T& operator[](size_t i) = 0;
    virtual const T& operator[](size_t i) const = 0;
    
    virtual void randomize(const T &min = T(-1), const T &max = T(1)) = 0;

    virtual void save(std::ostream& os) const = 0;
    virtual void load(std::istream& is) = 0;
};


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

    void randomize(const T &min = T(-1), const T &max = T(1)) override {
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


    void save(std::ostream& os) const override {
        size_t dims = 2;
        // os.write(reinterpret_cast<const char*>(&dims), sizeof(size_t));

        os.write(reinterpret_cast<const char*>(this->shape.data()),
             dims * sizeof(size_t));
            
        size_t size = this->data.size();
        os.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

        os.write(reinterpret_cast<const char*>(this->data.data()),
             size * sizeof(T));
    }


    void load(std::istream& is) {
        size_t dims = 2;
        // is.read(reinterpret_cast<char*>(&dims), sizeof(size_t));

        this->shape.resize(dims);
        is.read(reinterpret_cast<char*>(this->shape.data()),
                dims * sizeof(size_t));

        size_t size;
        is.read(reinterpret_cast<char*>(&size), sizeof(size_t));

        this->data.resize(size);
        is.read(reinterpret_cast<char*>(this->data.data()),
                size * sizeof(T));
    }
};


#endif
