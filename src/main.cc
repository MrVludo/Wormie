#include "config.hh"

Font FontJersey10, FontMicro5, FontTiny5;
std::ifstream GameDataFileR;
std::ofstream GameDataFileW;
std::string GameDataFileName = "GameData.worm";
int savedGameData[3];
bool closeWindow = false;

std::vector<Vector4> buttons;

int gridHeight = 12;
int gridWidth = 15;

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
        GameDataFileW << "0 0 0";
        GameDataFileW.close();
        GameDataFileR.open(GameDataFileName);
    }
    GameDataFileR >> std::hex >> savedGameData[0] >> std::hex >> savedGameData[1] >> std::hex >> savedGameData[2];
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
        Vector2 mousePosition = GetMousePosition(); 
        
        DrawTextEx(FontTiny5, "Choose a game:", {5*widthScale,5*heightScale}, 10*heightScale, 2, RAYWHITE);
        
        std::vector<std::string> buttons_text = {
            "\n\n 1: Wormie 12x15",
            "\n\n\n 2: Wormie 16x20",
            "\n\n\n\n 3: Tetorm",
        };

        // Button: posX, posY, width, height 
        buttons.resize(buttons_text.size());

        for (int i = 0; i < buttons.size(); ++i) {
            buttons[i] = {5*widthScale, (26 + i*10)*heightScale, 90*widthScale, 9*heightScale};
            // Mouse hover
            bool ismousehover = false;
            if (mousePosition.x >= buttons[i].x && 
                mousePosition.y >= buttons[i].y &&
                mousePosition.x <= buttons[i].x + buttons[i].z &&
                mousePosition.y <= buttons[i].y + buttons[i].w)
                    ismousehover = true;
            
            DrawRectangle(buttons[i].x, buttons[i].y, buttons[i].z, buttons[i].w, (ismousehover ? LIGHTGRAY : DARKGRAY));
            DrawTextEx(FontTiny5, buttons_text[i].c_str(), {5*widthScale,5*heightScale}, 10*heightScale, 2, (ismousehover ? DARKGRAY : RAYWHITE));
        }
        

        // Mouse position circle:
        DrawCircleV(mousePosition, 1.6*heightScale, RED);
        HideCursor();


        EndDrawing();
    }

    GameDataFileW.open(GameDataFileName);
    GameDataFileW << std::hex << savedGameData[0] << ' ' << std::hex << savedGameData[1] << ' ' << std::hex << savedGameData[2]; 
    GameDataFileW.close();
    CloseWindow();
    UnloadFont(FontJersey10);
    UnloadFont(FontMicro5);
    return 0;
}
