#include "Fila.hpp"

void criarF (fila &fila) {
    fila.header = new nodeF;
    fila.header->dir = fila.header;
    fila.header->esq = fila.header;
}

bool vaziaF (fila &fila) {
    return ((fila.header == nullptr) || (fila.header == fila.header->dir));
}

void inserirF (fila &fila, lista x) {
    if (fila.header == nullptr) criarF(fila);

    nodeF *aux = new nodeF;
    aux->info = x;
    aux->dir = fila.header;
    aux->esq = fila.header->esq;
    fila.header->esq = aux;
    aux->esq->dir = aux;
}

bool retirarF (fila &fila, lista &x) {
    if (vaziaF(fila)) return false;

    nodeF *aux = fila.header->dir;
    x = aux->info;
    fila.header->dir = aux->dir;
    aux->dir->esq = fila.header;
    delete aux;
    return true;
}

void limparF (fila &fila) {
    if (vaziaF(fila)) return;
    lista x;
    while (retirarF(fila, x)) {
        destruirL(x);
    }
}

void destruirF (fila &fila) {
    if (fila.header == nullptr) return;
    limparF(fila);
    delete fila.header;
    fila.header = nullptr;
}