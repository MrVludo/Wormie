#include "config.hh"
#include "tetorm.hh"

std::vector<std::vector<int>> fieldArr;

bool tetormExit = false;
extern bool showGrid;
double startTime;
tBlock block;
int tscore;
bool tGameOver = false;

void play_tetorm() {
    Font scoreFont = FontMicro5;
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
    tscore = 0;
    tGameOver = false;
    int tbestScore = savedGameData[2];
    while (!tGameOver && !closeWindow && !WindowShouldClose() && !tetormExit) {
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
        }
        if (GetTime() - block.prevMoveTime >= 2 * 10./block.speed)
            if (!block.isFalling && (GetTime() - block.prevChangeTime >= 10./block.speed 
                || GetTime() - block.prevMoveTime >= 3 * 10./block.speed)) {
                block.sendToField();
                block.makeNew();
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

        // Score text
        std::string scoreText = "Score: ";
        float scoreFontSize = 12 * heightScale; 
        Vector2 scorePosition = {fieldPosition.x, 0};
        Vector2 scoreSize = MeasureTextEx(scoreFont, std::to_string(tscore).c_str(), scoreFontSize, 2);
        DrawTextEx(scoreFont, scoreText.c_str(), 
            {fieldPosition.x + fieldSize.x + 5*widthScale, 0},
            scoreFontSize, 2, RAYWHITE);
        DrawTextEx(scoreFont, std::to_string(tscore).c_str(),
            {fieldPosition.x + fieldSize.x + 5*widthScale, 0.8f*(scoreSize.y)},
            scoreFontSize, 2, RED);

        tbestScore = savedGameData[2] = std::max(tbestScore, tscore);
        
        std::string bestScoreText = "Best score: ";
        Vector2 bestScoreTextSize = MeasureTextEx(scoreFont, bestScoreText.c_str(), scoreFontSize, 2); 
        Vector2 bestScoreSize = MeasureTextEx(scoreFont, std::to_string(tbestScore).c_str(), scoreFontSize, 2);
        DrawTextEx(scoreFont, bestScoreText.c_str(), 
            {fieldPosition.x + fieldSize.x + 5*widthScale, 1.6f*(scoreSize.y)},
            scoreFontSize, 2, RAYWHITE);
        DrawTextEx(scoreFont, std::to_string(tbestScore).c_str(),
            {fieldPosition.x + fieldSize.x + 5*widthScale, 2.4f*(scoreSize.y)},
            scoreFontSize, 2, RED);


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
    GameDataFileW.open(GameDataFileName);
    for (int i : savedGameData) 
        GameDataFileW << std::hex << savedGameData[i] << ' '; 
    GameDataFileW.close();
}


void clearRows() {
    for (int row = gridHeight-1; row >= 0; --row) {
        int column = gridWidth-1;
        for (; column >= 0; --column) {
            if (!fieldArr[column][row]) break;
        }
        if (column == -1) {
            tscore += 50;
            for (column = gridWidth-1; column >= 0; --column) {
                fieldArr[column][row] = 0;
            }
            if (row > 0) 
                for (int ic = 0; ic < gridWidth; ++ic) 
                    for (int shiftRow = row-1; shiftRow >= 0; --shiftRow) {
                        fieldArr[ic][shiftRow + 1] = fieldArr[ic][shiftRow];
                    }
            row++;
        }
    }
}