#ifndef EVALUATIONS_HPP
#define EVALUATIONS_HPP
#pragma once

#include <hive/gamecontroller.hpp>
#include <unordered_map>
#include <nnue/ndarray.hpp>


float heuristic1(Controller &controller);

float heuristic2(Controller &controller);

float heuristic3(Controller &controller);

float learn_nnue(Controller &controller);


int get_index_for_input(const std::pair<std::string, Coords> &piece);

template <class T>
void set_input(nd2array<T> *input, const std::unordered_map<std::string, Coords> *insects);


#endif
