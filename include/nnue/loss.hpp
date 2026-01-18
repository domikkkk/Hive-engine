#ifndef LOSS_HPP
#define LOSS_HPP
#pragma once

#include <nnue/ndarray.hpp>


template <class T, class ArrayType=narray<T>>
class Loss {
public:
    T operator()(const ArrayType& y_pred, const ArrayType& y_true) { return this->forward(y_pred, y_true); };
    virtual T forward(const ArrayType& y_pred, const ArrayType& y_true) = 0;
    virtual ArrayType backward(const ArrayType& y_pred, const ArrayType& y_true) = 0;

private:

};



template <class T, class ArrayType=narray<T>>
class MSE : public Loss<T, ArrayType> {
public:
    MSE() = default;
    T forward(const ArrayType& y_pred, const ArrayType& y_true) override;
    ArrayType backward(const ArrayType& y_pred, const ArrayType& y_true) override;
};


#endif
