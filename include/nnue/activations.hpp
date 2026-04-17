#ifndef ACTIVATION_HPP
#define ACTIVATION_HPP

#pragma once
#include <nnue/layer.hpp>
#include <functional>


template<class T>
class Activation : public Layer<T> {
public:
    using ArrayType = nd2array<T>;
    using Func = std::function<ArrayType(const ArrayType&)>;

    Activation(Func func, Func deriv)
        : function(func), derivative(deriv) {}

    ArrayType forward(const ArrayType& input) {
        this->last_input = input;
        return this->function(input);
    }
    ArrayType backward(const ArrayType& output_gradient) {
        ArrayType grad = this->derivative(this->last_input);

        for (size_t i = 0; i < grad.size(); ++i)
            grad[i] *= output_gradient[i];

        return grad;
    }
    void step(const T& ) {};
    void zero_grad() {};

private:
    ArrayType last_input;
    Func function;
    Func derivative;
};


template<class T>
class ReLU : public Activation<T> {
public:
    using ArrayType = nd2array<T>;
    ReLU()
        : Activation<T>(
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


template<class T>
class ClippedReLU : public Activation<T> {
public:
    using ArrayType = nd2array<T>;
    ClippedReLU(const T& limit)
        : Activation<T>(
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
