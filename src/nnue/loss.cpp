#include <nnue/loss.hpp>
#include <exceptions.hpp>


template <class T, class ArrayType>
T MSE<T, ArrayType>::forward(const ArrayType& y_pred, const ArrayType& y_true) {
    if (y_pred.size() != y_true.size()) {
        throw WrongMatrixSize(y_pred.size(), y_true.size());
    }

    T sum = 0;
    for (size_t i = 0; i < y_pred.size(); ++i) {
        T diff = y_pred[i] - y_true[i];
        sum += diff * diff;
    }
    return sum / static_cast<T>(y_pred.size());
}


template <class T, class ArrayType>
ArrayType MSE<T, ArrayType>::backward(const ArrayType& y_pred, const ArrayType& y_true) {
    if (y_pred.size() != y_true.size())
        throw WrongMatrixSize(y_pred.size(), y_true.size());

    ArrayType grad(y_pred.shape);
    T n = static_cast<T>(y_pred.size());
    for (size_t i = 0; i < y_pred.size(); ++i) {
        grad[i] = 2 * (y_pred[i] - y_true[i]) / n;
    }
    return grad;
}


template class MSE<float, nd2array<float>>;
template class MSE<double, nd2array<double>>;
template class MSE<int, nd2array<int>>;
