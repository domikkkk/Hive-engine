#ifndef EVALUATIONS_HPP
#define EVALUATIONS_HPP
#pragma once

#include <hive/gamecontroller.hpp>
#include <unordered_map>
#include <nnue/ndarray.hpp>


float heuristic1(Controller &controller);

float heuristic2(Controller &controller);

float heuristic3(Controller &controller);

#ifdef LEARN
extern float total_loss;
extern int counter;
#endif

#ifdef NNUE
float heuristic_nnue(Controller &controller);
#endif

#endif
