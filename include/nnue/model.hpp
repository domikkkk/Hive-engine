#ifndef MODEL_HPP
#define MODEL_HPP
#pragma once

#include <nnue/layer.hpp>
#include <memory>


template <class T>
class Model {
public:
    Model() = default;

    template <typename... Layers>
    Model(Layers*... args) : layers{args...} {}

    nd2array<T> operator()(const nd2array<T>& input) {
        return this->forward(input);
    };

    nd2array<T> forward(const nd2array<T>& input) {
        nd2array<T> output = input;
        for (auto& layer : layers) {
            output = layer->forward(output);
        }
        return output;
    }

private:
    // std::vector<std::unique_ptr<Layer<T, nd2array<T>>>> layers;
    std::vector<Layer<T, nd2array<T>>*> layers;
};


#endif
