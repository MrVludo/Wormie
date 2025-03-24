#include "config.hh"

Font FontJersey10, FontMicro5, FontTiny5;
std::ifstream GameDataFileR;
std::ofstream GameDataFileW;
std::string GameDataFileName = "GameData.worm";
int savedGameData[2];
bool closeWindow = false;

// Button: posX, posY, width, height 
std::vector<Vector4> buttons = {{0, 0, 0, 0}, {0, 0, 0, 0}};

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Wormie (by Vludo)");

    // SetExitKey(KEY_NULL);
    FontJersey10 = LoadFont("../fonts/Jersey10-Regular.ttf");
    FontMicro5 = LoadFont("../fonts/Micro5-Regular.ttf");
    FontTiny5 = LoadFont("../fonts/Tiny5-Regular.ttf");

    if (FontJersey10.texture.id == 0 || FontMicro5.texture.id == 0) {
        TraceLog(LOG_WARNING, "Failed to load fonts!");
    }

    if (FontJersey10.texture.id == 0 || FontMicro5.texture.id == 0) {
        TraceLog(LOG_WARNING, "Failed to load fonts!");
    }

    if (!IsWindowReady()) {
        TraceLog(LOG_ERROR, "Failed to initialize window!");
        return -1;
    }

    GameDataFileR.open(GameDataFileName);
    if (!GameDataFileR.is_open()) {
        GameDataFileW.open(GameDataFileName);
        GameDataFileW << "0 0";
        GameDataFileW.close();
        GameDataFileR.open(GameDataFileName);
    }
    GameDataFileR >> std::hex >> savedGameData[0] >> std::hex >> savedGameData[1];
    // std::cout << savedGameData[0] << ' ' << savedGameData[1] << std::endl; 
    GameDataFileR.close();
    
    while (!closeWindow && !WindowShouldClose()) {
        KeyboardEvents();
        LobbyKeyboard();

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

        buttons[0] = {5*widthScale, 26*heightScale, 90*widthScale, 9*heightScale};
        buttons[1] = {5*widthScale, 36*heightScale, 90*widthScale, 9*heightScale};
        DrawRectangle(buttons[0].x, buttons[0].y, buttons[0].z, buttons[0].w, DARKGRAY);
        DrawRectangle(buttons[1].x, buttons[1].y, buttons[1].z, buttons[1].w, LIGHTGRAY);
        DrawTextEx(FontTiny5, "Choose a game:", {5*widthScale,5*heightScale}, 10*heightScale, 2, RAYWHITE);
        DrawTextEx(FontTiny5, "\n\n 1: Wormie 12x15", {5*widthScale,5*heightScale}, 10*heightScale, 2, RAYWHITE);
        DrawTextEx(FontTiny5, "\n\n\n 2: Wormie 16x20", {5*widthScale,5*heightScale}, 10*heightScale, 2, DARKGRAY);

        // Mouse position circle:
        Vector2 mousePosition = GetMousePosition(); 
        DrawCircleV(mousePosition, 1.6*heightScale, RED);
        HideCursor();


        EndDrawing();
    }

    GameDataFileW.open(GameDataFileName);
    GameDataFileW << std::hex << savedGameData[0] << ' ' << std::hex << savedGameData[1]; 
    GameDataFileW.close();
    CloseWindow();
    UnloadFont(FontJersey10);
    UnloadFont(FontMicro5);
    return 0;
}
