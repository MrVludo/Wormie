#include "config.hh"
#include "snake.hh"
#include "tetorm.hh"

void KeyboardEvents() {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_W))
        closeWindow = true;
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {}
}

void LobbyKeyboard() {
    if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1))
        play_snake(1);
    if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2))
        play_snake(2);
    if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)) 
        play_tetorm();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();
        for (int i = 0; i < buttons.size(); ++i) {
            auto button = buttons[i];
            if (mousePosition.x >= button.x && mousePosition.y >= button.y
                && mousePosition.x <= button.x + button.z
                && mousePosition.y <= button.y + button.w) {
                play_snake(i + 1);
                break;
            }
        }
    }
}

void SnakeKeyboard() {
    // movement:
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        if (snake1.getDirection() != UP && (snake1.getLenght() == 1 || snake1.getFacing() != DOWN)) {
            snake1.setDirection(UP);
            // snake1.Move(UP);
        }
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        if (snake1.getDirection() != DOWN && (snake1.getLenght() == 1 || snake1.getFacing() != UP)) {
            snake1.setDirection(DOWN);
            // snake1.Move(DOWN);
        }
    }
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        if (snake1.getDirection() != LEFT && (snake1.getLenght() == 1 || snake1.getFacing() != RIGHT)) {
            snake1.setDirection(LEFT);
            // snake1.Move(LEFT);
        }
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        if (snake1.getDirection() != RIGHT && (snake1.getLenght() == 1 || snake1.getFacing() != LEFT)) {
            snake1.setDirection(RIGHT);
            // snake1.Move(RIGHT);
        }
    }

    // change grid / show grid
    /*
    if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_G)) {
        if (snake1.getLenght() <= 1) {
            if (gridHeight == 12) gridHeight = 16;
            else gridHeight = 12;
            if (gridWidth == 15) gridWidth = 20;
            else gridWidth = 15;
            apple = make_apple();
        }
    } else */
    if (IsKeyPressed(KEY_G)) {
        showGrid ^= 1;
    }

    // new snake
    if (IsKeyPressed(KEY_R) || IsKeyPressed(KEY_N) 
        || (IsKeyPressed(KEY_ENTER) && snake1.getLenght() == 0)) {
        snake1 = Snake();
        score = 0;
        apple = make_apple();
    }
}

void TetormKeyboard() {
    // Movement:
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        block.rotate();
        if (block.checkCollision()) {
            block.x -= 1;
            if (block.checkCollision()) {
                block.x += 2;
                if (block.checkCollision()) {
                    block.x -= 3;
                    if (block.checkCollision()) {
                        block.x += 4;
                        if (block.checkCollision()) {
                            block.x -= 2;
                            block.y += 1;
                            if (block.checkCollision()) {
                                block.y += 1;
                                if (block.checkCollision()) {
                                    block.y -= 2;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (block.checkCollision()) block.rotateBack();
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) || IsKeyPressedRepeat(KEY_DOWN) || IsKeyPressedRepeat(KEY_S)) {
        block.fall();
        score++;
    }
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) || IsKeyPressedRepeat(KEY_LEFT) || IsKeyPressedRepeat(KEY_A)) {
        block.x -= 1;
        if (block.checkCollision()) block.x += 1;
        else block.prevChangeTime = GetTime();
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) || IsKeyPressedRepeat(KEY_RIGHT) || IsKeyPressedRepeat(KEY_D)) {
        block.x += 1;
        if (block.checkCollision()) block.x -= 1;
        else block.prevChangeTime = GetTime();
    }
    if (IsKeyPressed(KEY_SPACE)) {
        block.shift();
        block.sendToField();
        block.makeNew();
    }
}