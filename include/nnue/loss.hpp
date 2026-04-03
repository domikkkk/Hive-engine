#ifndef LOSS_HPP
#define LOSS_HPP
#pragma once

#include <nnue/ndarray.hpp>
#include <exceptions.hpp>


template <class T, class ArrayType=narray<T>>
class Loss {
public:
    T operator()(const ArrayType& y_pred, const ArrayType& y_true) { return this->forward(y_pred, y_true); };
    virtual T forward(const ArrayType& y_pred, const ArrayType& y_true) = 0;
    virtual ArrayType backward(const ArrayType& y_pred, const ArrayType& y_true) = 0;
};



template <class T, class ArrayType=narray<T>>
class MSE : public Loss<T, ArrayType> {
public:
    MSE() = default;
    T forward(const ArrayType& y_pred, const ArrayType& y_true) {
        if (y_pred.size() != y_true.size()) {
            throw WrongMatrixSize(y_pred.size(), y_true.size());
        }

        T sum = 0;
        for (size_t i = 0; i < y_pred.size(); ++i) {
            T diff = y_pred[i] - y_true[i];
            sum += diff * diff;
        }
        return sum / static_cast<T>(y_pred.size());
    }
    ArrayType backward(const ArrayType& y_pred, const ArrayType& y_true) {
        if (y_pred.size() != y_true.size())
            throw WrongMatrixSize(y_pred.size(), y_true.size());

        ArrayType grad(y_pred.shape);
        T n = static_cast<T>(y_pred.size());
        for (size_t i = 0; i < y_pred.size(); ++i) {
            grad[i] = 2 * (y_pred[i] - y_true[i]) / n;
        }
        return grad;
    }
};


#endif
