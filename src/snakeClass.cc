#include "snake.hh"

Snake::Snake() {
    prevMoveTime = GetTime();
    speed = 40; // moves in 10 seconds
    snake.push_back({gridWidth/2-1, gridHeight/2});
    direction = WAIT;
    facing = WAIT;
    isAlive = true;
}

int Snake::getLenght() {
    return lenght;
}

float Snake::getSpeed() {
    return speed;
}

std::vector<std::pair<int,int>> Snake::getSnake() {
    return snake;
}

Direction Snake::getDirection() {
    return direction; 
}

Direction Snake::getFacing() {
    return facing;
}

void Snake::setDirection(Direction dir) {
    direction = dir;
}

void Snake::grow(int n) {
    lenght += n;
}

void Snake::Move(Direction dir) {
    snake.push_back(nextMove(dir));
    prevMoveTime = GetTime();
    facing = dir;
}

std::pair<int,int> Snake::nextMove(Direction dir) {
    auto head = snake.back();
    switch (dir) {
        case UP:
            return {head.first, head.second - 1};
        case DOWN:
            return {head.first, head.second + 1};
        case LEFT:
            return {head.first - 1, head.second};
        case RIGHT:
            return {head.first + 1, head.second};
        case WAIT:
            return head;
    }
    return head;
}

void Snake::kill() {
    snake.clear();
    lenght = 0;
    isAlive = false;
}