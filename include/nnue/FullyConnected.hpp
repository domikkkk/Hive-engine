#pragma once
#include <nnue/layer.hpp>
#include <nnue/ndarray.hpp>
#include <cstddef>


template <class T>
class FullyConnected : public Layer<T> {
public:
    FullyConnected(const size_t &input, const size_t &output) noexcept:
        input(input),
        output(output),
        weights(input, output),
        bias(input, output) {};

    ndarray<T> operator()(ndarray<T>& input) override;

    ndarray<T> forward(ndarray<T>& input) override;

    ndarray<T> backward(const ndarray<T>& output_gradient, const float& learning_rate) override;

private:
    size_t input, output;
    ndarray<T> weights;
    ndarray<T> bias;
};
