//Martha Mariana Angulo González
//220588284

#include "raylib.h"

int main() {

    InitWindow(800, 600, "Raylib Test");

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hola raylib!", 300, 280, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}