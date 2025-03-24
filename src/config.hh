#pragma once

#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <chrono>
#include <fstream>

// Game Data:
extern std::ifstream GameDataFileR;
extern std::ofstream GameDataFileW;
extern int savedGameData[2];
extern std::string GameDataFileName;

// Fonts:
extern Font FontJersey10, FontMicro5, FontTiny5;


extern bool closeWindow;

extern std::vector<Vector4> buttons;

void KeyboardEvents();

void play_snake(int gridR);

void LobbyKeyboard();