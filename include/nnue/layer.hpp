#pragma once
#include <nnue/ndarray.hpp>


template <class T>
class Layer {
public:
    virtual ~Layer() = default; 
    virtual ndarray<T> operator()(ndarray<T> &input) = 0;
    virtual ndarray<T> forward(ndarray<T> &input) = 0;
    virtual ndarray<T> backward(const ndarray<T> &output_gradient, const float &learning_rate) = 0;
};
