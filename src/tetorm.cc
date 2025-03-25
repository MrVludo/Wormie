#include "config.hh"
#include "tetorm.hh"

std::vector<std::vector<int>> fieldArr;

bool tetormExit = false;
extern bool showGrid;
double startTime;
tBlock block;

void play_tetorm() {
    gridHeight = 18;
    gridWidth = 10;
    fieldArr.clear();
    for (int i = 0; i < gridWidth; ++i) {
        fieldArr.push_back({});
        for (int j = 0; j < gridHeight; ++j)
            fieldArr[i].push_back(0);
    }
    startTime = GetTime();
    block = tBlock();
    while (!closeWindow && !WindowShouldClose() && !tetormExit) {
        KeyboardEvents();
        TetormKeyboard();

        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        ShowCursor();

        if (screenHeight*1.05f > screenWidth) {
            screenWidth = screenHeight*1.05f;
            SetWindowSize(screenWidth, screenHeight);
        }

        float widthScale = screenWidth / 100.0f;
        float heightScale = screenHeight / 100.0f;

        BeginDrawing(); 
        ClearBackground(BLACK);
        
        // Game field:
        Vector2 fieldSize = {gridWidth * 5.f*heightScale, gridHeight * 5.f*heightScale};
        Vector2 fieldPosition = {5.f * widthScale, 5.f * heightScale};
        DrawRectangleV(fieldPosition, fieldSize, DARKGRAY);
        
        // Falling block:
        auto blockArr = block.getArr();
        
        if (GetTime() - block.prevMoveTime >= 10./block.speed) {
            block.fall();
            if (!block.isFalling && (GetTime() - block.prevChangeTime >= 10./block.speed 
                || GetTime() - block.prevMoveTime >= 3 * 10./block.speed)) {
                block.sendToField();
                block.makeNew();
            }
        }
        
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (blockArr[i][j]) {
                    DrawRectangle(fieldPosition.x + (block.x+i) * fieldSize.x/gridWidth, 
                        fieldPosition.y + (block.y+j) * fieldSize.y/gridHeight, 
                        fieldSize.x/gridWidth, fieldSize.y/gridHeight, block.color);
                }
            }
        }

        // Other blocks:
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) if (fieldArr[i][j]) {
                DrawRectangle(fieldPosition.x + i * fieldSize.x/gridWidth, 
                        fieldPosition.y + j * fieldSize.y/gridHeight, 
                        fieldSize.x/gridWidth, fieldSize.y/gridHeight, tBlock::idToColor(fieldArr[i][j]));
            }
        }

        // Game field grid (gridWidth x gridHeight):
        if (true || showGrid) {
            for (float i = 0; i <= gridWidth; ++i) {
                float gridLineCenterX = fieldPosition.x + i/gridWidth * fieldSize.x;
                Vector2 gridLinePosition = {gridLineCenterX - 1, fieldPosition.y};
                DrawRectangleV(gridLinePosition, {2, fieldSize.y}, DARKGRAY);
            }
            for (float i = 0; i <= gridHeight; ++i) {
                float gridLineCenterY = fieldPosition.y + i/gridHeight * fieldSize.y;
                Vector2 gridLinePosition = {fieldPosition.x, gridLineCenterY - 1};
                DrawRectangleV(gridLinePosition, {fieldSize.x, 2}, DARKGRAY);
            }
        }
        EndDrawing();
    }
}