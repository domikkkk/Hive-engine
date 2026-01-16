#include <iostream>
#include <nnue/FullyConnected.hpp>
#include <nnue/activations.hpp>
#include <nnue/ndarray.hpp>


int main() {
    nd2array<int> array1(3, 2), array2(2, 3), result;
    array1(0, 0) = 2;
    array1(1, 0) = 23;
    array1(2, 0) = 1;
    array1(0, 1) = 1;
    array1(1, 1) = -1;
    array1(2, 1) = 2;

    array2(0, 0) = 2;
    array2(1, 0) = -1;
    
    result = array1 * array2;
    ClippedReLU<int, nd2array<int>> t(3);
    // ReLU<float> t2;
    FullyConnected<int> fc(2, 2);
    array1 = t(array1);
    for (const auto &a: result.data) {
        printf("%d\n", a);
    }

    printf("\n%d\n", array1(1, 0));

    // array.reshape(2, 3);

    // printf("%d\n", array(1, 0));
    // return 0;
}
