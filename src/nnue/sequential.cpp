#include <nnue/sequential.hpp>


template <class T, class ArrayType>
ArrayType Sequential<T, ArrayType>::operator()(const ArrayType& input) {
    return this->forward(input);
}


template <class T, class ArrayType>
ArrayType Sequential<T, ArrayType>::forward(const ArrayType& input) {
    ArrayType output = input;
    for (auto& layer : this->layers) {
        output = layer->forward(output);
    }
    return output;
}


template <class T, class ArrayType>
ArrayType Sequential<T, ArrayType>::backward(const ArrayType& output_gradient, const T& learning_rate) {
    ArrayType grad = output_gradient;

    for (auto it = this->layers.rbegin(); it != this->layers.rend(); ++it) {
        grad = (*it)->backward(grad);
        (*it)->step(learning_rate);
        (*it)->zero_grad();
    }

    return grad;
}


template class Sequential<float, nd2array<float>>;
template class Sequential<double, nd2array<double>>;
template class Sequential<int, nd2array<int>>;
