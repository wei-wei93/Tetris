#include "game.h"
#include <random>

/// Game construct
Game::Game()
{
    grid = Grid();
    blocks = {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    completed = 0;
}

/// generate a block in random type
Block Game::GetRandomBlock()
{
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    return block;
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw();
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || !IsBlockFit())
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || !IsBlockFit())
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !IsBlockFit())
        {
            currentBlock.Move(-1, 0);
            if (!IsBlockFit())
            {
                gameOver = true;
            }
            LockBlock();
        }
    }
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotation();
        if (IsBlockOutside() || !IsBlockFit())
        {
            currentBlock.Unrotation();
        }
    }
}

// Scan each row from bottom to top, and make due operations
void Game::EnableScanning()
{
    completed += grid.ScanForCompletedRows();
}

void Game::DisplayScore(Font font, Vector2 position, float fontSize, float spacing, Color tint)
{
    // const char* completedChar = char(completed);
    std::string t = std::to_string(completed);
    const char* completedChars = t.c_str();
    DrawTextEx(font, completedChars, position, fontSize, spacing, tint);
}

void Game::DisplayNextBlock(Vector2 DrawPosition)
{
    nextBlock.DrawNextBlock(DrawPosition);
}

void Game::DisplayGameOver(Font font, Vector2 position, float fontSize, float spacing, Color tint)
{
    if(gameOver)
    {
        DrawTextEx(font, "Game Over!", position, fontSize, spacing, tint);
    }
}

// void Game::DisplayNextBlock(Rectangle rec, float roundness, int segments, Color color)
// {
// }

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.col))
        {
            return true;
        }
    }
    return false;
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id;
    }

    // If Game is Over
    if (!gameOver) // Stop renewing current block when game's over
    {
        currentBlock = nextBlock;
        nextBlock = GetRandomBlock();
    }
}

bool Game::IsBlockFit()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.grid[item.row][item.col] != 0)
        {
            return false;
        }
    }
    return true;
}
