#include <string>
using namespace std;
struct node
{
    string tipo;
    node *dir = nullptr, *esq  = nullptr;
};
struct header
{
    node *headerp=nullptr;
};
void criar(header &inicio){
    inicio.headerp = new node;
    inicio.headerp->dir=inicio.headerp;
    inicio.headerp->esq=inicio.headerp;
}
bool vazio(header &inicio){
    return (inicio.headerp==nullptr || inicio.headerp->dir==nullptr);
}

void inserir(header &inicio,string item){
    if(vazio(inicio)) criar(inicio);
    node *iaux = new node;
    iaux->tipo=item;
    node *aux = inicio.headerp->dir;
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

bool retirar(header &inicio,string itemComparado)
{   
    if(vazio(inicio)) return false;
    node *aux= inicio.headerp->dir;
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

bool listasIguais(header &inicio1, header &inicio2){
    if(vazio(inicio1) || vazio(inicio2)) return vazio(inicio1) && vazio(inicio2);
    node *aux1 = inicio1.headerp->dir;
    node *aux2 = inicio2.headerp->dir;
    while(aux1 != inicio1.headerp){
        if(aux1->tipo != aux2->tipo) return false;
        aux1 = aux1->dir;
        aux2 = aux2->dir;
    }
    return true;
}