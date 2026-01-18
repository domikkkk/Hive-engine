#include <nnue/activations.hpp>


template<class T, class ArrayType>
ArrayType Activation<T, ArrayType>::forward(const ArrayType& input) {
    this->last_input = input;
    return function(input);
}


template<class T, class ArrayType>
ArrayType Activation<T, ArrayType>::backward(
    const ArrayType& output_gradient
) {
    ArrayType grad = derivative(this->last_input);

    for (size_t i = 0; i < grad.size(); ++i)
        grad[i] *= output_gradient[i];

    return grad;
}


template class Activation<float, nd2array<float>>;
template class Activation<double, nd2array<double>>;
template class Activation<int, nd2array<int>>;

template class ReLU<float, nd2array<float>>;
template class ReLU<double, nd2array<double>>;
template class ReLU<int, nd2array<int>>;

template class ClippedReLU<float, nd2array<float>>;
template class ClippedReLU<double, nd2array<double>>;
template class ClippedReLU<int, nd2array<int>>;
