#ifndef FULLYCONNECTED_HPP
#define FULLYCONNECTED_HPP

#pragma once
#include <nnue/layer.hpp>
#include <nnue/ndarray.hpp>
#include <cstddef>


template <class T>
class FullyConnected : public Layer<T, nd2array<T>> {
public:
    size_t input, output;
    nd2array<T> weights, bias;
    nd2array<T> dW, db;
    nd2array<T> last_input;

    FullyConnected(const size_t &input, const size_t &output) noexcept:
        input(input),
        output(output),
        weights(input, output),
        bias(1, output) {
            weights.randomize();
            bias.randomize();
        };

    nd2array<T> forward(const nd2array<T>& input) override;
    nd2array<T> backward(const nd2array<T>& output_gradient) override;
    void step(const T& learning_rate) override;
    void zero_grad() override;

private:
    
};


#endif
