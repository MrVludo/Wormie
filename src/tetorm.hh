#pragma once
#include "config.hh"

extern std::vector<std::vector<int>> fieldArr;
extern double startTime;
extern int tscore;
extern bool tGameOver;

extern void clearRows();
extern void clearField();

class tBlock {
private:
public:
    int id;
    int holdId;
    int rotation;
    int x;
    int y;
    Color color;
    double prevMoveTime;
    double prevChangeTime;
    float speed; // moves in 10 sec
    bool isFalling;
    bool isHolded;
    tBlock(int makeId = 0);
    void rotate();
    void rotateBack();
    void fall();
    void shift();
    void sendToField();
    std::vector<std::vector<bool>> getArr();
    std::vector<std::vector<bool>> getHoldArr();
    bool checkCollision();
    static Color idToColor(int blockId);
    void makeNew();
    void hold();
};

extern tBlock block;

void TetormKeyboard();