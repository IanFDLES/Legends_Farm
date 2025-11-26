#ifndef LISTA_HPP
#define LISTA_HPP
#include<raylib.h>
#include <string>

struct nodeL
{
    std::string tipo;
    nodeL *dir = nullptr, *esq = nullptr;
};

struct lista
{
    nodeL *headerp = nullptr;
};

void criarL(lista &inicio);
bool vazioL(lista &inicio);
void inserirL(lista &inicio, std::string item);
bool retirarL(lista &inicio,std::string itemComparado);
bool listasIguais(lista &inicio1, lista &inicio2);
void limparL(lista &inicio);
void destruirL(lista &inicio);
#endif