#include <nnue/ndarray.hpp>
#include <exceptions.hpp>


template<class T>
T& nd2array<T>::operator()(const size_t &r, const size_t &c) {
    if (r >= this->shape[0] || c >= this->shape[1]){
        throw std::out_of_range("Index out of range");
    }
    return data[r * this->shape[1] + c];
}


template<class T>
const T& nd2array<T>::operator()(const size_t &r, const size_t &c) const {
    if (r >= this->shape[0] || c >= this->shape[1]){
        throw std::out_of_range("Index out of range");
    }
    return data[r * this->shape[1] + c];
}


template<class T>
nd2array<T> nd2array<T>::operator*(const nd2array& array) {
    if (this->shape[1] != array.shape[0]) {
        throw WrongMatrixSize(this->shape[0], this->shape[1], array.shape[0], array.shape[1]);
    }
    nd2array result(this->shape[0], array.shape[1]);
    for (size_t i = 0; i < this->shape[0]; ++i) {
        for (size_t j = 0; j < array.shape[1]; ++j) {
            T sum{};
            for (size_t k = 0; k < this->shape[1]; ++k) {
                sum += (*this)(i, k) * array(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}


template class nd2array<float>;
template class nd2array<int>;
template class nd2array<double>;
