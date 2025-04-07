#pragma once
#include "config.hh"

extern std::vector<std::vector<int>> fieldArr;
extern double startTime;
extern int tscore;
extern bool tGameOver;

extern void clearRows();

class tBlock {
private:
public:
    int id;
    int rotation;
    int x;
    int y;
    Color color;
    double prevMoveTime;
    double prevChangeTime;
    float speed; // moves in 10 sec
    bool isFalling;
    tBlock();
    void rotate();
    void rotateBack();
    void fall();
    void shift();
    void sendToField();
    std::vector<std::vector<bool>> getArr();
    bool checkCollision();
    static Color idToColor(int blockId);
    void makeNew();
};

extern tBlock block;

void TetormKeyboard();