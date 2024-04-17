#ifndef BOARD_HPP
#define BOARD_HPP
#pragma once
#include <vector>
#include <memory>
#include <hive/pieces.hpp>


namespace hive {
    class Board {
    public:
        Board();
        ~Board() = default;
    private:
        std::vector<std::unique_ptr<hive::Piece>> pieces;
    };
}

#endif
