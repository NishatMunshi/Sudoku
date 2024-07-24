#include "../include/sudoku_bot.hpp"

#include <cassert>
#include <iostream>

void sudoku_bot::get_input() {
    std::cout << "please provide the input board:\n";
    for (std::size_t row = 0; row < BOARD_SIZE; ++row) {
        for (std::size_t col = 0; col < BOARD_SIZE; ++col) {
            size_t dig;
            std::cin >> dig;
            assert(dig < 10 and "digit must be less than 10\n");
            put_digit(row, col, dig);
        }
    }
}

void sudoku_bot::display_output() {
    for (std::size_t row = 0; row < BOARD_SIZE; ++row) {
        if (row and row % 3 == 0) {
            for (std::size_t col = 0; col < BOARD_SIZE; ++col) {
                std::cout << "   -";
            }
            std::cout << '\n';
        }
        for (std::size_t col = 0; col < BOARD_SIZE; ++col) {
            if (col and col % 3 == 0) {
                std::cout << " | ";
            } else {
                std::cout << "   ";
            }
            std::cout << m_board[row][col];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

bool sudoku_bot::solve_input() {
    for (std::size_t row = 0; row < BOARD_SIZE; ++row) {
        for (std::size_t col = 0; col < BOARD_SIZE; ++col) {
            // skip the occupied cells
            if (m_board[row][col] not_eq EMPTY) {
                continue;
            }

            for (std::size_t dig = 1; dig <= BOARD_SIZE; ++dig) {
                // skip the unplacable digits
                if (not digit_possible(row, col, dig)) {
                    continue;
                }

                // now the digit is placable
                auto poss = m_dig_possibility[row][col];  // save the poss list for this cell
                put_digit(row, col, dig);                 // put the probable digit in the board

                // try to solve recursively
                if (solve_input()) {
                    return true;
                }

                // if we could not solve recursively
                withdraw_digit(row, col, dig);       // then restore the board
                m_dig_possibility[row][col] = poss;  // restore the poss list as well
                // retry with the next choice
            }

            // if we could not place any digit that means this path is wrong
            if (m_board[row][col] == EMPTY) {
                return false;
            }
        }
    }
    // if we reached here that means we are done
    return true;
}

std::size_t sudoku_bot::box_index(std::size_t row, std::size_t col) {
    return 3ul * (row / 3u) + (col / 3u);
}

bool sudoku_bot::digit_possible(std::size_t row, std::size_t col, std::size_t dig) {
    return m_row_occupancy[row][dig] == false and
           m_col_occupancy[col][dig] == false and
           m_box_occupancy[box_index(row, col)][dig] == false and
           m_dig_possibility[row][col][dig] == true;
}

void sudoku_bot::put_digit(std::size_t row, std::size_t col, std::size_t dig) {
    m_board[row][col] = dig;
    m_row_occupancy[row][dig] = true;
    m_col_occupancy[col][dig] = true;
    m_box_occupancy[box_index(row, col)][dig] = true;
    m_dig_possibility[row][col].fill(!dig);
}

void sudoku_bot::withdraw_digit(std::size_t row, std::size_t col, std::size_t dig) {
    m_board[row][col] = EMPTY;
    m_row_occupancy[row][dig] = false;
    m_col_occupancy[col][dig] = false;
    m_box_occupancy[box_index(row, col)][dig] = false;
    m_dig_possibility[row][col].fill(dig);
}