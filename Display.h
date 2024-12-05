#ifndef DISPLAY_H
#define DISPLAY_H

#include "Board.h"
#include <string>

class Display {
public:
    // Constructor
    Display();

    // Destructor
    ~Display() = default;

    // Render the board to the console
    void render(const Board& board) const;

private:
    // ANSI color codes
    const std::string RESET;
    const std::string WHITE_PIECE;
    const std::string BLACK_PIECE;
    const std::string WHITE_SQUARE;
    const std::string BLACK_SQUARE;

    // Helper methods
    std::string getPieceSymbol(const Piece* piece) const;
    std::string getSquareColor(int x, int y) const;
};

#endif // DISPLAY_H
