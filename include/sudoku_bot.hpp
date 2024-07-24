#pragma once

#include <array>

#define BOARD_SIZE 9ul
#define EMPTY 0ul

class sudoku_bot {
   public:
    void get_input();
    bool solve_input();
    void display_output();

   private:
    std::array<std::array<std::size_t, BOARD_SIZE>, BOARD_SIZE> m_board = {EMPTY};
    std::array<std::array<bool, BOARD_SIZE + 1>, BOARD_SIZE> m_row_occupancy = {false};
    std::array<std::array<bool, BOARD_SIZE + 1>, BOARD_SIZE> m_col_occupancy = {false};
    std::array<std::array<bool, BOARD_SIZE + 1>, BOARD_SIZE> m_box_occupancy = {false};
    std::array<std::array<std::array<bool, BOARD_SIZE + 1>, BOARD_SIZE>, BOARD_SIZE> m_dig_possibility = {true};

   private:
    std::size_t box_index(std::size_t row, std::size_t col);
    bool digit_possible(std::size_t row, std::size_t col, std::size_t dig);
    void put_digit(std::size_t row, std::size_t col, std::size_t dig);
    void withdraw_digit(std::size_t row, std::size_t col, std::size_t dig);
};
