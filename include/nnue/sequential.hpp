#ifndef MODEL_HPP
#define MODEL_HPP
#pragma once

#include <nnue/layer.hpp>
#include <memory>
#include <fstream>


template <class T>
class Sequential {
public:
    using ArrayType = nd2array<T>;

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

    void save_weights(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);

        if (!file)
            throw std::runtime_error("Cannot open file");
        
        size_t count = this->layers.size();
        file.write(reinterpret_cast<const char*>(&count),
            sizeof(size_t));

        for (const auto* layer : this->layers) {
            layer->save(file);
        }
    }


    void load_weights(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);

        if (!file)
            throw std::runtime_error("Cannot open file");

        size_t count;
        file.read(reinterpret_cast<char*>(&count),
                sizeof(size_t));

        if (count != this->layers.size())
            throw std::runtime_error("Layer count mismatch");

        for (auto* layer : this->layers) {
            layer->load(file);
        }
    }


private:
    std::vector<Layer<T>*> layers;
};


#endif
