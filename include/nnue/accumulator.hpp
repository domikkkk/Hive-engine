#ifndef ACCUMULATOR_HPP
#define ACCUMULATOR_HPP
#pragma once

#include <nnue/ndarray.hpp>
#include <hive/namespaces.hpp>


template<class T>
class Accumulator {
public:
    Accumulator() = default;

    Accumulator(Layer<T> *firstlayer) noexcept : first_layer(firstlayer) {};

    nd2array<T>& _input() {return this->input;}

    void change_input(const size_t &pos) {this->input(0, pos) = static_cast<T>(1) - this->input(0, pos);}
    void change_input(const std::string &piece, const int &x, const int &y, const int &z) {
        int insect_type = 0;
        switch(piece[1]) {
            case Insect::bee: insect_type = 0; break;
            case Insect::spider: insect_type = 1; break;
            case Insect::beetle: insect_type = 2; break;
            case Insect::grasshopper: insect_type = 3; break;
            case Insect::ant: insect_type = 4; break;
        }
        const int color_offset = piece[0] == 'w' ? 0 : 1;
        const int layer = (color_offset * 5) + insect_type;
        const int pos = (layer * hive::X * hive::Y) + ((y + hive::Y/2) * hive::X) + x + hive::X/2;

        this->input(0, pos) = static_cast<T>(1) - this->input(0, pos);

        if (insect_type == 2 && z > 0) { // dla beetle
            const int offset = hive::X * hive::Y * 2 * 5;
            char num = piece[2] - '1';
            const int pos2 = offset + (8 * color_offset) + 4 * num + (z-1);
            this->input(0, pos2) = static_cast<T>(1) - this->input(0, pos2);
        }
    }


private:
    Layer<T> *first_layer;
    nd2array<T> input;
};


#endif
