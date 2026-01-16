#include <iostream>
#include <nnue/FullyConnected.hpp>
#include <nnue/activations.hpp>
#include <nnue/ndarray.hpp>
#include <nnue/model.hpp>


int main() {
    nd2array<float> array1(1, 8), output;
    array1(0, 0) = 1.0;
    array1(0, 1) = 1.0;
    array1(0, 2) = 0.0;
    array1(0, 3) = 1.0;
    array1(0, 4) = 1.0;
    array1(0, 5) = 0.0;
    array1(0, 6) = 0.0;
    array1(0, 7) = 1.0;
    
    ClippedReLU<float, nd2array<float>> t(1.0), t2(1.0);

    FullyConnected<float> fc(8, 4), fc2(4, 10), fc3(10, 1);
    
    Model<float> model(&fc, &t, &fc2, &t2, &fc3);

    output = model(array1);

    printf("%f\n", output(0, 0));
}
