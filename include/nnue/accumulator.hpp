#ifndef ACCUMULATOR_HPP
#define ACCUMULATOR_HPP
#pragma once

#include <nnue/ndarray.hpp>


template<class T>
class Accumulator {
public:
    nd2array<T> &_input() {
        return this->input;
    }


private:
    nd2array<T> input;
};


#endif
