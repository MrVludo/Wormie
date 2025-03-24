#include "config.hh"
#include "snake.hh"

bool showGrid = false;
bool snakeExit = false;
int score;
int bestScore[3];
int gridHeight = 12;
int gridWidth = 15;

Snake snake1;
std::pair<int,int> apple;

void play_snake(int gridR) {
    switch (gridR) {
        case 1:
            gridHeight = 12;
            gridWidth = 15;
            break;
        case 2:
            gridHeight = 16;
            gridWidth = 20;
            break;
        default:
            gridHeight = 8;
            gridWidth = 10;
    }

    Font scoreFont = FontMicro5;

    score = 0;
    bestScore[gridR] = savedGameData[gridR-1];

    apple = make_apple();
    snake1 = Snake();
    
    while (!closeWindow && !WindowShouldClose() && !snakeExit) {
        KeyboardEvents();
        SnakeKeyboard();

        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        if (screenHeight > screenWidth) {
            screenWidth = screenHeight;
            SetWindowSize(screenWidth, screenHeight);
        }

        float widthScale = screenWidth / 100.0f;
        float heightScale = screenHeight / 100.0f;

        BeginDrawing(); 
        ClearBackground(BLACK);

        // Game field:
        Vector2 fieldSize = {10.0f/8.0f * 0.8f * screenHeight, 0.8f * screenHeight};
        Vector2 fieldPosition = {(screenWidth - fieldSize.x) / 2, 15 * heightScale};
        DrawRectangle(fieldPosition.x, fieldPosition.y, fieldSize.x, fieldSize.y, DARKGRAY);


        // Snake:
        auto snakeVector = snake1.getSnake();

        if (!snakeVector.empty() && (snakeVector.back().first < 0 || snakeVector.back().first >= gridWidth
            || snakeVector.back().second < 0 || snakeVector.back().second >= gridHeight))
            snake1.kill();
        for (int tail = 1; tail < snake1.getLenght(); ++tail) {
            if (tail > snakeVector.size()) break;
            if (snakeVector.back() == *(snakeVector.rbegin()+tail)) {
                snake1.kill();
                break;
            }
        }

        snakeVector = snake1.getSnake();

        if (!snakeVector.empty()) {
            DrawRectangle(fieldPosition.x + snakeVector.back().first * fieldSize.x/gridWidth,
                fieldPosition.y + snakeVector.back().second * fieldSize.y/gridHeight,
                fieldSize.x/gridWidth, fieldSize.y/gridHeight, snake1.headColor);
        }
        for (int tail = 1; tail < snake1.getLenght(); ++tail) {
            if (tail > snakeVector.size()) break;
            DrawRectangle(fieldPosition.x + (*(snakeVector.rbegin()+tail)).first * fieldSize.x/gridWidth,
            fieldPosition.y + (*(snakeVector.rbegin()+tail)).second * fieldSize.y/gridHeight,
            fieldSize.x/gridWidth, fieldSize.y/gridHeight, snake1.tailColor[tail%2]);
        }

        if (GetTime() - snake1.prevMoveTime >= 10.0f / snake1.getSpeed()) {
            snake1.Move(snake1.getDirection());
        }

        // Apple:
        if (!snakeVector.empty() && snakeVector.back() == apple) {
            snake1.grow();
            score++;
            apple = make_apple();
        }
        bestScore[gridR] = std::max(bestScore[gridR], score);
        savedGameData[gridR-1] = std::max(savedGameData[gridR-1], score);

        DrawRectangle(fieldPosition.x + apple.first * fieldSize.x/gridWidth,
            fieldPosition.y + apple.second * fieldSize.y/gridHeight,
            fieldSize.x/gridWidth, fieldSize.y/gridHeight, RED);

        // Game field grid (gridWidth x gridHeight) (relation 10:8):
        if (showGrid) {
            for (float i = 0; i <= gridWidth; ++i) {
                float gridLineCenterX = fieldPosition.x + i/gridWidth * fieldSize.x;
                Vector2 gridLinePosition = {gridLineCenterX - fieldSize.x/600, fieldPosition.y};
                DrawRectangleV(gridLinePosition, {fieldSize.x/300, fieldSize.y}, BLACK);
            }
            for (float i = 0; i <= gridHeight; ++i) {
                float gridLineCenterY = fieldPosition.y + i/gridHeight * fieldSize.y;
                Vector2 gridLinePosition = {fieldPosition.x, gridLineCenterY - fieldSize.x/600};
                DrawRectangleV(gridLinePosition, {fieldSize.x, fieldSize.x/300}, BLACK);
            }
        }

        // Grid size info text:
        DrawTextEx(FontTiny5, ("Wormie "+std::to_string(gridHeight)+"x"+std::to_string(gridWidth)).c_str(),
            {fieldPosition.x, fieldPosition.y+fieldSize.y}, 5*heightScale, 2, RAYWHITE);

        // Leave info text:
        std::string leaveText = "Press ESC to leave.";
        Vector2 leaveTextSize = MeasureTextEx(FontTiny5, leaveText.c_str(), 5*heightScale, 2); 
        DrawTextEx(FontTiny5, leaveText.c_str(), 
            {fieldPosition.x + fieldSize.x - leaveTextSize.x, fieldPosition.y + fieldSize.y},
            5*heightScale, 2, RAYWHITE);

        // Score text:
        Vector2 scorePosition = {fieldPosition.x, 0};
        std::string scoreText =  "Score: ";
        float scoreFontSize = 12 * heightScale; 
        DrawTextEx(scoreFont, scoreText.c_str(), scorePosition, scoreFontSize, 2, RAYWHITE);
        Vector2 scoreTextSize = MeasureTextEx(scoreFont, scoreText.c_str(), scoreFontSize, 2);
        DrawTextEx(scoreFont, std::to_string(score).c_str(), {scorePosition.x + scoreTextSize.x, scorePosition.y}, scoreFontSize, 2, RED);

        std::string bestScoreText = "Best: ";
        Vector2 bestScoreTextSize = MeasureTextEx(scoreFont, bestScoreText.c_str(), scoreFontSize, 2); 
        Vector2 bestScoreSize = MeasureTextEx(scoreFont, std::to_string(bestScore[gridR]).c_str(), scoreFontSize, 2);
        DrawTextEx(scoreFont, bestScoreText.c_str(), 
            {fieldPosition.x + fieldSize.x - bestScoreTextSize.x - bestScoreSize.x, 0},
            scoreFontSize, 2, RAYWHITE);
        DrawTextEx(scoreFont, std::to_string(bestScore[gridR]).c_str(),
            {fieldPosition.x + fieldSize.x - bestScoreSize.x, 0},
            scoreFontSize, 2, RED);

        EndDrawing();
        ShowCursor();
    }
    GameDataFileW.open(GameDataFileName);
    GameDataFileW << std::hex << savedGameData[0] << ' ' << std::hex << savedGameData[1]; 
    GameDataFileW.close();
}

std::pair<int,int> make_apple() {
    auto snakeVector = snake1.getSnake();

    std::pair<int,int> apple = {GetRandomValue(0,gridWidth-1), GetRandomValue(0,gridHeight-1)};

    while (1) {
        int tail;
        for (tail = 0; tail < snake1.getLenght(); ++tail) {
            if (tail > snakeVector.size()) break;
            if (apple == *(snakeVector.rbegin()+tail)) {
                apple = {GetRandomValue(0,gridWidth-1), GetRandomValue(0,gridHeight-1)};
                break;
            }
        }
        if (tail == snake1.getLenght() || tail > snakeVector.size()) break;
    }

    return apple;
}

        