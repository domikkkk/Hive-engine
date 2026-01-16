#ifndef LAYER_HPP
#define LAYER_HPP

#pragma once
#include <nnue/ndarray.hpp>


template <class T, class ArrayType>
class Layer {
public:
    virtual ~Layer() = default; 
    virtual ArrayType operator()(const ArrayType &input) = 0;
    virtual ArrayType forward(const ArrayType &input) = 0;
    virtual ArrayType backward(const ArrayType &output_gradient, const float &learning_rate) = 0;
};


#endif