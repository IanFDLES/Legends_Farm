#include"Pedidos.hpp"

// Gerador de pedidos

void GerarNovoPedido(fila &filaPedidos) {
    lista novoPedido;
    criarL(novoPedido);

    int numOvos = GetRandomValue(0, 3);
    int numLeite = GetRandomValue(0, 3);
    int numBacons = GetRandomValue(0, 3);
    int numLa = GetRandomValue(0, 3);

    int totalItens = 0;

    for (int i = 0; i < numOvos; i++) {
        inserirL(novoPedido, "ovo");
        totalItens++;
    }
    for (int i = 0; i < numLeite; i++) {
        inserirL(novoPedido, "leite");
        totalItens++;
    }
    for (int i = 0; i < numBacons; i++) {
        inserirL(novoPedido, "bacon");
        totalItens++;
    }
    for (int i = 0; i < numLa; i++) {
        inserirL(novoPedido, "la");
        totalItens++;
    }

    if (totalItens == 0) {
        inserirL(novoPedido, "ovo");
    }

    inserirF(filaPedidos, novoPedido);
}

// Desenha os pedidos

void DrawPedidos(fila &filaPedidos, Rectangle painel, Rectangle botaoPedidos) {
    
    float yPos = botaoPedidos.y + botaoPedidos.height + 10;

    if (vaziaF(filaPedidos)) {
        DrawText("Nenhum pedido", painel.x + 10, yPos, 20, LIGHTGRAY);
        return;
    }

    nodeF *noFilaAtual = filaPedidos.header->dir;
    
    while (noFilaAtual != filaPedidos.header) {
        
        lista &pedidoAtual = noFilaAtual->info;
        
        int ovos = 0, leite = 0, bacons = 0, la = 0;
        
        nodeL *noListaAtual = pedidoAtual.headerp->dir;
        while (noListaAtual != pedidoAtual.headerp) {
            if (noListaAtual->tipo == "ovo") ovos++;
            else if (noListaAtual->tipo == "leite") leite++;
            else if (noListaAtual->tipo == "bacon") bacons++;
            else if (noListaAtual->tipo == "la") la++;
            noListaAtual = noListaAtual->dir;
        }

        float alturaPedido = 10;
        if (ovos > 0) alturaPedido += 25;
        if (leite > 0) alturaPedido += 25;
        if (bacons > 0) alturaPedido += 25;
        if (la > 0) alturaPedido += 25;
        
        Rectangle bgPedido = {painel.x + 10, yPos, painel.width - 20, alturaPedido};
        DrawRectangleRec(bgPedido, (Color){70, 70, 70, 255});

        float xPosTexto = painel.x + 20;
        float yItemPos = yPos + 10;

        if (ovos > 0) {
            DrawText(TextFormat("%d x Ovos", ovos), xPosTexto, yItemPos, 20, YELLOW);
            yItemPos += 25;
        }
        if (leite > 0) {
            DrawText(TextFormat("%d x Leite", leite), xPosTexto, yItemPos, 20, WHITE);
            yItemPos += 25;
        }
        if (bacons > 0) {
            DrawText(TextFormat("%d x Bacon", bacons), xPosTexto, yItemPos, 20, RED);
            yItemPos += 25;
        }
        if (la > 0) {
            DrawText(TextFormat("%d x La", la), xPosTexto, yItemPos, 20, LIGHTGRAY);
            yItemPos += 25;
        }

        yPos = yPos + alturaPedido + 10;
        noFilaAtual = noFilaAtual->dir;
    }
}

RequisitosPedido ContarRequisitos(lista &pedido) {
    RequisitosPedido req = {0, 0, 0, 0};

    if (vazioL(pedido)) return req;

    nodeL *noListaAtual = pedido.headerp->dir;
    while (noListaAtual != pedido.headerp) {
        if (noListaAtual->tipo == "ovo") req.ovos++;
        else if (noListaAtual->tipo == "leite") req.leite++;
        else if (noListaAtual->tipo == "bacon") req.bacons++;
        else if (noListaAtual->tipo == "la") req.la++;
        noListaAtual = noListaAtual->dir;
    }
    return req;
}

bool PodeEntregar(RequisitosPedido &inventario, RequisitosPedido &pedido) {
    if (inventario.ovos < pedido.ovos) return false;
    if (inventario.leite < pedido.leite) return false;
    if (inventario.bacons < pedido.bacons) return false;
    if (inventario.la < pedido.la) return false;
    
    return true;
}
