#ifndef DECORATORS_HPP
#define DECORATORS_HPP

#include <chrono>
#include <functional>
#include <iostream>
#include <utility>


template <typename Func, typename... Args>
auto time_function(Func &&func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Czas wykonania: " << duration.count() << " s\n";
    return result;
}


#endif
