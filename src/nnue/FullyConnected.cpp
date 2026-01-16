#include <nnue/FullyConnected.hpp>


template <class T>
nd2array<T> FullyConnected<T>::operator()(const nd2array<T>& input) {
    return this->forward(input);
}


template <class T>
nd2array<T> FullyConnected<T>::forward(const nd2array<T>& input) {
    this->last_input = input; 
    nd2array<T> result = input * weights;
    for (size_t j = 0; j < output; ++j) {
        result(0, j) += bias(0, j);
    }
    return result;
}


template <class T>
nd2array<T> FullyConnected<T>::backward(const nd2array<T>& output_gradient, const float& learning_rate) {
    nd2array<T> input_gradient(weights.shape[0], weights.shape[1]);
    nd2array<T> input_T = this->last_input.transpose();
    nd2array<T> dW = input_T * output_gradient;

    for (size_t i = 0; i < weights.shape[0]; ++i)
        for (size_t j = 0; j < weights.shape[1]; ++j)
            weights(i,j) -= learning_rate * dW(i,j);

    for (size_t j = 0; j < bias.shape[1]; ++j)
        bias(0,j) -= learning_rate * output_gradient(0,j);

    nd2array<T> weights_T = weights.transpose();
    return output_gradient * weights_T;
}


template class FullyConnected<float>;
template class FullyConnected<double>;
template class FullyConnected<int>;
