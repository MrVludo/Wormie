#pragma once
#include "config.hh"

extern int score;
extern int bestScore1;
extern int bestScore2;

enum Direction {UP, DOWN, LEFT, RIGHT, WAIT};

class Snake {
private:
    float speed; // moves in 10 seconds
    Direction direction;
    Direction facing;
    std::vector<std::pair<int,int>> snake;
    int lenght = 1;
public:
    Color headColor = YELLOW;
    Color tailColor[2] = {BLUE, GREEN};
    double prevMoveTime;
    Snake();
    int getLenght();
    float getSpeed();
    Direction getDirection();
    Direction getFacing();
    std::vector<std::pair<int,int>> getSnake();
    void Move(Direction dir);
    std::pair<int,int> nextMove(Direction dir);
    void setDirection(Direction dir);
    void grow(int n = 1);
    void kill();
};

extern Snake snake1;
extern std::pair<int,int> apple;
std::pair<int,int> make_apple();

void SnakeKeyboard();