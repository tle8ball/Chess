#include "Display.h"
#include <iostream>

Display::Display()
    : RESET("\033[0m"),
      WHITE_PIECE("\033[1;37m"), // Bright White
      BLACK_PIECE("\033[1;30m"), // Gray
      WHITE_SQUARE("\033[47m"),  // White background
      BLACK_SQUARE("\033[40m")   // Black background
{}

void Display::render(const Board& board) const {
    std::cout << "  +------------------------+" << std::endl;
    for (int y = 0; y < 8; ++y) {
        std::cout << 8 - y << " | ";
        for (int x = 0; x < 8; ++x) {
            const Piece* piece = board.getPieceAt(Position(x, y));
            std::string squareColor = getSquareColor(x, y);
            std::string pieceSymbol = getPieceSymbol(piece);
            std::cout << squareColor << pieceSymbol << " " << RESET;
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "  +------------------------+" << std::endl;
    std::cout << "    a b c d e f g h" << std::endl;
}

std::string Display::getPieceSymbol(const Piece* piece) const {
    if (piece) {
        std::string colorCode = (piece->getColor() == "white") ? WHITE_PIECE : BLACK_PIECE;
        char symbol = piece->getSymbol();
        std::string unicodeSymbol;

        switch (symbol) {
            case 'P':
                unicodeSymbol = "♙";
                break;
            case 'p':
                unicodeSymbol = "♟";
                break;
            case 'R':
                unicodeSymbol = "♖";
                break;
            case 'r':
                unicodeSymbol = "♜";
                break;
            case 'N':
                unicodeSymbol = "♘";
                break;
            case 'n':
                unicodeSymbol = "♞";
                break;
            case 'B':
                unicodeSymbol = "♗";
                break;
            case 'b':
                unicodeSymbol = "♝";
                break;
            case 'Q':
                unicodeSymbol = "♕";
                break;
            case 'q':
                unicodeSymbol = "♛";
                break;
            case 'K':
                unicodeSymbol = "♔";
                break;
            case 'k':
                unicodeSymbol = "♚";
                break;
            default:
                unicodeSymbol = " ";
        }
        return colorCode + unicodeSymbol;
    } else {
        return " ";
    }
}


std::string Display::getSquareColor(int x, int y) const {
    // Alternate square colors
    bool isWhiteSquare = (x + y) % 2 == 0;
    return isWhiteSquare ? WHITE_SQUARE : BLACK_SQUARE;
}
