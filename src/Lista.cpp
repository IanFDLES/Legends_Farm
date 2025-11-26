#include "Lista.hpp"

void criarL(lista &inicio){
    inicio.headerp = new nodeL;
    inicio.headerp->dir=inicio.headerp;
    inicio.headerp->esq=inicio.headerp;
}

bool vazioL(lista &inicio){
    return (inicio.headerp == nullptr || inicio.headerp->dir == inicio.headerp);
}

void inserirL(lista &inicio, std::string item){
    if(inicio.headerp == nullptr) criarL(inicio);
    nodeL *iaux = new nodeL;
    iaux->tipo=item;
    nodeL *aux = inicio.headerp->dir;
    while(aux != inicio.headerp){
            if(iaux->tipo > aux->tipo){
                aux =aux->dir;
            }else{
                iaux->esq=aux->esq;
                iaux->dir=aux;
                aux->esq->dir=iaux;
                aux->esq=iaux;
                break;
            }
    }
    if(aux == inicio.headerp){
        iaux->dir = inicio.headerp;
        iaux->esq = inicio.headerp->esq;
        inicio.headerp->esq->dir = iaux;
        inicio.headerp->esq = iaux;
    }
}

bool retirarL(lista &inicio,std::string itemComparado)
{   
    if(vazioL(inicio)) return false;
    nodeL *aux= inicio.headerp->dir;
    while(aux != inicio.headerp){
    if(aux->tipo == itemComparado){
        aux->dir->esq=aux->esq;
        aux->esq->dir=aux->dir;
        delete aux;
        return true;
    }
        aux= aux->dir;
    }
    return false;
}

bool listasIguais(lista &inicio1, lista &inicio2){
    if(vazioL(inicio1) || vazioL(inicio2)) return vazioL(inicio1) && vazioL(inicio2);
    
    nodeL *aux1 = inicio1.headerp->dir;
    nodeL *aux2 = inicio2.headerp->dir;

    while(aux1 != inicio1.headerp && aux2 != inicio2.headerp){
        if(aux1->tipo != aux2->tipo) return false;
        aux1 = aux1->dir;
        aux2 = aux2->dir;
    }

    return (aux1 == inicio1.headerp && aux2 == inicio2.headerp);
}

void limparL(lista &inicio) {
    if (vazioL(inicio)) return;
    nodeL *aux = inicio.headerp->dir;
    while (aux != inicio.headerp) {
        nodeL *paraDeletar = aux;
        aux = aux->dir;
        delete paraDeletar;
    }
    inicio.headerp->dir = inicio.headerp;
    inicio.headerp->esq = inicio.headerp;
}

void destruirL(lista &inicio) {
    if (inicio.headerp == nullptr) return;
    limparL(inicio);
    delete inicio.headerp;
    inicio.headerp = nullptr;
}