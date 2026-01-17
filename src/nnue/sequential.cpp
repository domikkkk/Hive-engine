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


template class Sequential<float, nd2array<float>>;
template class Sequential<double, nd2array<double>>;
template class Sequential<int, nd2array<int>>;
