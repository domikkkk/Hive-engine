#ifndef ACTIVATION_HPP
#define ACTIVATION_HPP

#pragma once
#include <nnue/layer.hpp>
#include <functional>


template<class T, class ArrayType>
class Activation : public Layer<T, ArrayType> {
public:
    using Func = std::function<ArrayType(const ArrayType&)>;

    Activation(Func func, Func deriv)
        : function(func), derivative(deriv) {}

    ArrayType operator()(const ArrayType& input) override;
    ArrayType forward(const ArrayType& input) override;
    ArrayType backward(const ArrayType& output_gradient) override;
    void step(const float& ) override {};

private:
    ArrayType last_input;
    Func function;
    Func derivative;
};


template<class T, class ArrayType>
class ReLU : public Activation<T, ArrayType> {
public:
    ReLU()
        : Activation<T, ArrayType>(
            [](const ArrayType& x) {
                ArrayType y = x;
                for (size_t i = 0; i < y.size(); ++i)
                    y[i] = std::max(y[i], (T)0);
                return y;
            },
            [](const ArrayType& x) {
                ArrayType y = x;
                for (size_t i = 0; i < y.size(); ++i)
                    y[i] = (y[i] > 0) ? (T)1 : (T)0;
                return y;
            }
        ) {}
};


template<class T, class ArrayType>
class ClippedReLU : public Activation<T, ArrayType> {
public:
    ClippedReLU(const T& limit)
        : Activation<T, ArrayType>(
            [limit](const ArrayType& x) {
                ArrayType y = x;
                for (size_t i = 0; i < y.size(); ++i)
                    y[i] = std::min(std::max(y[i], (T)0), limit);
                return y;
            },
            [limit](const ArrayType& x) {
                ArrayType y = x;
                for (size_t i = 0; i < y.size(); ++i)
                    y[i] = (y[i] > (T)0 && y[i] < limit) ? (T)1 : (T)0;
                return y;
            }
        ) {}
};


#endif
