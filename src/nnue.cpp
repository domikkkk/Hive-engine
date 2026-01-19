#include <iostream>
#include <nnue/FullyConnected.hpp>
#include <nnue/activations.hpp>
#include <nnue/ndarray.hpp>
#include <nnue/sequential.hpp>
#include <nnue/loss.hpp>


int main() {
    // --- przygotowanie danych ---
    const size_t input_size = 8;
    const size_t n_samples = 256;

    std::vector<nd2array<float>> X;
    std::vector<nd2array<float>> Y;

    for (int i = 0; i < 256; ++i) {
        nd2array<float> x(1, input_size);
        nd2array<float> y(1, 1);
        for (size_t b = 0; b < input_size; ++b) {
            x(0, b) = (i >> b) & 1;  // rozbicie liczby i na bity
        }
        y(0, 0) = static_cast<float>(i); // target to liczba dziesiętna
        X.push_back(x);
        Y.push_back(y);
    }

    // --- stworzenie sieci ---
    FullyConnected<float> fc1(input_size, 10);
    FullyConnected<float> fc2(8, 8);
    FullyConnected<float> fc3(10, 1);

    ReLU<float, nd2array<float>> relu1;
    ClippedReLU<float, nd2array<float>> relu2(16.0);

    Sequential<float, nd2array<float>> model(
        &fc1,
        // &relu1,
        // &fc2,
        &relu2,
        &fc3
    );

    MSE<float, nd2array<float>> loss_fn;

    float lr = 0.001;
    const int epochs = 100;

    for (int ep = 0; ep < epochs; ++ep) {
        float epoch_loss = 0;

        for (size_t i = 0; i < n_samples; ++i) {
            auto out = model(X[i]);
            auto grad = loss_fn.backward(out, Y[i]);

            model.backward(grad, lr);

            float sample_loss = loss_fn(out, Y[i]);
            epoch_loss += sample_loss;
        }
        if (ep >= 85) lr = 0.0001;

        std::cout << "Epoch " << ep << ", loss: " << epoch_loss / n_samples << "\n";
    }

    // --- test przykładowy ---
    for (size_t i = 0; i < X.size(); ++i) {
        auto out = model(X[i]);
        std::cout << "Liczba: " << Y[i](0, 0) << ", Predykcja: " << out(0, 0) << '\n';
    }
    return 0;
}
