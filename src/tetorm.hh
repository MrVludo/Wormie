#pragma once
#include "config.hh"

extern std::vector<std::vector<int>> fieldArr;

class tBlock {
private:
    int id;
    int rotation;
public:
    int x;
    int y;
    Color color;
    double prevMoveTime;
    float speed; // moves in 10 sec
    bool isFalling;
    tBlock();
    void rotate();
    void rotateBack();
    void fall();
    void sendToField();
    std::vector<std::vector<bool>> getArr();
    bool checkCollision();
    static Color idToColor(int blockId);
};

extern tBlock block;

void TetormKeyboard();