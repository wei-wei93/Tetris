#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    int grid[20][10];
    bool IsCellOutside(int row, int col);
    bool IsRowCompleted(int row);
    bool IsRowEmpty(int row);
    void MoveRowDown(int row, int interval);
    int ScanForCompletedRows();

private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};