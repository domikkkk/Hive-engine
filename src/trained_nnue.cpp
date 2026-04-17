#include <nnue.h>
#include <Hive.h>


#define INPUT hive::X * hive::Y * 2 * 5 + 16


int main() {

    FullyConnected<float> fc1(INPUT, 8), fc2(8, 8), fc3(8, 1);
    ClippedReLU<float> rl1(16.0f), rl2(255.0f);
    Sequential<float> model(&fc1, &rl1, &fc2, &rl2, &fc3);

    model.load_weights("model1.nnue");

    nd2array<float> input(1, INPUT);

    auto output = model(input);

    printf("%f\n", output(0, 0));
}
