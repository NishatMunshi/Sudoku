#include "../include/sudoku_bot.hpp"

int main() {
    sudoku_bot bot;
    bot.get_input();
    bot.solve_input();
    bot.display_output();
    return 0;
}