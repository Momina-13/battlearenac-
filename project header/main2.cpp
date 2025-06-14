#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Battle Arena - Main Menu");

    Texture2D background = LoadTexture("board.jpg");
    Texture2D fightButton = LoadTexture("fight.jpg");

    Rectangle fightBtnRect = {
        (float)(screenWidth / 2 - fightButton.width / 2),
        (float)(screenHeight / 2 - fightButton.height / 2),
        (float)fightButton.width,
        (float)fightButton.height
    };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (CheckCollisionPointRec(GetMousePosition(), fightBtnRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Start game logic here
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(fightButton, fightBtnRect.x, fightBtnRect.y, WHITE);
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(fightButton);
    CloseWindow();

    return 0;
}
