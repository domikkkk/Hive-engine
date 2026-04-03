#ifndef FULLYCONNECTED_HPP
#define FULLYCONNECTED_HPP

#pragma once
#include <nnue/layer.hpp>
#include <nnue/ndarray.hpp>
#include <cstddef>


template <class T>
class FullyConnected : public Layer<T, nd2array<T>> {
public:
    size_t input, output;
    nd2array<T> weights, bias;
    nd2array<T> dW, db;
    nd2array<T> last_input;

    FullyConnected(const size_t &input, const size_t &output) noexcept:
        input(input),
        output(output),
        weights(input, output),
        bias(1, output) {
            this->weights.randomize();
            this->bias.randomize();
        };

    nd2array<T> forward(const nd2array<T>& input) override {
        this->last_input = input; 
        nd2array<T> result = input * this->weights;
        for (size_t j = 0; j < this->output; ++j) {
            result(0, j) += this->bias(0, j);
        }
        return result;
    }

    nd2array<T> backward(const nd2array<T>& output_gradient) override {
        nd2array<T> input_T = this->last_input._T();
        this->dW = input_T * output_gradient;

        this->db = nd2array<T>(1, this->output);
        for (size_t j = 0; j < this->output; ++j)
            this->db(0, j) = output_gradient(0, j);

        nd2array<T> weights_T = this->weights._T();
        return output_gradient * weights_T;
    }

    void step(const T& learning_rate) override {
        for (size_t i = 0; i < this->weights.shape[0]; ++i)
            for (size_t j = 0; j < this->weights.shape[1]; ++j)
                this->weights(i,j) -= learning_rate * this->dW(i,j);

        for (size_t j = 0; j < this->bias.shape[1]; ++j)
            this->bias(0,j) -= learning_rate * this->db(0,j);
    }

    void zero_grad() override {
        std::fill(this->dW.data.begin(), this->dW.data.end(), 0);
        std::fill(this->db.data.begin(), this->db.data.end(), 0);
    }

private:
    
};


#endif
