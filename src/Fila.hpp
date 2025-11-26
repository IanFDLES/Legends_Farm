#ifndef FILA_HPP
#define FILA_HPP
#include<raylib.h>
#include "Lista.hpp"
struct nodeF {
    lista info;
    nodeF *dir = nullptr, *esq  = nullptr;
};

struct fila {
    nodeF *header = nullptr;
};

void criarF (fila &fila);
bool vaziaF (fila &fila);
void inserirF (fila &fila, lista x);
bool retirarF (fila &fila, lista &x);
void limparF (fila &fila);
void destruirF (fila &fila);
#endif
