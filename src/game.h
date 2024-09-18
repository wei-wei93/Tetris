#pragma once
#include <iostream>
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
    Game();
    Block GetRandomBlock();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    void RotateBlock();
    void EnableScanning();
    Grid grid;
    void DisplayScore(Font font, Vector2 position, float fontSize, float spacing, Color tint);
    void DisplayNextBlock(Vector2 DrawPosition);
    void DisplayGameOver(Font font, Vector2 position, float fontSize, float spacing, Color tint);

private:
    std::vector<Block> blocks;
    bool IsBlockOutside();
    void LockBlock();
    bool IsBlockFit();
    Block currentBlock;
    Block nextBlock;
    bool gameOver;
    int completed;
};
