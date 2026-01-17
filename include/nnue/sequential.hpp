#ifndef MODEL_HPP
#define MODEL_HPP
#pragma once

#include <nnue/layer.hpp>
#include <memory>


template <class T, class ArrayType>
class Sequential {
public:
    Sequential() = default;

    template <typename... Layers>
    Sequential(Layers*... args) : layers{args...} {}

    ArrayType operator()(const ArrayType& input);
    ArrayType forward(const ArrayType& input);
    ArrayType backward(const ArrayType &output_gradient, const float &learning_rate);


private:
    std::vector<Layer<T, ArrayType>*> layers;
};


#endif
