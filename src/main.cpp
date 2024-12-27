#include <raylib.h>
#include "simulation.hpp"
#include <iostream>

int main()
{
    Color GREY = {29, 29, 29, 255};
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 25;
    int FPS = 12;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game Of Life");
    SetTargetFPS(FPS);
    Simulation simulation{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE};

    // simulation loop
    while (!WindowShouldClose())
    {

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition();
            int row = mousePos.y / CELL_SIZE;
            int column = mousePos.x / CELL_SIZE;
            simulation.ToggleCel(row, column);
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            simulation.ToggleRunning();
            SetWindowTitle(("Conway's Game Of Life - " + std::string(simulation.IsRunning() ? "Running" : "Paused")).c_str());
        }
        else if (IsKeyPressed(KEY_F))
        {
            FPS += 2;
            SetTargetFPS(FPS);
        }

        else if (IsKeyPressed(KEY_S))
        {
            if (FPS > 5)
            {
                FPS -= 2;
                SetTargetFPS(FPS);
            }
        }
        else if (IsKeyPressed(KEY_R))
        {
            simulation.CreateRandomState();
        }
        else if (IsKeyPressed(KEY_C))
        {
            simulation.ClearGrid();
        }

        simulation.Update();

        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();
    }

    CloseWindow();
}