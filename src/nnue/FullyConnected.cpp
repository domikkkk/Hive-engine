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
nd2array<T> FullyConnected<T>::backward(const nd2array<T>& output_gradient) {
    nd2array<T> input_T = this->last_input._T();
    this->dW = input_T * output_gradient;

    this->db = nd2array<T>(1, output);
    for (size_t j = 0; j < output; ++j)
        this->db(0, j) = output_gradient(0, j);

    nd2array<T> weights_T = weights._T();
    return output_gradient * weights_T;
}


template <class T>
void FullyConnected<T>::step(const float& learning_rate) {
    for (size_t i = 0; i < this->weights.shape[0]; ++i)
        for (size_t j = 0; j < this->weights.shape[1]; ++j)
            this->weights(i,j) -= learning_rate * this->dW(i,j);

    for (size_t j = 0; j < this->bias.shape[1]; ++j)
        this->bias(0,j) -= learning_rate * this->db(0,j);
}


template class FullyConnected<float>;
template class FullyConnected<double>;
template class FullyConnected<int>;
