#include <iostream>
#include <nnue/FullyConnected.hpp>
#include <nnue/activations.hpp>
#include <nnue/ndarray.hpp>


int main() {
    ndarray<int> array(3, 2, 1);
    array(1, 0, 0) = 23;
    array(0, 0, 0) = 2;

    ClippedReLU<int> t(3);
    // ReLU<float> t2;
    FullyConnected<int> fc(2, 2);
    array.reshape(2, 3);
    array = t(array);
    for (const auto &a: array.data) {
        printf("%d\n", a);
    }

    // printf("%d\n", array(1, 0));

    // array.reshape(2, 3);

    // printf("%d\n", array(1, 0));
    // return 0;
}
