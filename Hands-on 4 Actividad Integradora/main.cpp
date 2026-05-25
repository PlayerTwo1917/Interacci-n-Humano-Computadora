#include "raylib.h"
#include <cmath>
#include <vector>

// Enumeración para controlar las pantallas/transformaciones
enum Transformacion { TRASLACION, ROTACION, REBOTE, SENOIDAL, TRAYECTORIA, ORBITA };

int main() {
    // Configuración de la ventana
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Hands-on 4: Transformaciones Matemáticas");

    SetTargetFPS(60);

    // Estado inicial
    Transformacion estadoActual = TRASLACION;

    // --- Variables para las transformaciones ---
    // a. Traslación
    Vector2 posTraslacion = { 100.0f, screenHeight / 2.0f };
    float velocidadTraslacion = 4.0f;

    // b. Rotación
    float anguloRotacion = 0.0f;

    // c. Rebote
    Vector2 posRebote = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 velRebote = { 5.0f, 4.0f };
    float radioRebote = 20.0f;

    // d. Movimiento Senoidal
    float posXSenoidal = 50.0f;
    float tiempoSenoidal = 0.0f;
    float amplitudSenoidal = 100.0f;
    float frecuenciaSenoidal = 3.0f;

    // e. Trayectoria (Línea recta de Punto A a Punto B)
    Vector2 puntoA = { 100.0f, 500.0f };
    Vector2 puntoB = { 700.0f, 100.0f };
    float tTrayectoria = 0.0f; // Interpolador (0.0 a 1.0)
    float velocidadTrayectoria = 0.01f;

    // f. Órbita
    Vector2 centroOrbita = { screenWidth / 2.0f, screenHeight / 2.0f };
    float radioOrbita = 120.0f;
    float anguloOrbita = 0.0f;
    float velocidadOrbita = 0.03f;

    // Bucle principal de la aplicación
    while (!WindowShouldClose()) {
        // --- 1. LÓGICA DE ENTRADA (Cambiar de pantalla con teclado) ---
        if (IsKeyPressed(KEY_ONE))   estadoActual = TRASLACION;
        if (IsKeyPressed(KEY_TWO))   estadoActual = ROTACION;
        if (IsKeyPressed(KEY_THREE)) estadoActual = REBOTE;
        if (IsKeyPressed(KEY_FOUR))  estadoActual = SENOIDAL;
        if (IsKeyPressed(KEY_FIVE))  estadoActual = TRAYECTORIA;
        if (IsKeyPressed(KEY_SIX))   estadoActual = ORBITA;

        // --- 2. ACTUALIZACIÓN DE LAS ECUACIONES MATEMÁTICAS ---
        switch (estadoActual) {
        case TRASLACION:
            // X_f = X_i + v * dt
            posTraslacion.x += velocidadTraslacion;
            if (posTraslacion.x > screenWidth + 40) posTraslacion.x = -40; // Reiniciar al salir
            break;

        case ROTACION:
            // theta_f = theta_i + omega * dt
            anguloRotacion += 2.0f; // Incremento de ángulo en grados
            if (anguloRotacion >= 360.0f) anguloRotacion -= 360.0f;
            break;

        case REBOTE:
            // Inversión de signo de velocidad al tocar límites
            posRebote.x += velRebote.x;
            posRebote.y += velRebote.y;

            if ((posRebote.x + radioRebote >= screenWidth) || (posRebote.x - radioRebote <= 0)) {
                velRebote.x *= -1.0f; // Invierte dirección X
            }
            if ((posRebote.y + radioRebote >= screenHeight) || (posRebote.y - radioRebote <= 0)) {
                velRebote.y *= -1.0f; // Invierte dirección Y
            }
            break;

        case SENOIDAL:
            // Y = Y_centro + Amplitud * sin(frecuencia * tiempo)
            tiempoSenoidal += GetFrameTime();
            posXSenoidal += 3.0f;
            if (posXSenoidal > screenWidth + 30) posXSenoidal = -30;
            break;

        case TRAYECTORIA:
            // Interpolación lineal (LERP): P = A + t * (B - A)
            tTrayectoria += velocidadTrayectoria;
            if (tTrayectoria > 1.0f) tTrayectoria = 0.0f; // Reiniciar ciclo
            break;

        case ORBITA:
            // Coordenadas polares a cartesianas: X = r * cos(theta), Y = r * sin(theta)
            anguloOrbita += velocidadOrbita;
            if (anguloOrbita > 2.0f * PI) anguloOrbita -= 2.0f * PI;
            break;
        }

        // --- 3. DIBUJADO EN PANTALLA ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Guía del Menú superior
        DrawText("Presiona: 1:Traslacion | 2:Rotacion | 3:Rebote | 4:Senoidal | 5:Trayectoria | 6:Orbita", 10, 10, 16, DARKGRAY);
        DrawLine(0, 35, screenWidth, 35, LIGHTGRAY);

        // Renderizado según la transformación activa
        switch (estadoActual) {
        case TRASLACION:
            DrawText("a. TRASLACIÓN (Movimiento Lineal)", 20, 50, 20, MAROON);
            DrawCircleV(posTraslacion, 30, BLUE);
            break;

        case ROTACION:
            DrawText("b. ROTACIÓN (Alrededor de su propio eje)", 20, 50, 20, MAROON);
            // Dibujamos un rectángulo centrado para apreciar la rotación
            DrawRectanglePro(
                Rectangle{ screenWidth / 2.0f, screenHeight / 2.0f, 150, 80 },
                Vector2{ 75, 40 }, // Origen en el centro del rectángulo
                anguloRotacion,
                LIME
            );
            break;

        case REBOTE:
            DrawText("c. REBOTE (Colisiones con bordes)", 20, 50, 20, MAROON);
            DrawCircleV(posRebote, radioRebote, GOLD);
            break;

        case SENOIDAL: {
            DrawText("d. MOVIMIENTO SENOIDAL", 20, 50, 20, MAROON);
            float posY = (screenHeight / 2.0f) + amplitudSenoidal * sinf(frecuenciaSenoidal * tiempoSenoidal);
            DrawCircle(posXSenoidal, posY, 20, PURPLE);
            break;
        }

        case TRAYECTORIA: {
            DrawText("e. TRAYECTORIA (Interpolacion Lineal entre A y B)", 20, 50, 20, MAROON);
            // Dibujar puntos de control
            DrawCircleV(puntoA, 8, RED);
            DrawCircleV(puntoB, 8, RED);
            DrawLineV(puntoA, puntoB, LIGHTGRAY);

            // Calcular posición actual con LERP
            float currX = puntoA.x + tTrayectoria * (puntoB.x - puntoA.x);
            float currY = puntoA.y + tTrayectoria * (puntoB.y - puntoA.y);
            DrawCircle(currX, currY, 20, ORANGE);
            break;
        }

        case ORBITA: {
            DrawText("f. ÓRBITA (Coordenadas Polares)", 20, 50, 20, MAROON);
            // Dibujar el "sol" u origen
            DrawCircleV(centroOrbita, 25, RED);

            // Calcular la posición del planeta usando trigonometría
            float planetaX = centroOrbita.x + radioOrbita * cosf(anguloOrbita);
            float planetaY = centroOrbita.y + radioOrbita * sinf(anguloOrbita);

            // Dibujar órbita guía y el planeta
            DrawCircleLines(centroOrbita.x, centroOrbita.y, radioOrbita, LIGHTGRAY);
            DrawCircle(planetaX, planetaY, 15, DARKBLUE);
            break;
        }
        }

        EndDrawing();
    }

    // Cerrar ventana
    CloseWindow();
    return 0;
}
