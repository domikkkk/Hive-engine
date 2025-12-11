#include <nnue/activations.hpp>


template<class T>
ndarray<T> Activation<T>::operator()(ndarray<T>& input) {
    return this->forward(input);
}


template<class T>
ndarray<T> Activation<T>::forward(ndarray<T>& input) {
    this->last_input = input;
    return function(input);
}


template<class T>
ndarray<T> Activation<T>::backward(const ndarray<T>& output_gradient, const float& learning_rate) {
    ndarray<T> grad = derivative(last_input);
    for (size_t i = 0; i < grad.data.size(); ++i) {
        grad.data[i] *= output_gradient.data[i];
    }
    return grad;
}


template class Activation<float>;
template class Activation<double>;
template class Activation<int>;

template class ReLU<float>;
template class ReLU<double>;
template class ReLU<int>;

template class ClippedReLU<float>;
template class ClippedReLU<double>;
template class ClippedReLU<int>;
