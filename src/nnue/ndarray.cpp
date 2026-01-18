#include <nnue/ndarray.hpp>
#include <exceptions.hpp>
#include <random>
#include <ctime>
#include <type_traits>


template<class T>
T& nd2array<T>::operator()(const size_t &r, const size_t &c) {
    if (r >= this->shape[0] || c >= this->shape[1]){
        throw std::out_of_range("Index out of range");
    }
    return this->data[r * this->shape[1] + c];
}


template<class T>
const T& nd2array<T>::operator()(const size_t &r, const size_t &c) const {
    if (r >= this->shape[0] || c >= this->shape[1]){
        throw std::out_of_range("Index out of range");
    }
    return this->data[r * this->shape[1] + c];
}


template<class T>
nd2array<T> nd2array<T>::operator*(const nd2array& array) const {
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


template<class T>
nd2array<T> nd2array<T>::operator*(const T& a) const {
    nd2array<T> result(*this);
    for (size_t i = 0; i < result.data.size(); ++i) {
        result[i] -= a;
    }
    return result;
}


template<class T>
nd2array<T> nd2array<T>::operator/(const T& a) const {
    nd2array<T> result(*this);
    for (size_t i = 0; i < result.data.size(); ++i) {
        result[i] -= a;
    }
    return result;
}


template<class T>
nd2array<T> nd2array<T>::operator+(const T& a) const {
    nd2array<T> result(*this);
    for (size_t i = 0; i < result.data.size(); ++i) {
        result[i] -= a;
    }
    return result;
}


template<class T>
nd2array<T> nd2array<T>::operator-(const T& a) const {
    nd2array<T> result(*this);
    for (size_t i = 0; i < result.data.size(); ++i) {
        result[i] -= a;
    }
    return result;
}


template<class T>
nd2array<T> nd2array<T>::transpose() const {
    nd2array<T> transposed(this->shape[1], this->shape[0]);
    for (size_t i = 0; i < this->shape[0]; ++i) {
        for (size_t j = 0; j < this->shape[1]; ++j) {
            transposed(j, i) = (*this)(i, j);
        }
    }
    return transposed;
}


template<class T>
void nd2array<T>::randomize(const T &min, const T &max) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(min, max);
        for (size_t i = 0; i < this->size(); ++i) this->data[i] = dist(gen);
    } else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist(min, max);
        for (size_t i = 0; i < this->size(); ++i) this->data[i] = dist(gen);
    }
}


template class nd2array<float>;
template class nd2array<int>;
template class nd2array<double>;
