#include "grid.hpp"
#include <raylib.h>

void Grid::Draw()
{
  for (int row = 0; row < rows; row++)
  {
    for (int column = 0; column < columns; column++)
    {
      Color color = cells[row][column] ? Color{0, 255, 0, 255} : Color{55, 55, 55, 255};
      DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
    }
  }
}

void Grid::SetValue(int row, int column, int value)
{
  if (IsWithinBounds(row, column))
  {
    cells[row][column] = value;
  }
}

int Grid::GetValue(int row, int column)
{
  if (IsWithinBounds(row, column))
  {
    return cells[row][column];
  }
  return 0;
}

bool Grid::IsWithinBounds(int row, int column)
{
  return row >= 0 && row < rows && column >= 0 && column < columns;
}

void Grid::FillRandom()
{
  for (int row = 0; row < rows; row++)
  {
    for (int column = 0; column < columns; column++)
    {
      int randomVal = GetRandomValue(0, 4);

      cells[row][column] = (randomVal == 4) ? ALIVE : DEAD;
    }
  }
}

void Grid::Clear()
{

  for (int row = 0; row < rows; row++)
  {
    for (int column = 0; column < columns; column++)
    {
      cells[row][column] = 0;
    }
  }
}

void Grid::ToggleCel(int row, int column)
{
  if (IsWithinBounds(row, column))
  {
    cells[row][column] = !cells[row][column];
  }
}
