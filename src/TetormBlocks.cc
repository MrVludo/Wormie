#include "tetorm.hh"
#include "TetormBlocks.hh"

tBlock::tBlock() {
    id = GetRandomValue(1, BLOCKAMOUNT);
    rotation = 0;
    color = idToColor(id);
    x = 3;
    y = -1;
    prevMoveTime = GetTime();
    speed = 20;
    isFalling = true;
}

void tBlock::rotate() {
    rotation = (rotation+1) % 4;
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
    prevMoveTime = GetTime();
}

void tBlock::sendToField() {
    auto blockArr = getArr();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) if (blockArr[i][j]) {
            fieldArr[x+i][y+j] = id;
        }
    }
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
    switch (blockId) {
    case 1:
        return GREEN;
    case 2:
        return RED;
    case 3:
        return YELLOW;
    default:
        return WHITE;
    }
}