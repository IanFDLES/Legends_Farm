#include"Animais.hpp"

float GalinhasCompradas = 4;
float VacasCompradas = 4;
float PorcosCompradas = 4;
float OvelhasCompradas = 4;


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
            a->VelocidadeProducao = 2.0f;
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
            a->VelocidadeProducao = 1.5f;
            a->cor = PINK;
            a->tamanho =  30.0f;
            break;

        case OVELHA:
            a->speed = 12.0f;
            a->life = 18;
            a->VelocidadeProducao = 1.2f;
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
                                float GalinhasCompradas, float VacasCompradas, float PorcosCompradas, float OvelhasCompradas,
                                Rectangle Galinheiro, Rectangle Curral, Rectangle Chiqueiro, Rectangle CampodasOvelhas) {
    
    // Inicializar galinhas
    for (int i = 0; i < MAX_ANIMALS; i++) galinha[i].active = false, galinha[i].processo = 0;
    for (int i = 0; i < GalinhasCompradas; i++) {
        InicializarAnimal(&galinha[i], TipoAnimal(2), 
                         (Vector2){Galinheiro.x + GetRandomValue(0, Galinheiro.width), 
                                  Galinheiro.y + GetRandomValue(0, Galinheiro.height)});
    }
    
    // Inicializar vacas
    for (int i = 0; i < MAX_ANIMALS; i++) vacas[i].active = false, vacas[i].processo = 0;
    for (int i = 0; i < VacasCompradas; i++) {
        InicializarAnimal(&vacas[i], TipoAnimal(2), 
                         (Vector2){Curral.x + GetRandomValue(0, Curral.width), 
                                  Curral.y + GetRandomValue(0, Curral.height)});
    }
    
    // Inicializar porcos
    for (int i = 0; i < MAX_ANIMALS; i++) porcos[i].active = false, porcos[i].processo = 0;
    for (int i = 0; i < PorcosCompradas; i++) {
        InicializarAnimal(&porcos[i], TipoAnimal(2), 
                         (Vector2){Chiqueiro.x + GetRandomValue(0, Chiqueiro.width), 
                                  Chiqueiro.y + GetRandomValue(0, Chiqueiro.height)});
    }
    
    // Inicializar ovelhas
    for (int i = 0; i < MAX_ANIMALS; i++) ovelhas[i].active = false, ovelhas[i].processo = 0;
    for (int i = 0; i < OvelhasCompradas; i++) {
        InicializarAnimal(&ovelhas[i], TipoAnimal(2), 
                         (Vector2){CampodasOvelhas.x + GetRandomValue(0, CampodasOvelhas.width), 
                                  CampodasOvelhas.y + GetRandomValue(0, CampodasOvelhas.height)});
    }
    }


    void ComportamentoGalinha(Animal galinhas[], int quantidade, Rectangle galinheiro, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador) {
        for (int i = 0; i < quantidade; i++) {
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
                        galinhas[i].active = false;
                        // A quantidade será ajustada no main
                    }
                }
            }

            // 5. Produção de ovo
            galinhas[i].processo += VEL_PROD * galinhas[i].VelocidadeProducao;
            if (Vector2Distance(galinhas[i].pos, posicaoJogador) < 200 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (galinhas[i].processo >= 40) {
                    inserirL(recursosJogador, "ovo");
                    galinhas[i].processo = 0;
                }
            }
        }
    }

    void ComportamentoVaca(Animal vacas[], int quantidade, Rectangle curral, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador) {
        for (int i = 0; i < quantidade; i++) {
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
                        vacas[i].active = false;
                        // A quantidade será ajustada no main
                    }
                }
            }

            // 5. Produção de leite
            vacas[i].processo += VEL_PROD * vacas[i].VelocidadeProducao;
            if (Vector2Distance(vacas[i].pos, posicaoJogador) < 200 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (vacas[i].processo >= 120) {
                    inserirL(recursosJogador, "leite");
                    vacas[i].processo = 0;
                }
            }
        }
    }

    // Implemente similarmente para ComportamentoPorco e ComportamentoOvelha...

    void ComportamentoPorco(Animal porcos[], int quantidade, Rectangle chiqueiro, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador) {
        for (int i = 0; i < quantidade; i++) {
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
                        porcos[i].active = false;
                    }
                }
            }

            // Produção de bacon (abate)
            porcos[i].processo += VEL_PROD * porcos[i].VelocidadeProducao;
            if (Vector2Distance(porcos[i].pos, posicaoJogador) < 200 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (porcos[i].processo >= 140) {
                    for (int j = 0; j < 3; j++) inserirL(recursosJogador, "bacon");
                    porcos[i].processo = 0;
                    porcos[i].active = false;
                    // A quantidade será ajustada no main
                }
            }
        }
    }

    void ComportamentoOvelha(Animal ovelhas[], int quantidade, Rectangle campoOvelhas, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador) {
        for (int i = 0; i < quantidade; i++) {
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
                        ovelhas[i].active = false;
                    }
                }
            }

            // Produção de lã
            ovelhas[i].processo += VEL_PROD * ovelhas[i].VelocidadeProducao;
            if (Vector2Distance(ovelhas[i].pos, posicaoJogador) < 200 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (ovelhas[i].processo >= 40) {
                    inserirL(recursosJogador, "la");
                    ovelhas[i].processo = 0;
                }
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
