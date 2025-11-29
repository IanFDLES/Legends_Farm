#ifndef APRIMORAMENTO_HPP
#define APRIMORAMENTO_HPP

#include "raylib.h"
#include "raymath.h"
#include "stdio.h"
#include "Animais.hpp"
// Estrutura para cada nível de aprimoramento
typedef struct {
    int nivel;
    float preco;
    const char* descricao;
    bool desbloqueado;
} NivelAprimoramento;

// Estrutura para cada construção aprimorável
typedef struct {
    const char* nome;
    int nivelAtual;
    int nivelMaximo;
    NivelAprimoramento niveis[3]; // 3 níveis máximo
    float tempoUltimaProducao;
    Texture2D textura;
} ConstrucaoAprimoravel;

// Variáveis das construções
extern ConstrucaoAprimoravel galinheiro;
extern ConstrucaoAprimoravel curral;
extern ConstrucaoAprimoravel chiqueiro;
extern ConstrucaoAprimoravel abrigo;

// Funções
void InicializarAprimoramentos(Texture2D galinhaTex, Texture2D vacaTex, Texture2D porcoTex, Texture2D ovelhaTex);
void DrawAprimoramentosScreen(Rectangle painelLateral, float painelLateralLargura, Vector2 mousePoint,
                             float& jogadorMoney);
void ProcessarCompraAprimoramentos(Rectangle painelLateral, float painelLateralLargura, Vector2 mousePoint,
                                  float& jogadorMoney);
void AtualizarAprimoramentos(float& GalinhasCompradas, float& VacasCompradas, 
                            float& PorcosCompradas, float& OvelhasCompradas);

// Funções de efeitos (para você implementar os efeitos específicos)
void AplicarEfeitoNivel1(int tipoConstrucao); // 0=Galinheiro, 1=Curral, 2=Chiqueiro, 3=Abrigo
void AplicarEfeitoNivel2(int tipoConstrucao);
void AplicarEfeitoNivel3(int tipoConstrucao);

#endif