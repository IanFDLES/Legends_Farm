#ifndef ANIMAIS_HPP
#define ANIMAIS_HPP
#include <raylib.h>
#include "Lista.hpp"
#include "raymath.h"
#include "Inimigos.hpp" 
#define VEL_PROD (1.0f / 60.0f)


extern float GalinhasCompradas;
extern float VacasCompradas ;
extern float PorcosCompradas ;
extern float OvelhasCompradas ;
#define MAX_ANIMALS 10
 enum TipoAnimal{
    VACA = 1,
    GALINHA,
    PORCO,
    OVELHA
} ;
typedef struct {
    Vector2 pos;
    Vector2 dir;
    float speed;
    bool active;
    bool podeProduzir;
    float life;
    float VelocidadeProducao;
    float processo;
    TipoAnimal tipo;
    Color cor;
    float tamanho;
} Animal;
    void InicializarAnimal(Animal *a, TipoAnimal tipo, Vector2 posInicial);
    void InicializarAnimaisComprados(Animal galinha[], Animal vacas[], Animal porcos[], Animal ovelhas[],
                                float GalinhasCompradas, float VacasCompradas, float PorcosCompradas, float OvelhasCompradas,
                                Rectangle Galinheiro, Rectangle Curral, Rectangle Chiqueiro, Rectangle CampodasOvelhas);
    void ComportamentoGalinha(Animal galinhas[], int quantidade, Rectangle galinheiro, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador);
    void ComportamentoVaca(Animal vacas[], int quantidade, Rectangle curral, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador);
    void ComportamentoPorco(Animal porcos[], int quantidade, Rectangle chiqueiro, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador);
    void ComportamentoOvelha(Animal ovelhas[], int quantidade, Rectangle campoOvelhas, Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador);

// Função geral para atualizar todos os animais
    void AtualizarTodosAnimais(Animal galinhas[], Animal vacas[], Animal porcos[], Animal ovelhas[],
                          int qtdGalinhas, int qtdVacas, int qtdPorcos, int qtdOvelhas,
                          Rectangle galinheiro, Rectangle curral, Rectangle chiqueiro, Rectangle campoOvelhas,
                          Vector2 posicaoJogador, Enemy inimigos[], int maxInimigos, lista& recursosJogador);
#endif