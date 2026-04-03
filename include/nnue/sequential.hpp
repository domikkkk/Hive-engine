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

    ArrayType operator()(const ArrayType& input) { return this->forward(input); };
    ArrayType forward(const ArrayType& input) {
        ArrayType output = input;
        for (auto& layer : this->layers) {
            output = layer->forward(output);
        }
        return output;
    }

    ArrayType backward(const ArrayType &output_gradient, const T& learning_rate) {
        ArrayType grad = output_gradient;

        for (auto it = this->layers.rbegin(); it != this->layers.rend(); ++it) {
            grad = (*it)->backward(grad);
            (*it)->step(learning_rate);
            (*it)->zero_grad();
        }

        return grad;
    }

    void step(const float&) {};
    void zero_grad() {};


private:
    std::vector<Layer<T, ArrayType>*> layers;
};


#endif
