#include <nnue/ndarray.hpp>
#include <exceptions.hpp>
#include <random>
#include <ctime>
#include <unordered_map>


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
        result[i] *= a;
    }
    return result;
}


template<class T>
nd2array<T> nd2array<T>::operator/(const T& a) const {
    nd2array<T> result(*this);
    for (size_t i = 0; i < result.data.size(); ++i) {
        result[i] /= a;
    }
    return result;
}


template<class T>
nd2array<T> nd2array<T>::operator+(const T& a) const {
    nd2array<T> result(*this);
    for (size_t i = 0; i < result.data.size(); ++i) {
        result[i] += a;
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


int get_index_for_input(const std::pair<std::string, Coords> &piece) {
    int insect_type = 0;
    switch(piece.first[1]) {
        case 'Q': insect_type = 0; break;
        case 'S': insect_type = 1; break;
        case 'B': insect_type = 2; break;
        case 'G': insect_type = 3; break;
        case 'A': insect_type = 4; break;
    }
    const int color_offset = piece.first[0] == 'w' ? 0 : 1;
    const int layer = (color_offset * 5) + insect_type;
    return (layer * hive::X * hive::Y) + ((piece.second.y + hive::Y/2) * hive::X) + piece.second.x + hive::X/2;
}


template <class T>
void set_input(nd2array<T> *input, const std::unordered_map<std::string, Coords> *insects) {
    for (const auto &p : insects) {
        int idx = get_index_for_input(p);
        (*input)(0, idx) = static_cast<T>(1);
    }
}



template struct nd2array<float>;
template struct nd2array<int>;
template struct nd2array<double>;
