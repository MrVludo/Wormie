#include "tetorm.hh"
#include "TetormBlocks.hh"

tBlock::tBlock() {
    id = GetRandomValue(1, BLOCKAMOUNT);
    rotation = 0;
    color = idToColor(id);
    x = 3;
    y = -1;
    prevChangeTime = prevMoveTime = GetTime();
    speed = 20 + ((int)((GetTime()-startTime)/5));
    isFalling = true;
}

void tBlock::rotate() {
    rotation = (rotation+1) % 4;
    prevChangeTime = GetTime();
}
void tBlock::rotateBack() {
    rotation = (rotation+3) % 4;
}

std::vector<std::vector<bool>> tBlock::getArr() {
    std::vector<std::vector<bool>> arr;
    for (int i = 0; i < 4; ++i) {
        arr.push_back({0,0,0,0});
        for (int j = 0; j < 4; ++j) {
            arr[i][j] = tetormBlocks[id][rotation][j][i]; 
        }
    }
    return arr;
}

void tBlock::fall() {
    y++;
    if (checkCollision()) {
        isFalling = false;
        y--;
    }
    else {
        isFalling = true;
        prevChangeTime = prevMoveTime = GetTime();
    }
}

void tBlock::shift() {
    while(isFalling) {
        fall();
        tscore++;
    }
}

void tBlock::sendToField() {
    auto blockArr = getArr();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) if (blockArr[i][j]) {
            fieldArr[x+i][y+j] = id;
        }
    }
    clearRows();
}

bool tBlock::checkCollision() {
    auto blockArr = getArr();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) if (blockArr[i][j]) {
            if (y + j >= gridHeight)
                return true;
            if (x + i < 0 || x + i >= gridWidth)
                return true;
            if (fieldArr[x+i][y+j]) 
                return true;
        }
    }
    return false;
}

Color tBlock::idToColor(int blockId) {
    Color colorArr[8] =
    {
        WHITE, 
        GREEN, RED,
        ORANGE, BLUE,
        VIOLET, SKYBLUE, //Color{173, 216, 230, 255}, 
        YELLOW
    };
    if (blockId > 0 && blockId < 8) 
        return colorArr[blockId];
    return WHITE;
}
void tBlock::makeNew() {
    int prevId = id;
    while (id == prevId) block = tBlock();
    if (checkCollision())
        tGameOver = true;
}