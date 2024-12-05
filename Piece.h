#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "Position.h"

// Forward declaration of Board to avoid circular dependency
class Board;

class Piece {
public:
    // Constructor
    Piece(const std::string& color, const Position& position);

    // Virtual Destructor
    virtual ~Piece() = default;

    // Getters
    std::string getColor() const;
    Position getPosition() const;

    // Setter
    void setPosition(const Position& position);

    // Pure Virtual Methods
    virtual bool isValidMove(const Position& newPos, const Board& board) const = 0;
    virtual char getSymbol() const = 0;

protected:
    std::string color_;
    Position position_;
};

#endif // PIECE_H
