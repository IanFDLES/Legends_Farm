#include "raylib.h"
#include "raymath.h"
#include "stdio.h"
#include "Animais.hpp"
#include "Fila.hpp"
#include "Lista.hpp"
#include "Pedidos.hpp"
#include <string>
#define vel 5.0f
#define MAX_ENEMIES 100
#define MAX_BULLETS 50
#define MAX_ANIMALS 10
#define INTERVALO_PEDIDO 10.0f
#define VEL_PROD (1.0f / 60.0f)

int framesCounter = 0;
float timerGerarPedidos = 0.0f;
// Varáveis de inimigos,tiros,galinhas

float spawnTimer = 0;
int enemiesPerWave = 3;
float timeBetweenWaves = 5.0f;
float fireTimer = 0;
float fireRate = 0.8f;
float GalinhasCompradas = 4;
float VacasCompradas = 4;
float PorcosCompradas = 4;
float OvelhasCompradas = 4;
//
typedef enum GameScreen { LOGO = 0, TITLE, CREDITS, SETTINGS, GAMEPLAY, PAUSE} GameScreen;

typedef struct {
    Vector2 pos;
    float speed;
    bool active;
    int damage;
} Enemy;

typedef struct {
    Vector2 pos;
    Vector2 dir;
    float speed;
    bool active;
} Bullet;

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
    Texture2D lasprite = LoadTexture("sprites/lã.png");
    Texture2D leitesprite = LoadTexture("sprites/leite.png");
    Texture2D ovosprite = LoadTexture("sprites/ovo.png");
    Texture2D galinhasprite = LoadTexture("sprites/galinha.png");
    GameScreen currentScreen = LOGO;
    Enemy enemies[MAX_ENEMIES];
Bullet bullets[MAX_BULLETS];
Animal galinha[MAX_ANIMALS];
Animal vacas[MAX_ANIMALS];
Animal porcos[MAX_ANIMALS];
Animal ovelhas[MAX_ANIMALS];
    SetTargetFPS(60);
   jogador  = {1000,100};
   criarL(jogador.recursos);
   fila filaDePedidos;
   criarF(filaDePedidos);
   float LarguraTela = GetScreenWidth();
   float AlturaTela = GetScreenHeight();
// Front-End (Menus Principais da Gameplay)
    float painelLateralLargura = 600;
    Rectangle painelLateral = {LarguraTela - painelLateralLargura, 0, painelLateralLargura, AlturaTela};
    float painelMeioLargura = 800;
    float painelMeioAltura = 200;

    float quadradosLargura = 120;
    Rectangle QuadradoPainelLateral1 = {LarguraTela - painelLateralLargura+ 10, 0,(painelLateralLargura-20)/5,(painelLateralLargura-20)/5};  
    Rectangle QuadradoPainelLateral2 = {LarguraTela - painelLateralLargura+(painelLateralLargura-20)/5, 0, (painelLateralLargura-20)/5, (painelLateralLargura-20)/5};
    Rectangle QuadradoPainelLateral3 = {LarguraTela - painelLateralLargura +(painelLateralLargura-20)/5*2, 0, (painelLateralLargura-20)/5, (painelLateralLargura-20)/5};
    Rectangle QuadradoPainelLateral4 = {LarguraTela - painelLateralLargura+(painelLateralLargura-20)/5*3, 0, (painelLateralLargura-20)/5, (painelLateralLargura-20)/5};
    Rectangle QuadradoPainelLateral5 = {LarguraTela - painelLateralLargura+(painelLateralLargura-20)/5*4, 0, (painelLateralLargura-20)/5, (painelLateralLargura-20)/5};

    //Menu Recursos
    bool recursos = false;
    Rectangle LeitePainelLateral = {LarguraTela - painelLateralLargura+ 10, ((painelLateralLargura-20)/5)+10,(painelLateralLargura)/5*4,(painelLateralLargura-20)/4}; 
    Rectangle OvoPainelLateral = {LarguraTela - painelLateralLargura+ 10, ((painelLateralLargura-20)/5)+20+(painelLateralLargura-20)/4,(painelLateralLargura)/5*4,(painelLateralLargura-20)/4};
    Rectangle BaconPainelLateral = {LarguraTela - painelLateralLargura+ 10, ((painelLateralLargura-20)/5)+30+(painelLateralLargura-20)/4*2,(painelLateralLargura)/5*4,(painelLateralLargura-20)/4};  
    Rectangle LaPainelLateral = {LarguraTela - painelLateralLargura+ 10, ((painelLateralLargura-20)/5)+40+(painelLateralLargura-20)/4*3,(painelLateralLargura)/5*4,(painelLateralLargura-20)/4}; 
    //Tela Pedidos
    bool Pedidos = false;
    //Tela Skins
    bool skins = false;
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
        Rectangle Curral ={mapaLargura/5*3,mapaAltura-mapaAltura/5, 500, 400 };
        Rectangle Chiqueiro ={mapaLargura/5,0, 500, 400 };
        Rectangle CampodasOvelhas ={mapaLargura/5*3,0, 500, 400 };
// Jogador tamanho e posição inicial
    float radius = 20.0f;
    Vector2 pos = {bounds.width / 2.0f, bounds.height / 2.0f};
// Camera config de inicialização
    Camera2D camera = {0};
    camera.offset   = (Vector2){(painelLateralLargura + painelMeioLargura)/2, (AlturaTela-painelMeioAltura) / 2.0f};
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

    //Alocação anti-dinâmica 🫠
    for (int i = 0; i < MAX_ENEMIES; i++) enemies[i].active = false;
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
    for (int i = 0; i < MAX_ANIMALS; i++) galinha[i].active = false,galinha[i].processo=0;
    for (int i = 0; i < GalinhasCompradas; i++) {
        InicializarAnimal(&galinha[i],TipoAnimal (2),(Vector2){Galinheiro.x + GetRandomValue(0,Galinheiro.width),Galinheiro.y + GetRandomValue(0,Galinheiro.height)});
    }
    for (int i = 0; i < MAX_ANIMALS; i++) vacas[i].active = false,vacas[i].processo=0;
    for (int i = 0; i < VacasCompradas; i++) {
        InicializarAnimal(&vacas[i],TipoAnimal (2),(Vector2){Curral.x + GetRandomValue(0,Curral.width),Curral.y + GetRandomValue(0,Curral.height)});
    }
    for (int i = 0; i < MAX_ANIMALS; i++) porcos[i].active = false,porcos[i].processo=0;
    for (int i = 0; i < PorcosCompradas; i++) {
        InicializarAnimal(&porcos[i],TipoAnimal (2),(Vector2){Chiqueiro.x + GetRandomValue(0,Chiqueiro.width),Chiqueiro.y + GetRandomValue(0,Chiqueiro.height)});
    } 
    for (int i = 0; i < MAX_ANIMALS; i++) ovelhas[i].active = false,ovelhas[i].processo=0;
    for (int i = 0; i < OvelhasCompradas; i++) {
        InicializarAnimal(&ovelhas[i],TipoAnimal (2),(Vector2){CampodasOvelhas.x + GetRandomValue(0,CampodasOvelhas.width),CampodasOvelhas.y + GetRandomValue(0,CampodasOvelhas.height)});
    }      
    // ---------------------------------------------------


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
                            for (int i = 0; i < requisitosPedido.ovos; i++) retirarL(jogador.recursos, "ovo");
                            for (int i = 0; i < requisitosPedido.leite; i++) retirarL(jogador.recursos, "leite");
                            for (int i = 0; i < requisitosPedido.bacons; i++) retirarL(jogador.recursos, "bacon");
                            for (int i = 0; i < requisitosPedido.la; i++) retirarL(jogador.recursos, "la");
                            jogador.money += 100.0f; 
                            lista pedidoEntregue; 
                            retirarF(filaDePedidos, pedidoEntregue);
                            destruirL(pedidoEntregue);
                        }
                    }
                }
                //Comportamento Galinha
                        for (int j = 0; j < GalinhasCompradas; j++) {
                            if (!galinha[j].active) {
                                galinha[j].active = true;
                                break;
                            }
                        }
                        for (int i = 0; i < GalinhasCompradas; i++) {
                            if (!galinha[i].active) continue;
                                // 1. Gera um destino aleatório dentro do galinheiro, se ainda não tiver direção
                                if (Vector2Length(galinha[i].dir) == 0 || GetRandomValue(0, 100) < 2) {
                                    float destinoX = GetRandomValue(Galinheiro.x, Galinheiro.x + Galinheiro.width);
                                    float destinoY = GetRandomValue(Galinheiro.y, Galinheiro.y + Galinheiro.height);
                                    Vector2 destino = (Vector2){destinoX, destinoY};
                                    galinha[i].dir = Vector2Normalize(Vector2Subtract(destino, galinha[i].pos));
                                }
                                // 2. Move a galinha em direção ao destino
                                galinha[i].pos = Vector2Add(
                                    galinha[i].pos,
                                    Vector2Scale(galinha[i].dir, galinha[i].speed * GetFrameTime())
                                );
                                // 3. Mantém dentro dos limites do galinheiro
                                if (galinha[i].pos.x < Galinheiro.x) galinha[i].pos.x = Galinheiro.x;
                                if (galinha[i].pos.x > Galinheiro.x + Galinheiro.width) galinha[i].pos.x = Galinheiro.x + Galinheiro.width;
                                if (galinha[i].pos.y < Galinheiro.y) galinha[i].pos.y = Galinheiro.y;
                                if (galinha[i].pos.y > Galinheiro.y + Galinheiro.height) galinha[i].pos.y = Galinheiro.y + Galinheiro.height;
                                // 4. Verifica colisão com inimigos
                                for (int i = 0; i < MAX_ANIMALS; i++) {
                                    if (!galinha[i].active) continue;
                                
                                    for (int e = 0; e < MAX_ENEMIES; e++) {
                                        if (!enemies[e].active) continue;
                                    
                                        if (Vector2Distance(galinha[i].pos, enemies[e].pos) < 20) {
                                            galinha[i].life -= enemies[e].damage * GetFrameTime();
                                            if (galinha[i].life <= 0) {
                                                galinha[i].active = false;
                                                GalinhasCompradas--;
                                            }
                                        }
                                    }
                                }
                                
                                // Produz ovo
                                galinha[i].processo += VEL_PROD*galinha[i].VelocidadeProducao;
                                    if (Vector2Distance(galinha[i].pos,pos) < 200 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                if (galinha[i].processo >= 40)
                                {
                                    inserirL(jogador.recursos, "ovo");
                                    galinha[i].processo = 0;
                                    }
                                
                                }
                            }
                // ---------------------------------------------------
                //Comportamento Vaca
                        for (int j = 0; j < VacasCompradas; j++) {
                            if (!vacas[j].active) {
                                vacas[j].active = true;
                                break;
                            }
                        }
                        for (int i = 0; i < VacasCompradas; i++) {
                            if (!vacas[i].active) continue; 
                                // 1. Gera um destino aleatório dentro do galinheiro, se ainda não tiver direção
                                if (Vector2Length(vacas[i].dir) == 0 || GetRandomValue(0, 100) < 2) {
                                    float destinoX = GetRandomValue(Curral.x, Curral.x + Curral.width);
                                    float destinoY = GetRandomValue(Curral.y, Curral.y + Curral.height);
                                    Vector2 destino = (Vector2){destinoX, destinoY};
                                    vacas[i].dir = Vector2Normalize(Vector2Subtract(destino, vacas[i].pos));
                                }
                                // 2. Move a vacas em direção ao destino
                                vacas[i].pos = Vector2Add(
                                    vacas[i].pos,
                                    Vector2Scale(vacas[i].dir, vacas[i].speed * GetFrameTime())
                                );
                                // 3. Mantém dentro dos limites do galinheiro
                                if (vacas[i].pos.x < Curral.x) vacas[i].pos.x = Curral.x;
                                if (vacas[i].pos.x > Curral.x + Curral.width) vacas[i].pos.x = Curral.x + Curral.width;
                                if (vacas[i].pos.y < Curral.y) vacas[i].pos.y = Curral.y;
                                if (vacas[i].pos.y > Curral.y + Curral.height) vacas[i].pos.y = Curral.y + Curral.height;
                                // 4. Verifica colisão com inimigos
                                for (int i = 0; i < MAX_ANIMALS; i++) {
                                    if (!vacas[i].active) continue;
                                
                                    for (int e = 0; e < MAX_ENEMIES; e++) {
                                        if (!enemies[e].active) continue;
                                    
                                        if (Vector2Distance(vacas[i].pos, enemies[e].pos) < 20) {
                                            vacas[i].life -= enemies[e].damage * GetFrameTime();
                                            if (vacas[i].life <= 0) {
                                                vacas[i].active = false;
                                                VacasCompradas--;
                                            }
                                        }
                                    }
                                }
                                // Produz leite
                                vacas[i].processo += VEL_PROD*vacas[i].VelocidadeProducao;
                                if ( Vector2Distance(vacas[i].pos,pos) < 200 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                if (vacas[i].processo >= 120)
                                { 
                                    inserirL(jogador.recursos, "leite");
                                    vacas[i].processo = 0;
                                    }
                                }
                            }
                // ---------------------------------------------------
                //Comportamento Porco
                        for (int i = 0; i < PorcosCompradas; i++) {
                            if (!porcos[i].active) continue;
                                // 1. Gera um destino aleatório dentro do galinheiro, se ainda não tiver direção
                                if (Vector2Length(porcos[i].dir) == 0 || GetRandomValue(0, 100) < 2) {
                                    float destinoX = GetRandomValue(Chiqueiro.x, Chiqueiro.x + Chiqueiro.width);
                                    float destinoY = GetRandomValue(Chiqueiro.y,Chiqueiro.y + Chiqueiro.height);
                                    Vector2 destino = (Vector2){destinoX, destinoY};
                                    porcos[i].dir = Vector2Normalize(Vector2Subtract(destino, porcos[i].pos));
                                }
                                // 2. Move a galinha em direção ao destino
                                porcos[i].pos = Vector2Add(
                                    porcos[i].pos,
                                    Vector2Scale(porcos[i].dir, porcos[i].speed * GetFrameTime())
                                );
                                // 3. Mantém dentro dos limites do galinheiro
                                if (porcos[i].pos.x < Chiqueiro.x) porcos[i].pos.x = Chiqueiro.x;
                                if (porcos[i].pos.x > Chiqueiro.x + Chiqueiro.width) porcos[i].pos.x = Chiqueiro.x + Chiqueiro.width;
                                if (porcos[i].pos.y < Chiqueiro.y) porcos[i].pos.y = Chiqueiro.y;
                                if (porcos[i].pos.y > Chiqueiro.y + Chiqueiro.height) porcos[i].pos.y = Chiqueiro.y + Chiqueiro.height;
                                // 4. Verifica colisão com inimigos
                                for (int i = 0; i < MAX_ANIMALS; i++) {
                                    if (!porcos[i].active) continue;
                                
                                    for (int e = 0; e < MAX_ENEMIES; e++) {
                                        if (!enemies[e].active) continue;
                                    
                                        if (Vector2Distance(porcos[i].pos, enemies[e].pos) < 20) {
                                            porcos[i].life -= enemies[e].damage * GetFrameTime();
                                            if (porcos[i].life <= 0) {
                                                porcos[i].active = false;
                                                PorcosCompradas--;
                                            }
                                        }
                                    }
                                }
                                // Produz Bacon(abate)
                                porcos[i].processo += VEL_PROD*porcos[i].VelocidadeProducao;
                                if ( Vector2Distance(porcos[i].pos,pos) <200 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                if (porcos[i].processo >= 140)
                                {
                                    for (int i = 0; i < 3; i++) inserirL(jogador.recursos, "bacon");
                                    porcos[i].processo = 0;
                                    porcos[i].active =false;
                                    PorcosCompradas--;
                                    }
                                }
                            }
                // ---------------------------------------------------
                //Comportamento Ovelha
                        for (int j = 0; j < OvelhasCompradas; j++) {
                            if (!ovelhas[j].active) {
                                ovelhas[j].active = true;
                                break;
                            }
                        }
                        for (int i = 0; i < OvelhasCompradas; i++) {
                            if (!ovelhas[i].active) continue;
                                // 1. Gera um destino aleatório dentro do galinheiro, se ainda não tiver direção
                                if (Vector2Length(ovelhas[i].dir) == 0 || GetRandomValue(0, 100) < 2) {
                                    float destinoX = GetRandomValue(CampodasOvelhas.x, CampodasOvelhas.x + CampodasOvelhas.width);
                                    float destinoY = GetRandomValue(CampodasOvelhas.y, CampodasOvelhas.y + CampodasOvelhas.height);
                                    Vector2 destino = (Vector2){destinoX, destinoY};
                                    ovelhas[i].dir = Vector2Normalize(Vector2Subtract(destino, ovelhas[i].pos));
                                }
                                // 2. Move a galinha em direção ao destino
                                ovelhas[i].pos = Vector2Add(
                                    ovelhas[i].pos,
                                    Vector2Scale(ovelhas[i].dir,ovelhas[i].speed * GetFrameTime())
                                );
                                // 3. Mantém dentro dos limites do galinheiro
                                if (ovelhas[i].pos.x < CampodasOvelhas.x) ovelhas[i].pos.x = CampodasOvelhas.x;
                                if (ovelhas[i].pos.x > CampodasOvelhas.x + CampodasOvelhas.width) ovelhas[i].pos.x = CampodasOvelhas.x + CampodasOvelhas.width;
                                if (ovelhas[i].pos.y < CampodasOvelhas.y) ovelhas[i].pos.y = CampodasOvelhas.y;
                                if (ovelhas[i].pos.y > CampodasOvelhas.y + CampodasOvelhas.height) ovelhas[i].pos.y = CampodasOvelhas.y + CampodasOvelhas.height;
                                // 4. Verifica colisão com inimigos
                                for (int i = 0; i < MAX_ANIMALS; i++) {
                                    if (!ovelhas[i].active) continue;
                                
                                    for (int e = 0; e < MAX_ENEMIES; e++) {
                                        if (!enemies[e].active) continue;
                                    
                                        if (Vector2Distance(ovelhas[i].pos, enemies[e].pos) < 20) {
                                            ovelhas[i].life -= enemies[e].damage * GetFrameTime();
                                            if (ovelhas[i].life <= 0) {
                                                ovelhas[i].active = false;
                                                OvelhasCompradas--;
                                            }
                                        }
                                    }
                                }
                                // Produz ovo
                                ovelhas[i].processo += VEL_PROD*ovelhas[i].VelocidadeProducao;
                                if ( Vector2Distance(ovelhas[i].pos,pos) < 200 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                if (ovelhas[i].processo >= 40)
                                {   
                                    inserirL(jogador.recursos, "la");
                                    ovelhas[i].processo = 0;
                                }
                            }
                            }
                // ---------------------------------------------------

                // 🔥 INIMIGOS E TIROS (inserido sem alterar estrutura original)
                //Set do inimigo
                spawnTimer += GetFrameTime();
                if (spawnTimer >= timeBetweenWaves) {
                    spawnTimer = 0;
                    for (int i = 0; i < enemiesPerWave; i++) {
                        for (int j = 0; j < MAX_ENEMIES; j++) {
                            if (!enemies[j].active) {
                                enemies[j].active = true;
                                enemies[j].speed = 2.0f;
                                float angle = GetRandomValue(0, 360) * DEG2RAD;
                                float dist = 500.0f;
                                enemies[j].pos = (Vector2){ pos.x + cosf(angle)*dist, pos.y + sinf(angle)*dist };
                                break;
                            }
                        }
                    }
                    enemiesPerWave++;
                }
                //Movimentação do inimigo
                for (int i = 0; i < MAX_ENEMIES; i++) {
                    if (enemies[i].active) {
                        Vector2 dirE = Vector2Normalize(Vector2Subtract(pos, enemies[i].pos));
                        enemies[i].pos = Vector2Add(enemies[i].pos, Vector2Scale(dirE, enemies[i].speed));
                        if (Vector2Distance(pos, enemies[i].pos) < 20) {
                            enemies[i].active = false;
                        }
                    }
                }
                // Achar o inimigo mais próximo
                fireTimer += GetFrameTime();
                if (fireTimer >= fireRate) {
                    fireTimer = 0;
                    int target = -1;
                    float minDist = 99999.0f;
                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        if (enemies[i].active) {
                            float d = Vector2Distance(pos, enemies[i].pos);
                            if (d < minDist) {
                                minDist = d;
                                target = i;
                            }
                        }
                    }
                    // Set da bala em relação ao inimigo mais próximo
                    if (target != -1) {
                        for (int b = 0; b < MAX_BULLETS; b++) {
                            if (!bullets[b].active) {
                                bullets[b].active = true;
                                bullets[b].pos = pos;
                                bullets[b].dir = Vector2Normalize(Vector2Subtract(enemies[target].pos, pos));
                                bullets[b].speed = 8.0f;
                                break;
                            }
                        }
                    }
                }
                // Movimentar bala e verificar colisão
                for (int b = 0; b < MAX_BULLETS; b++) {
                    if (bullets[b].active) {
                        bullets[b].pos = Vector2Add(bullets[b].pos, Vector2Scale(bullets[b].dir, bullets[b].speed));

                        for (int i = 0; i < MAX_ENEMIES; i++) {
                            if (enemies[i].active && Vector2Distance(bullets[b].pos, enemies[i].pos) < 15) {
                                bullets[b].active = false;
                                enemies[i].active = false;
                                break;
                            }
                        }

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
                    DrawRectangleRec(bounds, LIGHTGRAY);
                    DrawRectangleRec(Galinheiro, ORANGE);
                    DrawRectangleRec(Curral, BLUE);
                    DrawRectangleRec(Chiqueiro, BROWN);
                    DrawRectangleRec(CampodasOvelhas, GREEN);
                    DrawCircleV(pos, radius, RED);

                    for (int i = 0; i < MAX_ENEMIES; i++) {
                        if (enemies[i].active) DrawCircleV(enemies[i].pos, 10, DARKPURPLE);
                    }
                    for (int b = 0; b < MAX_BULLETS; b++) {
                        if (bullets[b].active) DrawCircleV(bullets[b].pos, 5, RED);
                    }

                    for (int i = 0; i < MAX_ANIMALS; i++) {
                        if (galinha[i].active){
                            Rectangle src = {0, 0, galinhasprite.width, galinhasprite.height};
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
                            DrawCircleV(galinha[i].pos, galinha[i].tamanho, galinha[i].cor);
                        } 
                    }
                    for (int i = 0; i < MAX_ANIMALS; i++) {
                        if (vacas[i].active){
                        
                            DrawCircleV(vacas[i].pos, vacas[i].tamanho, vacas[i].cor);
                        } 
                    }
                    for (int i = 0; i < MAX_ANIMALS; i++) {
                        if (porcos[i].active){
                        
                            DrawCircleV(porcos[i].pos,porcos[i].tamanho, porcos[i].cor);
                        } 
                    }
                    for (int i = 0; i < MAX_ANIMALS; i++) {
                        if (ovelhas[i].active){
                        
                            DrawCircleV(ovelhas[i].pos,ovelhas[i].tamanho, ovelhas[i].cor);
                        } 
                    }

                EndMode2D();
            //Elementos de Menu Estático
               // Painel fixo à direita (fora do modo 2D)
                
                Color QuadradohoverColor = (Color){75, 175, 175,240};
                Color QuadradonormalColor = (Color){50, 150, 150,255};
                DrawRectangleRec(painelLateral, (Color){50, 50, 50,255});
                DrawRectangleRec(QuadradoPainelLateral1, CheckCollisionPointRec(mousePoint, QuadradoPainelLateral1) ? QuadradohoverColor : QuadradonormalColor);
                                DrawText("Pedidos", QuadradoPainelLateral1.x + 16, 20, 20, WHITE);
                DrawRectangleRec(QuadradoPainelLateral2, CheckCollisionPointRec(mousePoint, QuadradoPainelLateral2) ? QuadradohoverColor : QuadradonormalColor);
                DrawRectangleRec(QuadradoPainelLateral3, CheckCollisionPointRec(mousePoint, QuadradoPainelLateral3) ? QuadradohoverColor : QuadradonormalColor);
                DrawRectangleRec(QuadradoPainelLateral4, CheckCollisionPointRec(mousePoint, QuadradoPainelLateral4) ? QuadradohoverColor : QuadradonormalColor);
                                DrawText("Recursos", QuadradoPainelLateral4.x + 10, 20, 20, WHITE); 
                DrawRectangleRec(QuadradoPainelLateral5, CheckCollisionPointRec(mousePoint, QuadradoPainelLateral5) ? QuadradohoverColor : QuadradonormalColor);
                                DrawText("Menu", QuadradoPainelLateral5.x + 33, 20, 20, WHITE); 
                                if (CheckCollisionPointRec(mousePoint,QuadradoPainelLateral1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) Pedidos=true, Aprimoramento =false, skins =false, recursos= false, Menu=false;
                                if (CheckCollisionPointRec(mousePoint,QuadradoPainelLateral2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) Pedidos=false, Aprimoramento =true, skins =false, recursos= false, Menu=false;
                                if (CheckCollisionPointRec(mousePoint,QuadradoPainelLateral3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) Pedidos=false, Aprimoramento =false, skins =true, recursos= false, Menu=false;
                                if (CheckCollisionPointRec(mousePoint,QuadradoPainelLateral4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) Pedidos=false, Aprimoramento =false, skins =false, recursos= true, Menu=false;
                                if (CheckCollisionPointRec(mousePoint,QuadradoPainelLateral5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) Pedidos=false, Aprimoramento =false, skins =false, recursos= false, Menu=true;
                                if (Pedidos) DrawPedidos(filaDePedidos, painelLateral, QuadradoPainelLateral1);
                                if(recursos){
                                    RequisitosPedido inventarioCounts = ContarRequisitos(jogador.recursos);
                                    
                                    DrawRectangleRec(LeitePainelLateral, CheckCollisionPointRec(mousePoint, LeitePainelLateral) ? QuadradohoverColor : QuadradonormalColor);
                                                    DrawText(TextFormat("%d Litros", inventarioCounts.leite),  LeitePainelLateral.x + 10,LeitePainelLateral.y +10, 20, WHITE);
                                                    DrawText(TextFormat("%2.f", vacas[1].processo), LeitePainelLateral.x + 20,LeitePainelLateral.y +40, 20, WHITE);         
                                    DrawRectangleRec(OvoPainelLateral, CheckCollisionPointRec(mousePoint, OvoPainelLateral) ? QuadradohoverColor : QuadradonormalColor);
                                                    DrawText(TextFormat("%d Ovos", inventarioCounts.ovos), OvoPainelLateral.x + 10, OvoPainelLateral.y +10, 20, WHITE);
                                                    DrawText(TextFormat("%2.f", galinha[1].processo), OvoPainelLateral.x + 20,OvoPainelLateral.y +40, 20, WHITE); 
                                    DrawRectangleRec(BaconPainelLateral, CheckCollisionPointRec(mousePoint, BaconPainelLateral) ? QuadradohoverColor : QuadradonormalColor);
                                                    DrawText(TextFormat("%d Bacon" , inventarioCounts.bacons), BaconPainelLateral.x + 10, BaconPainelLateral.y +10, 20, WHITE);
                                                    DrawText(TextFormat("%2.f", porcos[1].processo), BaconPainelLateral.x + 20, BaconPainelLateral.y +40, 20, WHITE);
                                    DrawRectangleRec(LaPainelLateral, CheckCollisionPointRec(mousePoint, LaPainelLateral) ? QuadradohoverColor : QuadradonormalColor);
                                                    DrawText(TextFormat("%d La", inventarioCounts.la), LaPainelLateral.x + 10, LaPainelLateral.y +10, 20, WHITE);
                                                    DrawText(TextFormat("%2.f", ovelhas[1].processo), LaPainelLateral.x + 20, LaPainelLateral.y +40, 20, WHITE);
                                }
                                if(Menu){
                                   currentScreen = SETTINGS; 
                                }
                // Painel fixo itens (fora do modo 2D)
                Rectangle painelMeio = { painelLateralLargura/2, AlturaTela - painelMeioAltura , painelMeioLargura, painelMeioAltura};
                DrawRectangleRec(painelMeio, (Color){50, 50, 50, 200});
                DrawText("Painel de Itens", painelMeio.x + 20, AlturaTela - painelMeioAltura, 20, WHITE); 

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