#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#pragma once

#include <stdexcept>
#include <format>


class InvalidMove : public std::exception {
public:
    explicit InvalidMove(const std::string &mess) {
        this->message = "Invalid move: " + mess;
    }

    const char* what() const noexcept override {
        return this->message.c_str();
    }

private:
    std::string message;
};


class PieceNotExisting : public std::exception {
public:
    explicit PieceNotExisting(const std::string& piece) {
        this->message = "Piece " + piece + " does not exist.";
    }

    const char* what() const noexcept override {
        return this->message.c_str();
    }

private:
    std::string message;
};


class PieceNotOnTheBoard : public std::exception {
public:
    explicit PieceNotOnTheBoard(const std::string& piece) {
        this->message = "Piece " + piece + " is not on the board.";
    }

    const char* what() const noexcept override {
        return this->message.c_str();
    }

private:
    std::string message;
};


class NotOneHive : public std::exception {
public:
    const char* what() const noexcept override {
        return "Board is not connected";
    }
};


class WrongMatrixSize : public std::exception {
public:
    explicit WrongMatrixSize(const size_t &x1, const size_t &y1, const size_t &x2, const size_t &y2) {
        this->message = std::format("Incompatible matrix sizes ({}, {}) with ({}, {})", x1, y1, x2, y2);
    }

    const char* what() const noexcept override {
        return this->message.c_str();
    }

private:
    std::string message;
};


#endif
