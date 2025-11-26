#ifndef PEDIDOS_HPP
#define PEDIDOS_HPP
#include<raylib.h>
#include "Fila.hpp"

typedef struct {
    int ovos;
    int leite;
    int bacons;
    int la;
} RequisitosPedido;

void GerarNovoPedido(fila &filaPedidos);
void DrawPedidos(fila &filaPedidos, Rectangle painel, Rectangle botaoPedidos);
RequisitosPedido ContarRequisitos(lista &pedido);
bool PodeEntregar(RequisitosPedido &inventario, RequisitosPedido &pedido);
#endif