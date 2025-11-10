struct node {
    int info = 0;
    node *dir = nullptr, *esq  = nullptr;
};
struct Header {
    node *header = nullptr;
};
void criar (Header &fila) {
    fila.header = new node;
    fila.header->dir = fila.header;
    fila.header->esq = fila.header;
}
bool vazia (Header &fila) {
    return ((fila.header == nullptr) || (fila.header == fila.header->dir));
}
void inserir (Header &fila, int x) {

    if (fila.header == nullptr) criar(fila);


    node *aux = new node;
    aux->info = x;
    aux->dir = fila.header;
    aux->esq = fila.header->esq;
    fila.header->esq = aux;
    aux->esq->dir = aux;
}
bool retirar (Header &fila, int &x) {

    if (vazia(fila)) return false;

    node *aux = fila.header->dir;
    x = aux->info;
    fila.header->dir = aux->dir;
    aux->dir->esq = fila.header;
    delete aux;
    return true;
}