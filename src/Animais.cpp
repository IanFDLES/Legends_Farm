#include "Animais.hpp"

int GalinhasAtuais = 0;
int VacasAtuais = 0;
int PorcosAtuais = 0;
int OvelhasAtuais = 0;

// resource pool definition
Resource resources[MAX_RESOURCES];

void InicializarRecursos() {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        resources[i].active = false;
        resources[i].ttl = 0.0f;
        resources[i].pos = (Vector2){0,0};
        resources[i].type = R_OVO;
    }
}

bool SpawnResource(ResourceType tipo, Vector2 pos, int quantidade, float ttl) {
    bool spawned = false;
    for (int q = 0; q < quantidade; q++) {
        for (int i = 0; i < MAX_RESOURCES; i++) {
            if (!resources[i].active) {
                resources[i].active = true;
                resources[i].type = tipo;
                resources[i].pos.x = pos.x + GetRandomValue(-10, 10);
                resources[i].pos.y = pos.y + GetRandomValue(-10, 10);
                resources[i].ttl = ttl;
                spawned = true;
                break;
            }
        }
    }
    return spawned;
}

void AtualizarRecursos(Vector2 playerPos, lista& recursosJogador) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (!resources[i].active) continue;

        if (resources[i].ttl > 0.0f) {
            resources[i].ttl -= GetFrameTime();
            if (resources[i].ttl <= 0.0f) { resources[i].active = false; continue; }
        }

        if (Vector2Distance(playerPos, resources[i].pos) < 24.0f) {
            switch (resources[i].type) {
                case R_OVO: inserirL(recursosJogador, "ovo"); break;
                case R_LEITE: inserirL(recursosJogador, "leite"); break;
                case R_LA: inserirL(recursosJogador, "la"); break;
                case R_BACON: inserirL(recursosJogador, "bacon"); break;
            }
            resources[i].active = false;
        }
    }
}

void InicializarAnimal(Animal *a, TipoAnimal tipo, Vector2 posInicial) {
    a->tipo = tipo;
    a->pos = posInicial;
    a->active = true;
    a->podeProduzir = true;
    a->dir = (Vector2){0, 0};

    switch (tipo) {
        case VACA:
            a->speed = 8.0f;
            a->life = 30;
            a->VelocidadeProducao = 24.0f;
            a->cor = BROWN; 
            a->tamanho =  45.0f;
            break;

        case GALINHA:
            a->speed = 7;
            a->life = 10;
            a->VelocidadeProducao = 8.0f;
            a->cor = YELLOW; 
            a->tamanho =  20.0f;
            break;

        case PORCO:
            a->speed = 9.0f;
            a->life = 20;
            a->VelocidadeProducao = 28.0f;
            a->cor = PINK;
            a->tamanho =  30.0f;
            break;

        case OVELHA:
            a->speed = 12.0f;
            a->life = 18;
            a->VelocidadeProducao = 8.0f;
            a->cor = LIGHTGRAY;
            a->tamanho =  24.0f; 
            break;

        default:
            a->speed = 10.0f;
            a->life = 10;
            a->VelocidadeProducao = 1.0f;
            a->cor = WHITE;
            break;
    }
}

    void InicializarAnimaisComprados(Animal galinha[], Animal vacas[], Animal porcos[], Animal ovelhas[],
                                int GalinhasAtuais, int VacasAtuais, int PorcosAtuais, int OvelhasAtuais,
                                Rectangle Galinheiro, Rectangle Curral, Rectangle Chiqueiro, Rectangle CampodasOvelhas) {
    
    // Inicializar galinhas
    for (int i = 0; i < MAX_ANIMALS; i++) galinha[i].active = false, galinha[i].processo = 0;
    for (int i = 0; i < GalinhasAtuais; i++) {
        InicializarAnimal(&galinha[i], GALINHA, 
                         (Vector2){Galinheiro.x + GetRandomValue(0, Galinheiro.width), 
                                  Galinheiro.y + GetRandomValue(0, Galinheiro.height)});
    }
    
    // Inicializar vacas
    for (int i = 0; i < MAX_ANIMALS; i++) vacas[i].active = false, vacas[i].processo = 0;
    for (int i = 0; i < VacasAtuais; i++) {
        // Use the correct enum value for cows (VACA)
        InicializarAnimal(&vacas[i], VACA, 
                         (Vector2){Curral.x + GetRandomValue(0, Curral.width), 
                                  Curral.y + GetRandomValue(0, Curral.height)});
    }
    
    // Inicializar porcos
    for (int i = 0; i < MAX_ANIMALS; i++) porcos[i].active = false, porcos[i].processo = 0;
    for (int i = 0; i < PorcosAtuais; i++) {
        // Use the correct enum value for pigs (PORCO)
        InicializarAnimal(&porcos[i], PORCO, 
                         (Vector2){Chiqueiro.x + GetRandomValue(0, Chiqueiro.width), 
                                  Chiqueiro.y + GetRandomValue(0, Chiqueiro.height)});
    }
    
    // Inicializar ovelhas
    for (int i = 0; i < MAX_ANIMALS; i++) ovelhas[i].active = false, ovelhas[i].processo = 0;
    for (int i = 0; i < OvelhasAtuais; i++) {
        // Use the correct enum value for sheep (OVELHA)
        InicializarAnimal(&ovelhas[i], OVELHA, 
                         (Vector2){CampodasOvelhas.x + GetRandomValue(0, CampodasOvelhas.width), 
                                  CampodasOvelhas.y + GetRandomValue(0, CampodasOvelhas.height)});
    }
    }


    void ComportamentoGalinha(Animal galinhas[], int quantidade, Rectangle galinheiro, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador) {
        // iterate over whole array and check active flag -> avoids "hole" bugs
        // where animals can be at indices beyond `quantidade` and get left unprocessed
        for (int i = 0; i < MAX_ANIMALS; i++) {
            if (!galinhas[i].active) continue;

            // 1. Movimento aleatório
            if (Vector2Length(galinhas[i].dir) == 0 || GetRandomValue(0, 100) < 2) {
                float destinoX = GetRandomValue(galinheiro.x, galinheiro.x + galinheiro.width);
                float destinoY = GetRandomValue(galinheiro.y, galinheiro.y + galinheiro.height);
                Vector2 destino = (Vector2){destinoX, destinoY};
                galinhas[i].dir = Vector2Normalize(Vector2Subtract(destino, galinhas[i].pos));
            }

            // 2. Movimentação
            galinhas[i].pos = Vector2Add(
                galinhas[i].pos, 
                Vector2Scale(galinhas[i].dir, galinhas[i].speed * GetFrameTime())
            );

            // 3. Limites do galinheiro
            if (galinhas[i].pos.x < galinheiro.x) galinhas[i].pos.x = galinheiro.x;
            if (galinhas[i].pos.x > galinheiro.x + galinheiro.width) galinhas[i].pos.x = galinheiro.x + galinheiro.width;
            if (galinhas[i].pos.y < galinheiro.y) galinhas[i].pos.y = galinheiro.y;
            if (galinhas[i].pos.y > galinheiro.y + galinheiro.height) galinhas[i].pos.y = galinheiro.y + galinheiro.height;

            // 4. Colisão com inimigos
            for (int e = 0; e < maxInimigos; e++) {
                if (!inimigos[e].active) continue;
                if (Vector2Distance(galinhas[i].pos, inimigos[e].pos) < 20) {
                    galinhas[i].life -= inimigos[e].damage * GetFrameTime();
                    if (galinhas[i].life <= 0) {
                        if (GalinhasAtuais > 0) GalinhasAtuais--;
                        galinhas[i].active = false;
                        // A quantidade será ajustada no main
                    }
                }
            }

            // 5. Produção de ovo -> drop on ground when process threshold is reached
            galinhas[i].processo += VEL_PROD * galinhas[i].VelocidadeProducao;
            if (galinhas[i].processo >= 40) {
                SpawnResource(R_OVO, galinhas[i].pos, 1, 60.0f); // egg despawns after 60s
                galinhas[i].processo = 0;
            }
        }
    }

    void ComportamentoVaca(Animal vacas[], int quantidade, Rectangle curral, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador) {
        // process full array, not only the compacted count
        for (int i = 0; i < MAX_ANIMALS; i++) {
            if (!vacas[i].active) continue;

            // 1. Movimento aleatório
            if (Vector2Length(vacas[i].dir) == 0 || GetRandomValue(0, 100) < 2) {
                float destinoX = GetRandomValue(curral.x, curral.x + curral.width);
                float destinoY = GetRandomValue(curral.y, curral.y + curral.height);
                Vector2 destino = (Vector2){destinoX, destinoY};
                vacas[i].dir = Vector2Normalize(Vector2Subtract(destino, vacas[i].pos));
            }

            // 2. Movimentação
            vacas[i].pos = Vector2Add(
                vacas[i].pos, 
                Vector2Scale(vacas[i].dir, vacas[i].speed * GetFrameTime())
            );

            // 3. Limites do curral
            if (vacas[i].pos.x < curral.x) vacas[i].pos.x = curral.x;
            if (vacas[i].pos.x > curral.x + curral.width) vacas[i].pos.x = curral.x + curral.width;
            if (vacas[i].pos.y < curral.y) vacas[i].pos.y = curral.y;
            if (vacas[i].pos.y > curral.y + curral.height) vacas[i].pos.y = curral.y + curral.height;

            // 4. Colisão com inimigos
            for (int e = 0; e < maxInimigos; e++) {
                if (!inimigos[e].active) continue;
                if (Vector2Distance(vacas[i].pos, inimigos[e].pos) < 20) {
                    vacas[i].life -= inimigos[e].damage * GetFrameTime();
                    if (vacas[i].life <= 0) {
                        if (VacasAtuais > 0) VacasAtuais--;
                        vacas[i].active = false;
                        // A quantidade será ajustada no main
                    }
                }
            }

            // 5. Produção de leite -> drop on ground
            vacas[i].processo += VEL_PROD * vacas[i].VelocidadeProducao;
            if (vacas[i].processo >= 120) {
                SpawnResource(R_LEITE, vacas[i].pos, 1, 60.0f);
                vacas[i].processo = 0;
            }
        }
    }

    // Implemente similarmente para ComportamentoPorco e ComportamentoOvelha...

    void ComportamentoPorco(Animal porcos[], int quantidade, Rectangle chiqueiro, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador) {
        // process full array, not only the compacted count
        for (int i = 0; i < MAX_ANIMALS; i++) {
            if (!porcos[i].active) continue;

            // Movimento aleatório
            if (Vector2Length(porcos[i].dir) == 0 || GetRandomValue(0, 100) < 2) {
                float destinoX = GetRandomValue(chiqueiro.x, chiqueiro.x + chiqueiro.width);
                float destinoY = GetRandomValue(chiqueiro.y, chiqueiro.y + chiqueiro.height);
                Vector2 destino = (Vector2){destinoX, destinoY};
                porcos[i].dir = Vector2Normalize(Vector2Subtract(destino, porcos[i].pos));
            }

            // Movimentação
            porcos[i].pos = Vector2Add(
                porcos[i].pos, 
                Vector2Scale(porcos[i].dir, porcos[i].speed * GetFrameTime())
            );

            // Limites
            if (porcos[i].pos.x < chiqueiro.x) porcos[i].pos.x = chiqueiro.x;
            if (porcos[i].pos.x > chiqueiro.x + chiqueiro.width) porcos[i].pos.x = chiqueiro.x + chiqueiro.width;
            if (porcos[i].pos.y < chiqueiro.y) porcos[i].pos.y = chiqueiro.y;
            if (porcos[i].pos.y > chiqueiro.y + chiqueiro.height) porcos[i].pos.y = chiqueiro.y + chiqueiro.height;

            // Colisão com inimigos
            for (int e = 0; e < maxInimigos; e++) {
                if (!inimigos[e].active) continue;
                if (Vector2Distance(porcos[i].pos, inimigos[e].pos) < 20) {
                    porcos[i].life -= inimigos[e].damage * GetFrameTime();
                        if (porcos[i].life <= 0) {
                            if (PorcosAtuais > 0) PorcosAtuais--;
                            porcos[i].active = false;
                        }
                }
            }

            // Bacon now drops only when player shoots the pig (handled in main loop)
            // (timed production removed)
        }
    }

    void ComportamentoOvelha(Animal ovelhas[], int quantidade, Rectangle campoOvelhas, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador) {
        // process full array, not only the compacted count
        for (int i = 0; i < MAX_ANIMALS; i++) {
            if (!ovelhas[i].active) continue;

            // Movimento aleatório
            if (Vector2Length(ovelhas[i].dir) == 0 || GetRandomValue(0, 100) < 2) {
                float destinoX = GetRandomValue(campoOvelhas.x, campoOvelhas.x + campoOvelhas.width);
                float destinoY = GetRandomValue(campoOvelhas.y, campoOvelhas.y + campoOvelhas.height);
                Vector2 destino = (Vector2){destinoX, destinoY};
                ovelhas[i].dir = Vector2Normalize(Vector2Subtract(destino, ovelhas[i].pos));
            }

            // Movimentação
            ovelhas[i].pos = Vector2Add(
                ovelhas[i].pos, 
                Vector2Scale(ovelhas[i].dir, ovelhas[i].speed * GetFrameTime())
            );

            // Limites
            if (ovelhas[i].pos.x < campoOvelhas.x) ovelhas[i].pos.x = campoOvelhas.x;
            if (ovelhas[i].pos.x > campoOvelhas.x + campoOvelhas.width) ovelhas[i].pos.x = campoOvelhas.x + campoOvelhas.width;
            if (ovelhas[i].pos.y < campoOvelhas.y) ovelhas[i].pos.y = campoOvelhas.y;
            if (ovelhas[i].pos.y > campoOvelhas.y + campoOvelhas.height) ovelhas[i].pos.y = campoOvelhas.y + campoOvelhas.height;

            // Colisão com inimigos
            for (int e = 0; e < maxInimigos; e++) {
                if (!inimigos[e].active) continue;
                if (Vector2Distance(ovelhas[i].pos, inimigos[e].pos) < 20) {
                    ovelhas[i].life -= inimigos[e].damage * GetFrameTime();
                    if (ovelhas[i].life <= 0) {
                        if (OvelhasAtuais > 0) OvelhasAtuais--;
                        ovelhas[i].active = false;
                    }
                }
            }

            // Produção de lã (drop)
            ovelhas[i].processo += VEL_PROD * ovelhas[i].VelocidadeProducao;
            if (ovelhas[i].processo >= 40) {
                SpawnResource(R_LA, ovelhas[i].pos, 1, 60.0f);
                ovelhas[i].processo = 0;
            }
        }
    }

    void AtualizarTodosAnimais(Animal galinhas[], Animal vacas[], Animal porcos[], Animal ovelhas[],
                              int qtdGalinhas, int qtdVacas, int qtdPorcos, int qtdOvelhas,
                              Rectangle galinheiro, Rectangle curral, Rectangle chiqueiro, Rectangle campoOvelhas,
                              Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador) {
                            
        ComportamentoGalinha(galinhas, qtdGalinhas, galinheiro, posicaoJogador, inimigos, maxInimigos, recursosJogador);
        ComportamentoVaca(vacas, qtdVacas, curral, posicaoJogador, inimigos, maxInimigos, recursosJogador);
        ComportamentoPorco(porcos, qtdPorcos, chiqueiro, posicaoJogador, inimigos, maxInimigos, recursosJogador);
        ComportamentoOvelha(ovelhas, qtdOvelhas, campoOvelhas, posicaoJogador, inimigos, maxInimigos, recursosJogador);
    }
