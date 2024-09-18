#include <raylib.h>
#include "game.h"
#include "color.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(560, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("font/Prague.ttf", 128, 0, 0);
    Font DigitFont = LoadFontEx("font/Digit.TTF", 128, 0, 0);

    Game game = Game();
    game.grid.Print();

    while (WindowShouldClose() == false)
    {
        game.HandleInput();
        if (EventTriggered(0.3))  //0.3s
        {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {370, 25}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {382, 185}, 38, 2, WHITE);
        DrawRectangleRounded({340, 70, 190, 80}, 0.3, 6, lightBlue);
        DrawRectangleRounded({335, 230, 200, 160}, 0.3, 6, lightBlue);
        game.DisplayScore(DigitFont, {412, 81}, 50, 2, WHITE);
        game.DisplayNextBlock({390, 280});
        game.DisplayGameOver(font, {345, 475}, 30, 2, WHITE);
        game.EnableScanning();
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}