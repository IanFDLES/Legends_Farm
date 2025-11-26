#include"Animais.hpp"

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
            a->tamanho =  15.0f;
            break;

        case GALINHA:
            a->speed = 7;
            a->life = 10;
            a->VelocidadeProducao = 8.0f;
            a->cor = YELLOW; 
            a->tamanho =  12.0f;
            break;

        case PORCO:
            a->speed = 9.0f;
            a->life = 20;
            a->VelocidadeProducao = 1.5f;
            a->cor = PINK;
            a->tamanho =  10.0f;
            break;

        case OVELHA:
            a->speed = 12.0f;
            a->life = 18;
            a->VelocidadeProducao = 1.2f;
            a->cor = LIGHTGRAY;
            a->tamanho =  8.0f; 
            break;

        default:
            a->speed = 10.0f;
            a->life = 10;
            a->VelocidadeProducao = 1.0f;
            a->cor = WHITE;
            break;
    }
}