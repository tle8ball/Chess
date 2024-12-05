#include "InputHandler.h"
#include <iostream>
#include <cctype>

std::string InputHandler::getPlayerInput() const {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

bool InputHandler::parseInput(const std::string& input, Position& from, Position& to) const {
    if (input.length() != 4) {
        return false;
    }

    std::string fromStr = input.substr(0, 2);
    std::string toStr = input.substr(2, 2);

    if (!notationToPosition(fromStr, from) || !notationToPosition(toStr, to)) {
        return false;
    }

    return true;
}

bool InputHandler::notationToPosition(const std::string& notation, Position& position) const {
    if (notation.length() != 2) {
        return false;
    }

    char file = std::tolower(notation[0]);
    char rank = notation[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return false;
    }

    int x = file - 'a';
    int y = 8 - (rank - '0'); // Convert rank to 0-based index (top to bottom)

    position.setX(x);
    position.setY(y);

    return true;
}
