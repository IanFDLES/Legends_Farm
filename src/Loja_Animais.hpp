#ifndef SKINS_HPP
#define SKINS_HPP

#include "raylib.h"
#include "Animais.hpp"

// Declarações externas (apenas declara, não define)
extern float precoVaca;
extern float precoGalinha;
extern float precoPorco;
extern float precoOvelha;

// Estrutura para skins
typedef struct {
    Texture2D textura;
    const char* nome;
    float preco;
    int quantidade;
    bool compravel;
} SkinAnimal;

// Declaração das variáveis de skins (extern)
extern SkinAnimal skinVaca, skinGalinha, skinPorco, skinOvelha;

// Declaração da função
void DrawSkinsScreen(Rectangle painelLateral, float painelLateralLargura, Vector2 mousePoint, 
                    int& VacasAtuais, int& GalinhasAtuais, int& PorcosAtuais, int& OvelhasAtuais,
                    float& jogadorMoney, Animal vacas[], Animal galinha[], Animal porcos[], Animal ovelhas[],
                    Rectangle Curral, Rectangle Galinheiro, Rectangle Chiqueiro, Rectangle CampodasOvelhas);


void ProcessarCompraLoja(Rectangle painelLateral, float painelLateralLargura, Vector2 mousePoint,
                        float& jogadorMoney, 
                        int& VacasAtuais, int& GalinhasAtuais, int& PorcosAtuais, int& OvelhasAtuais,
                        Animal vacas[], Animal galinhas[], Animal porcos[], Animal ovelhas[],
                        Rectangle Curral, Rectangle Galinheiro, Rectangle Chiqueiro, Rectangle CampodasOvelhas);                    
#endif