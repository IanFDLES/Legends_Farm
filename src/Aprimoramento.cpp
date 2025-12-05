#include "Aprimoramento.hpp"
#include "Animais.hpp"


// Definição das construções
ConstrucaoAprimoravel galinheiro;
ConstrucaoAprimoravel curral;
ConstrucaoAprimoravel chiqueiro;
ConstrucaoAprimoravel abrigo;

void InicializarAprimoramentos(Texture2D galinhaTex, Texture2D vacaTex, Texture2D porcoTex, Texture2D ovelhaTex) {
    // Inicializa Galinheiro
    galinheiro.nome = "GALINHEIRO";
    galinheiro.nivelAtual = 0;
    galinheiro.nivelMaximo = 3;
    galinheiro.textura = galinhaTex;
    galinheiro.tempoUltimaProducao = 0;
    
    galinheiro.niveis[0] = {1, 100.0f, "+1 galinha/15s", false};
    galinheiro.niveis[1] = {2, 200.0f, "+2 galinhas/15s", false};
    galinheiro.niveis[2] = {3, 300.0f, "+3 galinhas/15s", false};
    
    // Inicializa Curral
    curral.nome = "CURRAL";
    curral.nivelAtual = 0;
    curral.nivelMaximo = 3;
    curral.textura = vacaTex;
    curral.tempoUltimaProducao = 0;
    
    curral.niveis[0] = {1, 150.0f, "+1 vaca/15s", false};
    curral.niveis[1] = {2, 300.0f, "+2 vacas/15s", false};
    curral.niveis[2] = {3, 450.0f, "+3 vacas/15s", false};
    
    // Inicializa Chiqueiro
    chiqueiro.nome = "CHIQUEIRO";
    chiqueiro.nivelAtual = 0;
    chiqueiro.nivelMaximo = 3;
    chiqueiro.textura = porcoTex;
    chiqueiro.tempoUltimaProducao = 0;
    
    chiqueiro.niveis[0] = {1, 120.0f, "+1 porco/15s", false};
    chiqueiro.niveis[1] = {2, 240.0f, "+2 porcos/15s", false};
    chiqueiro.niveis[2] = {3, 360.0f, "+3 porcos/15s", false};
    
    // Inicializa Abrigo
    abrigo.nome = "ABRIGO";
    abrigo.nivelAtual = 0;
    abrigo.nivelMaximo = 3;
    abrigo.textura = ovelhaTex;
    abrigo.tempoUltimaProducao = 0;
    
    abrigo.niveis[0] = {1, 130.0f, "+1 ovelha/15s", false};
    abrigo.niveis[1] = {2, 260.0f, "+2 ovelhas/15s", false};
    abrigo.niveis[2] = {3, 390.0f, "+3 ovelhas/15s", false};
}

void DrawAprimoramentosScreen(Rectangle areaConteudo, float painelLateralLargura, Vector2 mousePoint,
                             float& jogadorMoney) {
    
    // Título dentro da área de conteúdo
    DrawText("APRIMORAMENTOS", areaConteudo.x + 20, areaConteudo.y + 20, 30, GOLD);
    DrawText("Melhore suas construções (Níveis 1-3)", areaConteudo.x + 20, areaConteudo.y + 55, 18, LIGHTGRAY);
    
    float startY = areaConteudo.y + 90; // Começa mais abaixo para dar espaço ao título
    float espacamento = 140;
    float cardWidth = painelLateralLargura - 40;
    float cardHeight = 130;
    
    // Array de construções para facilitar o loop
    ConstrucaoAprimoravel* construcoes[] = {&galinheiro, &curral, &chiqueiro, &abrigo};
    
    for (int c = 0; c < 4; c++) {
        ConstrucaoAprimoravel* construcao = construcoes[c];
        Rectangle card = {areaConteudo.x + 20, startY + (espacamento * c), cardWidth, cardHeight};
        
        // Verifica se o card cabe na tela
        if (card.y + cardHeight > areaConteudo.y + areaConteudo.height) {
            break; // Não desenha se não couber
        }
        
        // Cor do card baseada no nível
        Color corCard;
        if (construcao->nivelAtual == 3) {
            corCard = (Color){100, 200, 255, 255}; // Azul - Nível máximo
        } else if (construcao->nivelAtual > 0) {
            corCard = (Color){100, 255, 100, 255}; // Verde - Níveis intermediários
        } else {
            corCard = (Color){70, 70, 70, 255}; // Cinza - Nível 0
        }
        
        // Efeito hover
        if (CheckCollisionPointRec(mousePoint, card)) {
            corCard = (Color){corCard.r + 30, corCard.g + 30, corCard.b + 30, corCard.a};
        }
        
        DrawRectangleRec(card, corCard);
        DrawRectangleLinesEx(card, 2, DARKGRAY);
        
        // Ícone
        float iconScale = 0.06f;
        float iconW = construcao->textura.width * iconScale;
        float iconH = construcao->textura.height * iconScale;
        DrawTexturePro(construcao->textura, 
                      (Rectangle){0, 0, (float)construcao->textura.width, (float)construcao->textura.height},
                      (Rectangle){card.x + 10, card.y + cardHeight/2 - iconH/2, iconW, iconH},
                      (Vector2){0, 0}, 0.0f, WHITE);
        
        // Nome e nível
        DrawText(construcao->nome, card.x + iconW + 20, card.y + 15, 22, WHITE);
        DrawText(TextFormat("Nível: %d/3", construcao->nivelAtual), card.x + iconW + 20, card.y + 40, 18, LIGHTGRAY);
        
        // Descrição do próximo nível ou nível máximo
        if (construcao->nivelAtual < 3) {
            DrawText(construcao->niveis[construcao->nivelAtual].descricao, card.x + iconW + 20, card.y + 65, 16, YELLOW);
            DrawText(TextFormat("Preço: $%.0f", construcao->niveis[construcao->nivelAtual].preco), 
                    card.x + iconW + 20, card.y + 85, 16, 
                    jogadorMoney >= construcao->niveis[construcao->nivelAtual].preco ? GREEN : RED);
        } else {
            DrawText("NÍVEL MÁXIMO ALCANÇADO", card.x + iconW + 20, card.y + 65, 16, GOLD);
        }
        
        // Barra de progresso dos níveis
        float barraWidth = cardWidth - iconW - 40;
        float barraHeight = 8;
        Rectangle barraFundo = {card.x + iconW + 20, card.y + 110, barraWidth, barraHeight};
        Rectangle barraProgresso = {barraFundo.x, barraFundo.y, barraWidth * (construcao->nivelAtual / 3.0f), barraHeight};
        
        DrawRectangleRec(barraFundo, (Color){50, 50, 50, 255});
        DrawRectangleRec(barraProgresso, (Color){0, 255, 0, 255});
        DrawRectangleLinesEx(barraFundo, 1, DARKGRAY);
    }
}

void ProcessarCompraAprimoramentos(Rectangle areaConteudo, float painelLateralLargura, Vector2 mousePoint,
                                  float& jogadorMoney) {
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        float startY = areaConteudo.y + 90;
        float espacamento = 140;
        float cardWidth = painelLateralLargura - 40;
        float cardHeight = 130;
        
        ConstrucaoAprimoravel* construcoes[] = {&galinheiro, &curral, &chiqueiro, &abrigo};
        
        for (int c = 0; c < 4; c++) {
            ConstrucaoAprimoravel* construcao = construcoes[c];
            Rectangle card = {areaConteudo.x + 20, startY + (espacamento * c), cardWidth, cardHeight};
            
            if (CheckCollisionPointRec(mousePoint, card) && 
                construcao->nivelAtual < 3 &&
                jogadorMoney >= construcao->niveis[construcao->nivelAtual].preco) {
                
                // Processa a compra
                jogadorMoney -= construcao->niveis[construcao->nivelAtual].preco;
                construcao->nivelAtual++;
                construcao->niveis[construcao->nivelAtual - 1].desbloqueado = true;
                construcao->tempoUltimaProducao = GetTime();
                
                // Aplica o efeito do nível
                switch (construcao->nivelAtual) {
                    case 1: AplicarEfeitoNivel1(c); break;
                    case 2: AplicarEfeitoNivel2(c); break;
                    case 3: AplicarEfeitoNivel3(c); break;
                }
                
                break; // Só processa uma compra por clique
            }
        }
    }
}

// Helper: Try to spawn 'count' animals of the given type into the provided array
static void TrySpawnAnimals(Animal arr[], Rectangle area, int count, TipoAnimal tipo) {
    for (int k = 0; k < count; k++) {
        for (int i = 0; i < MAX_ANIMALS; i++) {
            if (!arr[i].active) {
                Vector2 pos = { area.x + (float)GetRandomValue(0, (int)area.width), area.y + (float)GetRandomValue(0, (int)area.height) };
                InicializarAnimal(&arr[i], tipo, pos);
                break; // spawned one, go to next
            }
        }
    }
}

void AtualizarAprimoramentos(int& GalinhasAtuais, int& VacasAtuais, 
                            int& PorcosAtuais, int& OvelhasAtuais,
                            Animal galinhas[], Animal vacas[], Animal porcos[], Animal ovelhas[],
                            Rectangle Galinheiro, Rectangle Curral, Rectangle Chiqueiro, Rectangle CampodasOvelhas) {
    
    float tempoAtual = GetTime();
    
    // Atualiza cada construção
    ConstrucaoAprimoravel* construcoes[] = {&galinheiro, &curral, &chiqueiro, &abrigo};
    int* animaisComprados[] = {&GalinhasAtuais, &VacasAtuais, &PorcosAtuais, &OvelhasAtuais};
    
    for (int c = 0; c < 4; c++) {
        ConstrucaoAprimoravel* construcao = construcoes[c];
        
        if (construcao->nivelAtual > 0 && tempoAtual - construcao->tempoUltimaProducao >= 15.0f) {
            int animaisParaAdicionar = construcao->nivelAtual; // Nível 1: +1, Nível 2: +2, Nível 3: +3
            
            if (*animaisComprados[c] + animaisParaAdicionar <= MAX_ANIMALS) {
                *animaisComprados[c] += animaisParaAdicionar;
                construcao->tempoUltimaProducao = tempoAtual;

                // Actually initialize (spawn) animals in the matching array so they appear in-game
                switch (c) {
                    case 0: // galinheiro -> galinhas
                        TrySpawnAnimals(galinhas, Galinheiro, animaisParaAdicionar, GALINHA);
                        break;
                    case 1: // curral -> vacas
                        TrySpawnAnimals(vacas, Curral, animaisParaAdicionar, VACA);
                        break;
                    case 2: // chiqueiro -> porcos
                        TrySpawnAnimals(porcos, Chiqueiro, animaisParaAdicionar, PORCO);
                        break;
                    case 3: // abrigo -> ovelhas
                        TrySpawnAnimals(ovelhas, CampodasOvelhas, animaisParaAdicionar, OVELHA);
                        break;
                }
            }
        }
    }
}

// ⚡ FUNÇÕES DE EFEITOS - IMPLEMENTE AQUI SEUS EFEITOS PERSONALIZADOS ⚡

void AplicarEfeitoNivel1(int tipoConstrucao) {
    // Efeitos para o nível 1 de cada construção
    switch (tipoConstrucao) {
        case 0: // Galinheiro
            // Exemplo: Aumenta velocidade de produção das galinhas em 20%
            // galinha[i].VelocidadeProducao *= 1.2f;
            break;
        case 1: // Curral
            // Exemplo: Vacas produzem 50% mais leite
            break;
        case 2: // Chiqueiro
            // Exemplo: Porcos dão 1 bacon extra
            break;
        case 3: // Abrigo
            // Exemplo: Ovelhas produzem lã 30% mais rápido
            break;
    }
}

void AplicarEfeitoNivel2(int tipoConstrucao) {
    // Efeitos para o nível 2 de cada construção
    switch (tipoConstrucao) {
        case 0: // Galinheiro
            // Exemplo: Galinhas são imunes a inimigos
            break;
        case 1: // Curral
            // Exemplo: Vacas dão leite de qualidade superior (vende por mais)
            break;
        case 2: // Chiqueiro
            // Exemplo: Porcos se reproduzem automaticamente
            break;
        case 3: // Abrigo
            // Exemplo: Ovelhas dão lã colorida (valor maior)
            break;
    }
}

void AplicarEfeitoNivel3(int tipoConstrucao) {
    // Efeitos para o nível 3 (máximo) de cada construção
    switch (tipoConstrucao) {
        case 0: // Galinheiro
            // Exemplo: Galinhas produzem ovos dourados
            break;
        case 1: // Curral
            // Exemplo: Vacas dão leite infinito
            break;
        case 2: // Chiqueiro
            // Exemplo: Porcos dão bacon premium
            break;
        case 3: // Abrigo
            // Exemplo: Ovelhas dão lã mágica
            break;
    }
}