#include "grid.h"
#include <iostream>
#include "color.h"

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::Print()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            int cellValue = grid[row][col];
            DrawRectangle(col * cellSize + 10, row * cellSize + 10, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int col)
{
    if(row < 0 || row >= numRows || col < 0 || col >= numCols)
    {
        return true;
    }
    return false;
}

bool Grid::IsRowCompleted(int row)
{
    for (int col = 0; col < numCols; col++)
    {
        if (grid[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}

bool Grid::IsRowEmpty(int row)
{
    for (int col = 0; col < numCols; col++)
    {
        if (grid[row][col] != 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::MoveRowDown(int row, int interval)
{
    for (int col = 0; col < numCols; col++)
    {
        grid[row+interval][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

int Grid::ScanForCompletedRows()
{
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--)  //scan from bottom to top
    {
        if (IsRowEmpty(row))
        {
            break;
        }
        //check, and reset completed rows.
        if (IsRowCompleted(row))
        {
            completed++;
            for (int col = 0; col < numCols; col++)
            {
                grid[row][col] = 0;
            }
        }else if(completed != 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}
