#include <nnue/FullyConnected.hpp>


template <class T>
ndarray<T> FullyConnected<T>::operator()(ndarray<T>& input) {
    return this->forward(input);
}


template <class T>
ndarray<T> FullyConnected<T>::forward(ndarray<T>& input) {
    return input;
}


template <class T>
ndarray<T> FullyConnected<T>::backward(const ndarray<T>& output_gradient, const float& learning_rate) {
    return output_gradient;
}


template class FullyConnected<float>;
template class FullyConnected<double>;
template class FullyConnected<int>;
