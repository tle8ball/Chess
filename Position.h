#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    // Constructors
    Position();
    Position(int x, int y);

    // Copy Constructor and Assignment Operator
    Position(const Position& other) = default;
    Position& operator=(const Position& other) = default;

    // Move Constructor and Assignment Operator
    Position(Position&& other) = default;
    Position& operator=(Position&& other) = default;

    // Destructor
    ~Position() = default;

    // Getters
    int getX() const;
    int getY() const;

    // Setters
    void setX(int x);
    void setY(int y);

    // Operator Overloads
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

private:
    int x_;
    int y_;
};

#endif // POSITION_H
