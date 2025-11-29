#include "raylib.h"
#include "raymath.h"
#include "stdio.h"
#include "Animais.hpp"
#include "Fila.hpp"
#include "Lista.hpp"
#include "Pedidos.hpp"
#include "Loja_Animais.hpp"
#include "Inimigos.hpp" 
#include "Aprimoramento.hpp"
#include <string>
#define vel 10.0f
#define MAX_ENEMIES 100
#define MAX_BULLETS 50
#define INTERVALO_PEDIDO 10.0f
#define velTiro 10.0f
#define freqTiro 1.2f


int framesCounter = 0;


int pedidosConcluidos = 18;

float timerGerarPedidos = 0.0f;
// Varáveis de inimigos,tiros
float spawnTimer = 0;
int enemiesPerWave = 3;
float timeBetweenWaves = 5.0f;
float fireTimer = 0;
float fireRate = 0.8f;

typedef enum GameScreen { LOGO = 0, TITLE, CREDITS, SETTINGS, GAMEPLAY, PAUSE} GameScreen;

typedef struct {
    int life;
    float money;
    lista recursos;
} Jogador;
Jogador jogador;

void InicializarAnimal(Animal *a, TipoAnimal tipo, Vector2 posInicial);


int main() {
    InitWindow(0, 0, "Legends Farm");
    Texture2D logo = LoadTexture("resources/logo.png");
    Texture2D baconsprite = LoadTexture("sprites/bacon.png");
    Texture2D lasprite = LoadTexture("sprites/la.png");
    Texture2D leitesprite = LoadTexture("sprites/leite.png");
    Texture2D ovosprite = LoadTexture("sprites/ovo.png");
    Texture2D galinhasprite = LoadTexture("sprites/galinha.png");
    Texture2D galinheirosprite = LoadTexture("sprites/galinheirofrente.png");
    Texture2D ovelhasprite = LoadTexture("sprites/ovelha.png");
    Texture2D porcosprite = LoadTexture("sprites/porco.png");
    Texture2D vacasprite = LoadTexture("sprites/vaca.png");
    Texture2D mapaTexture = LoadTexture("sprites/mapa.png");
    GameScreen currentScreen = LOGO;
    Enemy enemies[MAX_ENEMIES];
    Bullet bullets[MAX_BULLETS];
    Animal galinha[MAX_ANIMALS];
    Animal vacas[MAX_ANIMALS];
    Animal porcos[MAX_ANIMALS];
    Animal ovelhas[MAX_ANIMALS];
    Boss boss;
    skinVaca = {vacasprite, "VACA", precoVaca, 0, true};
    skinGalinha = {galinhasprite, "GALINHA", precoGalinha, 0, true};
    skinPorco = {porcosprite, "PORCO", precoPorco, 0, true};
    skinOvelha = {ovelhasprite, "OVELHA", precoOvelha, 0, true};
    bool bossSpawned =false;



    SetTargetFPS(60);
    jogador  = {1000,1000};
    criarL(jogador.recursos);
    fila filaDePedidos;
    criarF(filaDePedidos);
    float LarguraTela = GetScreenWidth();
    float AlturaTela = GetScreenHeight();
// Front-End (Menus Principais da Gameplay)
    float painelLateralLargura = LarguraTela*0.3;
    Rectangle painelLateral = {LarguraTela - painelLateralLargura, 0, painelLateralLargura, AlturaTela};
    float painelMeioLargura = 800;
    float painelMeioAltura = 200;

    float quadradosLargura = 120;
    Rectangle QuadradoPainelLateral1 = {LarguraTela - painelLateralLargura+ 10, 0,(painelLateralLargura-20)/4,(painelLateralLargura-20)/5};  
    Rectangle QuadradoPainelLateral2 = {LarguraTela - painelLateralLargura+ 10 + QuadradoPainelLateral1.width, 0, (painelLateralLargura-20)/4, (painelLateralLargura-20)/5};
    Rectangle QuadradoPainelLateral3 = {LarguraTela - painelLateralLargura+ 10 + QuadradoPainelLateral1.width*2, 0, (painelLateralLargura-20)/4, (painelLateralLargura-20)/5};
    Rectangle QuadradoPainelLateral4 = {LarguraTela - painelLateralLargura+ 10 + QuadradoPainelLateral1.width*3, 0, (painelLateralLargura-20)/4, (painelLateralLargura-20)/5};

    //Menu Recursos (REMOVIDO)
    //Tela Pedidos
    bool Pedidos = false;
    //Tela Skins
    bool animais = false;
    //Tela Aprimoramento
    bool Aprimoramento = false;
    //Tela Menu
    bool Menu = false;
// Mapa Tamanho
    int mapaLargura = 2000;
    int mapaAltura = 2000;
    Rectangle bounds = {0, 0,mapaLargura ,mapaAltura};
    // Locais do Mapa
        Rectangle Galinheiro ={mapaLargura/5,mapaAltura-mapaAltura/5, 500, 400 };
        Rectangle GalinheiroCima ={mapaLargura/5,mapaAltura-mapaAltura/5 -(350*4/5), 340, 350 };
        Rectangle Curral ={mapaLargura/5*3,mapaAltura-mapaAltura/5, 500, 400 };
        Rectangle Chiqueiro ={mapaLargura/5,0, 500, 400 };
        Rectangle CampodasOvelhas ={mapaLargura/5*3,0, 500, 400 };
// Jogador tamanho e posição inicial
    float radius = 20.0f;
    Vector2 pos = {bounds.width / 2.0f, bounds.height / 2.0f};
// Camera config de inicialização
    Camera2D camera = {0};
    camera.offset   = (Vector2){LarguraTela*0.35, (AlturaTela) / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom     = 1.0f;
//Inicialização dos tamanhos/posições dos botões na tela Logo 
    int btnWidth = 250;
    int btnHeight = 60;
    int centerX = LarguraTela / 2 - btnWidth / 2;
    int startY = AlturaTela / 2 - 100;
    Rectangle btnJogar = { centerX, startY, btnWidth, btnHeight };
    Rectangle btnCreditos = { centerX, startY + 80, btnWidth, btnHeight };
    Rectangle btnConfig = { centerX, startY + 160, btnWidth, btnHeight };
    Rectangle btnVoltar = { LarguraTela/2 - 100, AlturaTela/2 + 120, 200, 50 };
    // ---------------------------------------------------

    //Inicialização de elementos
    InicializarAprimoramentos(galinheirosprite, vacasprite, porcosprite, ovelhasprite);
    InicializarInimigos(enemies);
    InicializarBalas(bullets);
    InicializarBoss(boss);
    InicializarAnimaisComprados(galinha, vacas, porcos, ovelhas,
                           GalinhasCompradas, VacasCompradas, PorcosCompradas, OvelhasCompradas,
                           Galinheiro, Curral, Chiqueiro, CampodasOvelhas);

//  TUDO ANTES DESSE COMENTÁRIO É O SETUP

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
//Controle de lógica para entrada de dados em cada tela e Comportamento(botões,teclas,inimigos,balas,...)
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
                if(!Menu){
                currentScreen = TITLE;
                }else{
                    currentScreen = GAMEPLAY;
                    Menu =false;
                }
                }
                if (IsKeyPressed(KEY_B)) {
                    currentScreen = GAMEPLAY;
                    Menu =false;
                }
            } break;

            case GAMEPLAY: {
                //movimentação do jogador
                Vector2 dir = {0, 0};
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) dir.x += 1;
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))  dir.x -= 1;
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))    dir.y -= 1;
                if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))  dir.y += 1;
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
                timerGerarPedidos += GetFrameTime();
                if (timerGerarPedidos >= INTERVALO_PEDIDO) {
                    timerGerarPedidos = 0.0f;
                    GerarNovoPedido(filaDePedidos);
                }
                if (IsKeyPressed(KEY_E)) {
                    if (!vaziaF(filaDePedidos)) {
                        lista& primeiroPedido = filaDePedidos.header->dir->info;
                        RequisitosPedido requisitosPedido = ContarRequisitos(primeiroPedido);
                        RequisitosPedido inventarioJogador = ContarRequisitos(jogador.recursos);
                        if (PodeEntregar(inventarioJogador, requisitosPedido)) {
                            for (int i = 0; i < requisitosPedido.ovos; i++) {
                                retirarL(jogador.recursos, "ovo");
                                jogador.money += 10.0f;
                            }
                            for (int i = 0; i < requisitosPedido.leite; i++) {
                                retirarL(jogador.recursos, "leite");
                                jogador.money += 20.0f;
                            }
                            for (int i = 0; i < requisitosPedido.bacons; i++) {
                                retirarL(jogador.recursos, "bacon");
                                jogador.money += 40.0f;
                            }
                            for (int i = 0; i < requisitosPedido.la; i++) {
                                retirarL(jogador.recursos, "la");
                                jogador.money += 30.0f;
                            }
                            lista pedidoEntregue; 
                            retirarF(filaDePedidos, pedidoEntregue);
                            destruirL(pedidoEntregue);
                            
                            // --- ALTERAÇÃO 2: Incrementa o contador ---
                            pedidosConcluidos++;
                            // ------------------------------------------
                        }
                    }
                }
                //Comportamento Galinha,vaca,ovelha,porco
                        AtualizarTodosAnimais(galinha, vacas, porcos, ovelhas,
                     GalinhasCompradas, VacasCompradas, PorcosCompradas, OvelhasCompradas,
                     Galinheiro, Curral, Chiqueiro, CampodasOvelhas,
                     pos, enemies, MAX_ENEMIES, jogador.recursos);
                // ---------------------------------------------------

                // 🔥 INIMIGOS E TIROS
                //Set do inimigo
                SpawnarOndaInimigos(enemies, pos, enemiesPerWave, spawnTimer, timeBetweenWaves);
                AtualizarInimigos(enemies, pos);
                
                // --- LÓGICA DO BOSS ---
                // Spawnar quando atingir 20 pedidos
                SpawnarBoss(boss, mapaLargura, mapaAltura, bossSpawned, pedidosConcluidos);
                AtualizarBoss(boss, pos, bullets);
                // ----------------------

                AtualizarAprimoramentos(GalinhasCompradas, VacasCompradas, PorcosCompradas, OvelhasCompradas);

                // ATIRAR NO CURSOR (Automático)
                fireTimer += GetFrameTime()*freqTiro;
                if (fireTimer >= fireRate) {
                    fireTimer = 0;
                    
                    // Pega posição do mouse em coordenadas do MUNDO (por causa da câmera)
                    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

                    for (int b = 0; b < MAX_BULLETS; b++) {
                        if (!bullets[b].active) {
                            bullets[b].active = true;
                            bullets[b].pos = pos;
                            // Calcula direção: Destino (Mouse) - Origem (Player)
                            bullets[b].dir = Vector2Normalize(Vector2Subtract(mouseWorldPos, pos));
                            bullets[b].speed = velTiro;
                            break;
                        }
                    }
                }
                
                // Movimentar bala e verificar colisão
                for (int b = 0; b < MAX_BULLETS; b++) {
                    if (bullets[b].active) {
                        bullets[b].pos = Vector2Add(bullets[b].pos, Vector2Scale(bullets[b].dir, bullets[b].speed));

                        // Colisão com inimigos normais
                        for (int i = 0; i < MAX_ENEMIES; i++) {
                            if (enemies[i].active && Vector2Distance(bullets[b].pos, enemies[i].pos) < 15) {
                                bullets[b].active = false;
                                enemies[i].active = false;
                                break;
                            }
                        }
                        
                        // --- COLISÃO COM O BOSS ---
                        if (boss.active && Vector2Distance(bullets[b].pos, boss.pos) < boss.radius) {
                            bullets[b].active = false;
                            boss.life -= 1; 
                            if (boss.life <= 0) {
                                boss.active = false;
                                // Boss derrotado
                            }
                        }
                        // ---------------------------

                        if (Vector2Distance(pos, bullets[b].pos) > 800) bullets[b].active = false;
                    }
                }
                // ---------------------------------------------------

                //Lógica do Menu Lateral
            } break;

            case PAUSE: {
                if (IsKeyPressed(KEY_P)) {
                    currentScreen = GAMEPLAY;
                }
            } break;

            default: break;
        }
//Frame
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
               
                    float escala = 1.18f;
                    Rectangle destRect = {
                        bounds.x - (bounds.width * escala - bounds.width) / 2.0f,  // Centraliza no eixo X
                        bounds.y - (bounds.height * escala - bounds.height) / 2.0f, // Centraliza no eixo Y
                        bounds.width * escala, 
                        bounds.height * escala
                    };
                    DrawTexturePro(mapaTexture, 
                                  (Rectangle){0, 0, (float)mapaTexture.width, (float)mapaTexture.height},
                                  destRect,
                                  (Vector2){0, 0}, 0.0f, WHITE);
                    DrawRectangleRec(Galinheiro, ORANGE);                   
                    DrawRectangleRec(Curral, BLUE);
                    DrawRectangleRec(Chiqueiro, BROWN);
                    DrawRectangleRec(CampodasOvelhas, GREEN);
                    DrawCircleV(pos, radius, RED);
                    float escalag = 0.8f;
                    Rectangle destRectG = {
                        GalinheiroCima.x - (GalinheiroCima.width * escalag - GalinheiroCima.width) / 2.0f,  // Centraliza no eixo X
                        GalinheiroCima.y - (GalinheiroCima.height * escalag - GalinheiroCima.height) / 2.0f, // Centraliza no eixo Y
                        GalinheiroCima.width * escalag, 
                        GalinheiroCima.height * escalag
                    };
                    DrawTexturePro(galinheirosprite, 
                                  (Rectangle){0, 0, (float)galinheirosprite.width, (float)galinheirosprite.height},
                                  destRectG,
                                  (Vector2){0, 0}, 0.0f, WHITE);

                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        if (enemies[i].active) DrawCircleV(enemies[i].pos, 20, DARKPURPLE);
                    }
                    
                    // --- DESENHO DO BOSS ---
                    if (boss.active) {
                        DrawCircleV(boss.pos, boss.radius, MAROON);
                        DrawText(TextFormat("%d", boss.life), boss.pos.x - 10, boss.pos.y - 10, 20, WHITE);
                    }
                    // -----------------------
                    
                    for (int b = 0; b < MAX_BULLETS; b++) {
                        if (bullets[b].active) DrawCircleV(bullets[b].pos, 10, RED);
                    }

                    for (int i = 0; i < MAX_ANIMALS; i++) {
                        if (galinha[i].active){
                            Rectangle src = {0, 0, (float)galinhasprite.width, (float)galinhasprite.height};
                            float scale = 0.08f;
                            float w = galinhasprite.width * scale;
                            float h = galinhasprite.height * scale;
                            // canto superior esquerdo
                            Rectangle dest = {
                                galinha[i].pos.x - w/2.0f,
                                galinha[i].pos.y - h/2.0f,
                                w,
                                h
                            };
                            // pivot no centro do sprite renderizado
                            Vector2 origin = {w/32.0f, h/32.0f};
                            DrawTexturePro(galinhasprite, src, dest, origin, 0.0f, WHITE);
                            // debug
                            //DrawCircleV(galinha[i].pos, galinha[i].tamanho, galinha[i].cor);
                        } 
                    }
                    for (int i = 0; i < MAX_ANIMALS; i++) {
                        if (vacas[i].active){

                            Rectangle src = {0, 0, (float)vacasprite.width, (float)vacasprite.height};
                            float scale = 0.15f;
                            float w = vacasprite.width * scale;
                            float h = vacasprite.height * scale;
                            // canto superior esquerdo
                            Rectangle dest = {
                                vacas[i].pos.x - w/2.0f,
                                vacas[i].pos.y - h/2.0f,
                                w,
                                h
                            };
                            // pivot no centro do sprite renderizado
                            Vector2 origin = {w/32.0f, h/32.0f};
                            DrawTexturePro(vacasprite, src, dest, origin, 0.0f, WHITE);
                        
                            //DrawCircleV(vacas[i].pos, vacas[i].tamanho, vacas[i].cor);
                        } 
                    }
                    for (int i = 0; i < MAX_ANIMALS; i++) {
                        if (porcos[i].active){

                            Rectangle src = {0, 0, (float)porcosprite.width, (float)porcosprite.height};
                            float scale = 0.1f;
                            float w = porcosprite.width * scale;
                            float h = porcosprite.height * scale;
                            // canto superior esquerdo
                            Rectangle dest = {
                                porcos[i].pos.x - w/2.0f,
                                porcos[i].pos.y - h/2.0f,
                                w,
                                h
                            };
                            // pivot no centro do sprite renderizado
                            Vector2 origin = {w/32.0f, h/32.0f};
                            DrawTexturePro(porcosprite, src, dest, origin, 0.0f, WHITE);
                        
                            //DrawCircleV(porcos[i].pos,porcos[i].tamanho, porcos[i].cor);
                        } 
                    }
                    for (int i = 0; i < MAX_ANIMALS; i++) {
                        if (ovelhas[i].active){

                            Rectangle src = {0, 0, (float)ovelhasprite.width, (float)ovelhasprite.height};
                            float scale = 0.11f;
                            float w = ovelhasprite.width * scale;
                            float h = ovelhasprite.height * scale;
                            // canto superior esquerdo
                            Rectangle dest = {
                                ovelhas[i].pos.x - w/2.0f,
                                ovelhas[i].pos.y - h/2.0f,
                                w,
                                h
                            };
                            // pivot no centro do sprite renderizado
                            Vector2 origin = {w/32.0f, h/32.0f};
                            DrawTexturePro(ovelhasprite, src, dest, origin, 0.0f, WHITE);
                        
                            //DrawCircleV(ovelhas[i].pos,ovelhas[i].tamanho, ovelhas[i].cor);
                        } 
                    }

                EndMode2D();
            //Elementos de Menu Estático
            
                // --- ALTERAÇÃO 3: Desenhar painel de pedidos no topo esquerdo ---
                DrawRectangle(10, 10, 220, 50, (Color){0, 0, 0, 150}); // Fundo semi-transparente
                DrawText(TextFormat("Pedidos: %d / 20", pedidosConcluidos), 20, 25, 20, WHITE);
                // ---------------------------------------------------------------

               // Painel fixo à direita (fora do modo 2D)

                Color QuadradohoverColor = (Color){75, 175, 175, 240};
                Color QuadradonormalColor = (Color){50, 150, 150, 255};
                // FUNDO DO PAINEL LATERAL (sempre visível)
                DrawRectangleRec(painelLateral, (Color){50, 50, 50, 255});
                // BOTÕES DO MENU SUPERIOR (sempre visíveis)
                DrawRectangleRec(QuadradoPainelLateral1, CheckCollisionPointRec(mousePoint, QuadradoPainelLateral1) ? QuadradohoverColor : QuadradonormalColor);
                DrawText("Pedidos", QuadradoPainelLateral1.x + QuadradoPainelLateral1.width*0.13, 20, 20, WHITE);

                DrawRectangleRec(QuadradoPainelLateral2, CheckCollisionPointRec(mousePoint, QuadradoPainelLateral2) ? QuadradohoverColor : QuadradonormalColor);
                DrawText("Animais", QuadradoPainelLateral2.x + QuadradoPainelLateral2.width*0.17, 20, 20, WHITE);

                DrawRectangleRec(QuadradoPainelLateral3, CheckCollisionPointRec(mousePoint, QuadradoPainelLateral3) ? QuadradohoverColor : QuadradonormalColor);
                DrawText("Melhorias", QuadradoPainelLateral3.x + QuadradoPainelLateral3.width*0.01, 20, 20, WHITE);

                DrawRectangleRec(QuadradoPainelLateral4, CheckCollisionPointRec(mousePoint, QuadradoPainelLateral4) ? QuadradohoverColor : QuadradonormalColor);
                DrawText("Menu", QuadradoPainelLateral4.x + QuadradoPainelLateral4.width*0.25, 20, 20, WHITE);

                // Lógica dos botões do menu
                if (CheckCollisionPointRec(mousePoint,QuadradoPainelLateral1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                    Pedidos=true, Aprimoramento=false, animais=false, Menu=false;
                if (CheckCollisionPointRec(mousePoint,QuadradoPainelLateral2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                    Pedidos=false, Aprimoramento=false, animais=true, Menu=false;
                if (CheckCollisionPointRec(mousePoint,QuadradoPainelLateral3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                    Pedidos=false, Aprimoramento=true, animais=false, Menu=false;
                if (CheckCollisionPointRec(mousePoint,QuadradoPainelLateral4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                    Pedidos=false, Aprimoramento=false, animais=false, Menu=true;

                // CONTEÚDO DAS ABAS (começa depois dos botões)
                float alturaConteudo = painelLateral.height - QuadradoPainelLateral1.height;
                Rectangle areaConteudo = {
                    painelLateral.x,
                    painelLateral.y + QuadradoPainelLateral1.height,
                    painelLateral.width,
                    alturaConteudo
                };

                if (Pedidos) {
                    DrawPedidos(filaDePedidos, areaConteudo, QuadradoPainelLateral1);
                }

                if(Menu){
                    currentScreen = SETTINGS; 
                }

                if(animais){
                    // Fundo da aba animais
                    DrawRectangleRec(areaConteudo, (Color){30, 30, 40, 255});
                    DrawSkinsScreen(areaConteudo, painelLateralLargura, mousePoint, 
                                   VacasCompradas, GalinhasCompradas, PorcosCompradas, OvelhasCompradas,
                                   jogador.money, vacas, galinha, porcos, ovelhas,
                                   Curral, Galinheiro, Chiqueiro, CampodasOvelhas);
                    
                    ProcessarCompraLoja(areaConteudo, painelLateralLargura, mousePoint,
                                       jogador.money,
                                       VacasCompradas, GalinhasCompradas, PorcosCompradas, OvelhasCompradas,
                                       vacas, galinha, porcos, ovelhas,
                                       Curral, Galinheiro, Chiqueiro, CampodasOvelhas);
                }

if(Aprimoramento){
    // Fundo da aba aprimoramentos
    DrawRectangleRec(areaConteudo, (Color){30, 40, 30, 255});
    DrawAprimoramentosScreen(areaConteudo, painelLateralLargura, mousePoint, jogador.money);
    ProcessarCompraAprimoramentos(areaConteudo, painelLateralLargura, mousePoint, jogador.money);
}

                // ------------------- HUD RECURSOS (NOVA TABELA) -------------------
                // Fundo semi-transparente
                DrawRectangle(10, AlturaTela - 230, 200, 220, (Color){0, 0, 0, 150});
                
                RequisitosPedido contagem = ContarRequisitos(jogador.recursos);
                float hudX = 20;
                float hudY = AlturaTela - 210;
                float espacamento = 40;
                float iconW = 30;

                // Dinheiro
                DrawText(TextFormat("R$: %.0f", jogador.money), hudX, hudY, 25, GREEN);
                hudY += espacamento;

                // Ovos
                DrawTexturePro(ovosprite, (Rectangle){0,0,(float)ovosprite.width,(float)ovosprite.height}, (Rectangle){hudX, hudY, iconW, iconW}, (Vector2){0,0}, 0, WHITE);
                DrawText(TextFormat("x %d", contagem.ovos), hudX + 40, hudY + 5, 25, WHITE);
                hudY += espacamento;

                // Leite
                DrawTexturePro(leitesprite, (Rectangle){0,0,(float)leitesprite.width,(float)leitesprite.height}, (Rectangle){hudX, hudY, iconW, iconW}, (Vector2){0,0}, 0, WHITE);
                DrawText(TextFormat("x %d", contagem.leite), hudX + 40, hudY + 5, 25, WHITE);
                hudY += espacamento;

                // Lã
                DrawTexturePro(lasprite, (Rectangle){0,0,(float)lasprite.width,(float)lasprite.height}, (Rectangle){hudX, hudY, iconW, iconW}, (Vector2){0,0}, 0, WHITE);
                DrawText(TextFormat("x %d", contagem.la), hudX + 40, hudY + 5, 25, WHITE);
                hudY += espacamento;

                // Bacon
                DrawTexturePro(baconsprite, (Rectangle){0,0,(float)baconsprite.width,(float)baconsprite.height}, (Rectangle){hudX, hudY, iconW, iconW}, (Vector2){0,0}, 0, WHITE);
                DrawText(TextFormat("x %d", contagem.bacons), hudX + 40, hudY + 5, 25, WHITE);
                // ------------------------------------------------------------------

                //cursor    
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

    destruirL(jogador.recursos);
    destruirF(filaDePedidos);
    UnloadTexture(logo);
    CloseWindow();
    return 0;
}