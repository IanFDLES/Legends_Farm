#ifndef ANIMAIS_HPP
#define ANIMAIS_HPP
#include <raylib.h>

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
    
#endif