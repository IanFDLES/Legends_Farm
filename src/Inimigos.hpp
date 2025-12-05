#ifndef INIMIGOS_HPP
#define INIMIGOS_HPP

#include "raylib.h"

#define MAX_ENEMIES 10000
#define MAX_BULLETS 50

typedef struct Enemy {
    Vector2 pos;
    float speed;
    bool active;
    int damage;
} Enemy;

typedef struct Bullet {
    Vector2 pos;
    Vector2 dir;
    float speed;
    bool active;
} Bullet;
typedef struct Boss {
    Vector2 pos;
    float speed;
    bool active;
    int life;
    int maxLife;
    float radius;
} Boss;

// Funções para inimigos
void InicializarInimigos(Enemy inimigos[]);
void InicializarBalas(Bullet balas[]);
void SpawnarOndaInimigos(Enemy inimigos[], Vector2 posicaoJogador, int& inimigosPorOnda, float& spawnTimer, float tempoEntreOndas);
void AtualizarInimigos(Enemy inimigos[], Vector2 posicaoJogador, int &vida);
void AtualizarBalas(Bullet balas[], Enemy inimigos[], Vector2 posicaoJogador);
void InicializarBoss(Boss& boss);
void SpawnarBoss(Boss& boss, int mapa_largura, int mapa_altura, bool& bossSpawned, int pedidosConcluidos);
void AtualizarBoss(Boss& boss, Vector2 posicaoJogador, Bullet balas[], int& vida);
bool BossFoiDerrotado(Boss& boss);
#endif