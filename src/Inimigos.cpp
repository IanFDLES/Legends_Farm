#include "Inimigos.hpp"
#include "raymath.h"

void InicializarInimigos(Enemy inimigos[]) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        inimigos[i].active = false;
    }
}

void InicializarBalas(Bullet balas[]) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        balas[i].active = false;
    }
}

void SpawnarOndaInimigos(Enemy inimigos[], Vector2 posicaoJogador, int& inimigosPorOnda, float& spawnTimer, float tempoEntreOndas) {
    spawnTimer += GetFrameTime();
    if (spawnTimer >= tempoEntreOndas) {
        spawnTimer = 0;
        for (int i = 0; i < inimigosPorOnda; i++) {
            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (!inimigos[j].active) {
                    inimigos[j].active = true;
                    inimigos[j].speed = 2.0f;
                    float angle = GetRandomValue(0, 360) * DEG2RAD;
                    float dist = 500.0f;
                    inimigos[j].pos = (Vector2){ 
                        posicaoJogador.x + cosf(angle) * dist, 
                        posicaoJogador.y + sinf(angle) * dist 
                    };
                    break;
                }
            }
        }
        inimigosPorOnda++;
    }
}

void AtualizarInimigos(Enemy inimigos[], Vector2 posicaoJogador) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (inimigos[i].active) {
            Vector2 dirE = Vector2Normalize(Vector2Subtract(posicaoJogador, inimigos[i].pos));
            inimigos[i].pos = Vector2Add(inimigos[i].pos, Vector2Scale(dirE, inimigos[i].speed));
            
            if (Vector2Distance(posicaoJogador, inimigos[i].pos) < 20) {
                inimigos[i].active = false;
            }
        }
    }
}

void AtualizarBalas(Bullet balas[], Enemy inimigos[], Vector2 posicaoJogador) {
    for (int b = 0; b < MAX_BULLETS; b++) {
        if (balas[b].active) {
            balas[b].pos = Vector2Add(balas[b].pos, Vector2Scale(balas[b].dir, balas[b].speed));
            
            // Colisão com inimigos
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (inimigos[i].active && Vector2Distance(balas[b].pos, inimigos[i].pos) < 15) {
                    balas[b].active = false;
                    inimigos[i].active = false;
                    break;
                }
            }
            
            if (Vector2Distance(posicaoJogador, balas[b].pos) > 800) {
                balas[b].active = false;
            }
        }
    }
}

void InicializarBoss(Boss& boss) {
    boss.active = false;
    boss.life = 50;
    boss.maxLife = 50;
    boss.radius = 40.0f;
    boss.speed = 3.5f;
}

void SpawnarBoss(Boss& boss, int mapa_largura, int mapa_altura, bool& bossSpawned, int pedidosConcluidos) {
    if (pedidosConcluidos >= 20 && !bossSpawned) {
        boss.active = true;
        boss.pos = (Vector2){ (float)mapa_largura / 2, (float)mapa_altura / 2 };
        bossSpawned = true;
    }
}

void AtualizarBoss(Boss& boss, Vector2 posicaoJogador, Bullet balas[]) {
    if (boss.active) {
        // Movimentação do Boss (persegue o jogador)
        Vector2 dirBoss = Vector2Normalize(Vector2Subtract(posicaoJogador, boss.pos));
        boss.pos = Vector2Add(boss.pos, Vector2Scale(dirBoss, boss.speed));
        
        // Colisão com balas
        for (int b = 0; b < MAX_BULLETS; b++) {
            if (balas[b].active && Vector2Distance(balas[b].pos, boss.pos) < boss.radius) {
                balas[b].active = false;
                boss.life -= 1;
                if (boss.life <= 0) {
                    boss.active = false;
                }
            }
        }
    }
}

bool BossFoiDerrotado(Boss& boss) {
    return !boss.active && boss.life <= 0;
}