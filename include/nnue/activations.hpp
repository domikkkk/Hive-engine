#ifndef ACTIVATION_HPP
#define ACTIVATION_HPP

#pragma once
#include <nnue/layer.hpp>
#include <functional>


template<class T>
class Activation : public Layer<T> {
public:
    Activation(
        std::function<ndarray<T>(ndarray<T>&)> func,
        std::function<ndarray<T>(ndarray<T>&)> deriv
    )
        : function(func), derivative(deriv) {}
    
    ndarray<T> operator()(ndarray<T>& input) override;

    ndarray<T> forward(ndarray<T>& input) override;

    ndarray<T> backward(const ndarray<T>& output_gradient, const float& learning_rate) override;

private:
    ndarray<T> last_input;
    std::function<ndarray<T>(ndarray<T>&)> function;
    std::function<ndarray<T>(ndarray<T>&)> derivative;
};



template<class T>
class ReLU : public Activation<T> {
public:
    ReLU()
        : Activation<T>(
            [](ndarray<T>& x) {
                for (size_t i = 0; i < x.data.size(); ++i)
                    x.data[i] = std::max(x.data[i], (T)0);
                return x;
            },
            [](ndarray<T>& x) {
                for (size_t i = 0; i < x.data.size(); ++i)
                    x.data[i] = (x.data[i] > 0) ? 1 : 0;
                return x;
            }
        )
    {}
};

template <class T>
class ClippedReLU : public Activation<T> {
public:
    ClippedReLU(const T& limit)
        : Activation<T>(
            [limit](ndarray<T>& x) {
                for (size_t i = 0; i < x.data.size(); ++i)
                    x.data[i] =  std::min(std::max(x.data[i], (T)0), limit);
                return x;
            },
            [limit](ndarray<T>& x) {
                for (size_t i = 0; i < x.data.size(); ++i)
                    x.data[i] = (x.data[i] > (T)0 && x.data[i] < limit) ? 1 : 0;
                return x;
            }
        )
    {}
};


#endif
