#ifndef LAYER_HPP
#define LAYER_HPP

#pragma once
#include <nnue/ndarray.hpp>


template <class T, class ArrayType>
class Layer {
public:
    ~Layer() = default; 
    ArrayType operator()(const ArrayType &input) { return this->forward(input); };
    ArrayType forward(const ArrayType &input);
    ArrayType backward(const ArrayType &output_gradient);
    void step(const T& learning_rate);
    void zero_grad();
};


#endif