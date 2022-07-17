#include <windows.h>

#include <iostream>
#include <string>

#include "display.cpp"
#include "snake_game.cpp"

int main() {
    clear_screen();

    setCursorPosition(10, 5);
    std::cout << "CHEESE";
    setCursorPosition(10, 5);
    std::cout << 'W';
    setCursorPosition(10, 9);
    std::cout << 'Z';
    setCursorPosition(10, 5);
    std::cout << "     ";  // Overwrite characters with spaces to "erase" them
    std::cout.flush();
}