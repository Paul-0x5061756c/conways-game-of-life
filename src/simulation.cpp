#include "simulation.hpp"
#include <vector>
#include <utility>

void Simulation::Draw()
{
  grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
  grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{
  int liveNeighbors = 0;

  std::vector<std::pair<int, int>> neighborOffsets =
      {
          {-1, 0},
          {1, 0},
          {0, -1},
          {0, 1},
          {-1, -1},
          {-1, 1},
          {1, -1},
          {1, 1},
      };

  for (const auto &offset : neighborOffsets)
  {
    int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
    int neighborColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns();

    liveNeighbors += grid.GetValue(neighborRow, neighborColumn);
  }

  return liveNeighbors;
}

void Simulation::Update()
{
  if (IsRunning())
  {
    for (int row = 0; row < grid.GetRows(); row++)
    {
      for (int column = 0; column < grid.GetColumns(); column++)
      {
        int liveNeighbors = CountLiveNeighbors(row, column);
        int cellValue = grid.GetValue(row, column);

        if (cellValue == grid.ALIVE)
        {
          tempGrid.SetValue(row, column, liveNeighbors < 2 || liveNeighbors > 3 ? grid.DEAD : grid.ALIVE);
          continue;
        }
        tempGrid.SetValue(row, column, liveNeighbors == 3 ? grid.ALIVE : grid.DEAD);
      }
    }

    grid = tempGrid;
  }
}

void Simulation::ClearGrid()
{
  if (!IsRunning())
  {
    grid.Clear();
  }
}

void Simulation::CreateRandomState()
{
  if (!IsRunning())
  {
    grid.FillRandom();
  }
}

void Simulation::ToggleCel(int row, int column)
{
  if (!IsRunning())
  {
    grid.ToggleCel(row, column);
  }
}
