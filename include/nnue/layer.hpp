#ifndef LAYER_HPP
#define LAYER_HPP

#pragma once
#include <nnue/ndarray.hpp>


template <class T>
class Layer {
public:
    using ArrayType = nd2array<T>;

    ~Layer() = default;
    ArrayType operator()(const ArrayType &input) { return this->forward(input); };
    virtual ArrayType forward(const ArrayType &input) = 0;
    virtual ArrayType backward(const ArrayType &output_gradient) = 0;
    virtual void step(const T& learning_rate) = 0;
    virtual void zero_grad() = 0;

    virtual void save(std::ostream&) const {};
    virtual void load(std::istream&) {};
};


#endif