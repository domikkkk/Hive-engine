#ifndef FULLYCONNECTED_HPP
#define FULLYCONNECTED_HPP

#pragma once
#include <nnue/layer.hpp>
#include <nnue/ndarray.hpp>
#include <cstddef>


template <class T>
class FullyConnected : public Layer<T, nd2array<T>> {
public:
    FullyConnected(const size_t &input, const size_t &output) noexcept:
        input(input),
        output(output),
        weights(input, output),
        bias(1, output) {
            weights.randomize(-0.5f, 0.5f);
            bias.randomize(-0.5f, 0.5f);
        };

    nd2array<T> operator()(const nd2array<T>& input) override;
    nd2array<T> forward(const nd2array<T>& input) override;
    nd2array<T> backward(const nd2array<T>& output_gradient, const float& learning_rate) override;


private:
    size_t input, output;
    nd2array<T> last_input;
    nd2array<T> weights;
    nd2array<T> bias;
};


#endif
