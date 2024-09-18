#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;
}

void Block::Draw()
{
    std::vector<Position> tiles = Block::GetCellPositions(); //return moved tiles (shape is clingy to Block instance already)
    for(Position item : tiles)
    {
        DrawRectangle(item.col * cellSize + 10, item.row * cellSize + 10, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::DrawNextBlock(Vector2 DrawPosition)
{
    std::vector<Position> tiles = cells[rotationState];
    for(Position item : tiles)
    {
        DrawRectangle(item.col * cellSize + DrawPosition.x, item.row * cellSize + DrawPosition.y, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int cols)
{
    rowOffset += rows;
    colOffset += cols;
}

/// get cell positions for one rotationState of a block, (given the rotationState, values of rowOffset and colOffset)
/// return cell positions, also position of a block, no other info but positions
std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.col + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotation()
{
    rotationState++;
    if(rotationState >= (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::Unrotation()
{
    rotationState--;
    if(rotationState < 0)
    {
        rotationState = cells.size() - 1;
    }
}
