#include "raylib.h"
#include "raymath.h"

#define vel 5.0f

typedef enum GameScreen { LOGO = 0, TITLE, CREDITS, SETTINGS, GAMEPLAY, PAUSE} GameScreen;

int main() {
    InitWindow(0, 0, "Legends Farm");

    Texture2D logo = LoadTexture("resources/logo.png");

    int LarguraTela = GetScreenWidth();
    int AlturaTela = GetScreenHeight();

    SetTargetFPS(60);

    Rectangle bounds = {0, 0, 2000, 2000};
    float radius = 20.0f;

    Vector2 pos = {bounds.width / 2.0f, bounds.height / 2.0f};

    Camera2D camera = {0};
    camera.offset   = (Vector2){LarguraTela / 2.0f, AlturaTela / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom     = 1.0f;

    int framesCounter = 0;
    GameScreen currentScreen = LOGO;

    int btnWidth = 250;
    int btnHeight = 60;
    int centerX = LarguraTela / 2 - btnWidth / 2;
    int startY = AlturaTela / 2 - 100;

    Rectangle btnJogar = { centerX, startY, btnWidth, btnHeight };
    Rectangle btnCreditos = { centerX, startY + 80, btnWidth, btnHeight };
    Rectangle btnConfig = { centerX, startY + 160, btnWidth, btnHeight };
    Rectangle btnVoltar = { LarguraTela/2 - 100, AlturaTela/2 + 120, 200, 50 };

    while (!WindowShouldClose()) {
        
        Vector2 mousePoint = GetMousePosition();
        
        switch (currentScreen) {
            case LOGO: {
                framesCounter++;
                if (framesCounter > 120) {
                    currentScreen = TITLE;
                }
            } break;

            case TITLE: {
                if (CheckCollisionPointRec(mousePoint, btnJogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = GAMEPLAY;
                }

                if (CheckCollisionPointRec(mousePoint, btnCreditos) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = CREDITS;
                }

                if (CheckCollisionPointRec(mousePoint, btnConfig) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = SETTINGS;
                }
                
            } break;
        
            case CREDITS: {
                if (CheckCollisionPointRec(mousePoint, btnVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                currentScreen = TITLE;
                }
            } break;

            case SETTINGS: {
                if (CheckCollisionPointRec(mousePoint, btnVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                currentScreen = TITLE;
                }
            } break;

            case GAMEPLAY: {
                Vector2 dir = {0, 0};

                if (IsKeyDown(KEY_RIGHT)) dir.x += 1;
                if (IsKeyDown(KEY_LEFT))  dir.x -= 1;
                if (IsKeyDown(KEY_UP))    dir.y -= 1;
                if (IsKeyDown(KEY_DOWN))  dir.y += 1;

                if (dir.x != 0 || dir.y != 0) {
                    dir = Vector2Normalize(dir);
                    pos = Vector2Add(pos, Vector2Scale(dir, vel));
                }

                pos.x = Clamp(pos.x, bounds.x + radius, bounds.x + bounds.width - radius);
                pos.y = Clamp(pos.y, bounds.y + radius, bounds.y + bounds.height - radius);

                camera.target = pos;

                    if (IsKeyPressed(KEY_P)) {
                        currentScreen = PAUSE;
                    }

            } break;

            case PAUSE: {
                if (IsKeyPressed(KEY_P)) {
                    currentScreen = GAMEPLAY;
                }
            } break;

            default: break;
        }

        BeginDrawing();

        switch (currentScreen) {
            case LOGO: {
                DrawTexture(logo, LarguraTela/2 - logo.width/2, AlturaTela/2 - logo.height/2, WHITE);
            } break;

            case TITLE: {
            
            ClearBackground(YELLOW);
            
            DrawText("MENU PRINCIPAL", LarguraTela/2 - MeasureText("MENU PRINCIPAL", 50)/2, 100, 50, DARKBROWN);

            Color hoverColor = (Color){210, 180, 140, 255};
            Color normalColor = (Color){222, 184, 135, 255};

            DrawRectangleRec(btnJogar, CheckCollisionPointRec(mousePoint, btnJogar) ? hoverColor : normalColor);
            DrawText("JOGAR", btnJogar.x + btnWidth/2 - MeasureText("JOGAR", 25)/2, btnJogar.y + 15, 25, DARKGREEN);

            DrawRectangleRec(btnCreditos, CheckCollisionPointRec(mousePoint, btnCreditos) ? hoverColor : normalColor);
            DrawText("CRÉDITOS", btnCreditos.x + btnWidth/2 - MeasureText("CRÉDITOS", 25)/2, btnCreditos.y + 15, 25, DARKBLUE);

            DrawRectangleRec(btnConfig, CheckCollisionPointRec(mousePoint, btnConfig) ? hoverColor : normalColor);
            DrawText("CONFIGURAÇÕES", btnConfig.x + btnWidth/2 - MeasureText("CONFIGURAÇÕES", 25)/2, btnConfig.y + 15, 25, DARKPURPLE);

            } break;

            case GAMEPLAY: {
                HideCursor();
                ClearBackground(RAYWHITE);

                BeginMode2D(camera);
                    DrawRectangleRec(bounds, LIGHTGRAY);
                    DrawCircleV(pos, radius, RED);
                EndMode2D();

                Vector2 mouse = GetMousePosition();
                int crossSize = 20;

                DrawLine(mouse.x - crossSize, mouse.y, mouse.x + crossSize, mouse.y, DARKGREEN);
                DrawLine(mouse.x, mouse.y - crossSize, mouse.x, mouse.y + crossSize, DARKGREEN);
                DrawCircleLines(mouse.x, mouse.y, 15, DARKGREEN);
            } break;

            case CREDITS: {
                
                ClearBackground(YELLOW);

                DrawText("CRÉDITOS", LarguraTela/2 - MeasureText("CRÉDITOS", 40)/2, 100, 40, DARKBLUE);

                DrawText("Ian", LarguraTela/2 - MeasureText("Ian", 30)/2, 200, 30, BLACK);
                DrawText("Ricardo", LarguraTela/2 - MeasureText("Ricardo", 30)/2, 250, 30, BLACK);
                DrawText("Mateus", LarguraTela/2 - MeasureText("Mateus", 30)/2, 300, 30, BLACK);
                DrawText("João Victor", LarguraTela/2 - MeasureText("João Victor", 30)/2, 350, 30, BLACK);

                DrawRectangleRec(btnVoltar, CheckCollisionPointRec(mousePoint, btnVoltar) ? GRAY : LIGHTGRAY);
                DrawText("VOLTAR", btnVoltar.x + btnVoltar.width/2 - MeasureText("VOLTAR", 20)/2, btnVoltar.y + 15, 20, BLACK);

            } break;

            case SETTINGS: {

                ClearBackground(YELLOW);

                DrawText("CONFIGURAÇÕES", LarguraTela/2 - MeasureText("CONFIGURAÇÕES", 30)/2, AlturaTela/2, 30, DARKPURPLE);

                DrawRectangleRec(btnVoltar, CheckCollisionPointRec(mousePoint, btnVoltar) ? GRAY : LIGHTGRAY);
                DrawText("VOLTAR", btnVoltar.x + btnVoltar.width/2 - MeasureText("VOLTAR", 20)/2, btnVoltar.y + 15, 20, BLACK);

            } break;

            case PAUSE: {

                ClearBackground(YELLOW);

                DrawText("JOGO PAUSADO", 280, 250, 30, RED);
                DrawText("Pressione P para continuar", 230, 300, 20, GRAY);

            } break;    

            default: break;
        }

        EndDrawing();
    }

    UnloadTexture(logo);
    CloseWindow();
    return 0;
}
