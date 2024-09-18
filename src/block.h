#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "color.h"

class Block
{
public:
    Block();
    void Draw();
    void DrawNextBlock(Vector2 DrawPosition);
    void Move(int rows, int cols);
    void Rotation();
    void Unrotation();
    std::vector<Position> GetCellPositions();
    int id;
    std::map<int, std::vector<Position>> cells;  //store 4 rotations of a block

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int colOffset;
};