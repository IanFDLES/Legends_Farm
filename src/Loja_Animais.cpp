#include "Loja_Animais.hpp"
#include "raymath.h"
#include "stdio.h"


float precoVaca = 200.0f;
float precoGalinha = 10.0f;
float precoPorco = 80.0f;
float precoOvelha = 60.0f;

// Definições das variáveis de skins
SkinAnimal skinVaca, skinGalinha, skinPorco, skinOvelha;

void DrawSkinsScreen(Rectangle areaConteudo, float painelLateralLargura, Vector2 mousePoint,
                    int& VacasAtuais, int& GalinhasAtuais, int& PorcosAtuais, int& OvelhasAtuais,
                    float& jogadorMoney, Animal vacas[], Animal galinhas[], Animal porcos[], Animal ovelhas[],
                    Rectangle Curral, Rectangle Galinheiro, Rectangle Chiqueiro, Rectangle CampodasOvelhas) {
    
    // Título dentro da área de conteúdo
    DrawText("LOJA DE ANIMAIS", areaConteudo.x + 20, areaConteudo.y + 20, 30, YELLOW);
    DrawText("Clique para comprar", areaConteudo.x + 20, areaConteudo.y + 55, 20, LIGHTGRAY);
    
    float startY = areaConteudo.y + 90;
    float espacamento = 120;
    float cardWidth = painelLateralLargura - 40;
    float cardHeight = 100;
    
    // Skin Vaca
    Rectangle cardVaca = {areaConteudo.x + 20, startY, cardWidth, cardHeight};
    Color corCardVaca = CheckCollisionPointRec(mousePoint, cardVaca) ? 
                       (jogadorMoney >= precoVaca ? (Color){100, 200, 100, 255} : (Color){200, 100, 100, 255}) : 
                       (Color){60, 60, 70, 255};
    
    DrawRectangleRec(cardVaca, corCardVaca);
    DrawRectangleLinesEx(cardVaca, 2, DARKGRAY);
    
    // Ícone da vaca
    float iconScale = 0.06f;
    float iconW = skinVaca.textura.width * iconScale;
    float iconH = skinVaca.textura.height * iconScale;
    DrawTexturePro(skinVaca.textura, 
                  (Rectangle){0, 0, (float)skinVaca.textura.width, (float)skinVaca.textura.height},
                  (Rectangle){cardVaca.x + 10, cardVaca.y + cardHeight/2 - iconH/2, iconW, iconH},
                  (Vector2){0, 0}, 0.0f, WHITE);
    
    // Texto da vaca
    DrawText("VACA", cardVaca.x + iconW + 20, cardVaca.y + 15, 22, WHITE);
    DrawText(TextFormat("Preço: $%.0f", precoVaca), cardVaca.x + iconW + 20, cardVaca.y + 45, 18, 
            jogadorMoney >= precoVaca ? GREEN : RED);
    DrawText(TextFormat("Atuais: %d", VacasAtuais), cardVaca.x + iconW + 20, cardVaca.y + 70, 16, LIGHTGRAY);
    
    // Skin Galinha
    Rectangle cardGalinha = {areaConteudo.x + 20, startY + espacamento, cardWidth, cardHeight};
    Color corCardGalinha = CheckCollisionPointRec(mousePoint, cardGalinha) ? 
                          (jogadorMoney >= precoGalinha ? (Color){100, 200, 100, 255} : (Color){200, 100, 100, 255}) : 
                          (Color){60, 60, 70, 255};
    
    DrawRectangleRec(cardGalinha, corCardGalinha);
    DrawRectangleLinesEx(cardGalinha, 2, DARKGRAY);
    
    // Ícone da galinha
    iconScale = 0.06f;
    iconW = skinGalinha.textura.width * iconScale;
    iconH = skinGalinha.textura.height * iconScale;
    DrawTexturePro(skinGalinha.textura, 
                  (Rectangle){0, 0, (float)skinGalinha.textura.width, (float)skinGalinha.textura.height},
                  (Rectangle){cardGalinha.x + 10, cardGalinha.y + cardHeight/2 - iconH/2, iconW, iconH},
                  (Vector2){0, 0}, 0.0f, WHITE);
    
    // Texto da galinha
    DrawText("GALINHA", cardGalinha.x + iconW + 20, cardGalinha.y + 15, 22, WHITE);
    DrawText(TextFormat("Preço: $%.0f", precoGalinha), cardGalinha.x + iconW + 20, cardGalinha.y + 45, 18, 
            jogadorMoney >= precoGalinha ? GREEN : RED);
    DrawText(TextFormat("Atuais: %d", GalinhasAtuais), cardGalinha.x + iconW + 20, cardGalinha.y + 70, 16, LIGHTGRAY);
    
    // Skin Porco
    Rectangle cardPorco = {areaConteudo.x + 20, startY + espacamento * 2, cardWidth, cardHeight};
    Color corCardPorco = CheckCollisionPointRec(mousePoint, cardPorco) ? 
                        (jogadorMoney >= precoPorco ? (Color){100, 200, 100, 255} : (Color){200, 100, 100, 255}) : 
                        (Color){60, 60, 70, 255};
    
    DrawRectangleRec(cardPorco, corCardPorco);
    DrawRectangleLinesEx(cardPorco, 2, DARKGRAY);
    
    // Ícone do porco
    iconScale = 0.06f;
    iconW = skinPorco.textura.width * iconScale;
    iconH = skinPorco.textura.height * iconScale;
    DrawTexturePro(skinPorco.textura, 
                  (Rectangle){0, 0, (float)skinPorco.textura.width, (float)skinPorco.textura.height},
                  (Rectangle){cardPorco.x + 10, cardPorco.y + cardHeight/2 - iconH/2, iconW, iconH},
                  (Vector2){0, 0}, 0.0f, WHITE);
    
    // Texto do porco
    DrawText("PORCO", cardPorco.x + iconW + 20, cardPorco.y + 15, 22, WHITE);
    DrawText(TextFormat("Preço: $%.0f", precoPorco), cardPorco.x + iconW + 20, cardPorco.y + 45, 18, 
            jogadorMoney >= precoPorco ? GREEN : RED);
    DrawText(TextFormat("Atuais: %d", PorcosAtuais), cardPorco.x + iconW + 20, cardPorco.y + 70, 16, LIGHTGRAY);
    
    // Skin Ovelha
    Rectangle cardOvelha = {areaConteudo.x + 20, startY + espacamento * 3, cardWidth, cardHeight};
    Color corCardOvelha = CheckCollisionPointRec(mousePoint, cardOvelha) ? 
                         (jogadorMoney >= precoOvelha ? (Color){100, 200, 100, 255} : (Color){200, 100, 100, 255}) : 
                         (Color){60, 60, 70, 255};
    
    DrawRectangleRec(cardOvelha, corCardOvelha);
    DrawRectangleLinesEx(cardOvelha, 2, DARKGRAY);
    
    // Ícone da ovelha
    iconScale = 0.06f;
    iconW = skinOvelha.textura.width * iconScale;
    iconH = skinOvelha.textura.height * iconScale;
    DrawTexturePro(skinOvelha.textura, 
                  (Rectangle){0, 0, (float)skinOvelha.textura.width, (float)skinOvelha.textura.height},
                  (Rectangle){cardOvelha.x + 10, cardOvelha.y + cardHeight/2 - iconH/2, iconW, iconH},
                  (Vector2){0, 0}, 0.0f, WHITE);
    
    // Texto da ovelha
    DrawText("OVELHA", cardOvelha.x + iconW + 20, cardOvelha.y + 15, 22, WHITE);
    DrawText(TextFormat("Preço: $%.0f", precoOvelha), cardOvelha.x + iconW + 20, cardOvelha.y + 45, 18, 
            jogadorMoney >= precoOvelha ? GREEN : RED);
    DrawText(TextFormat("Atuais: %d", OvelhasAtuais), cardOvelha.x + iconW + 20, cardOvelha.y + 70, 16, LIGHTGRAY);
}



void ProcessarCompraLoja(Rectangle areaConteudo, float painelLateralLargura, Vector2 mousePoint,
                        float& jogadorMoney, 
                        int& VacasAtuais, int& GalinhasAtuais, int& PorcosAtuais, int& OvelhasAtuais,
                        Animal vacas[], Animal galinhas[], Animal porcos[], Animal ovelhas[],
                        Rectangle Curral, Rectangle Galinheiro, Rectangle Chiqueiro, Rectangle CampodasOvelhas) {
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        float startY = areaConteudo.y + 90;
        float espacamento = 120;
        float cardWidth = painelLateralLargura - 40;
        float cardHeight = 100;
        
        Rectangle cardVaca = {areaConteudo.x + 20, startY, cardWidth, cardHeight};
        Rectangle cardGalinha = {areaConteudo.x + 20, startY + espacamento, cardWidth, cardHeight};
        Rectangle cardPorco = {areaConteudo.x + 20, startY + espacamento * 2, cardWidth, cardHeight};
        Rectangle cardOvelha = {areaConteudo.x + 20, startY + espacamento * 3, cardWidth, cardHeight};
        
        // Comprar Vaca
        if (CheckCollisionPointRec(mousePoint, cardVaca) && jogadorMoney >= precoVaca && VacasAtuais < MAX_ANIMALS) {
            jogadorMoney -= precoVaca;
            VacasAtuais++;
            for (int i = 0; i < MAX_ANIMALS; i++) {
                if (!vacas[i].active) {
                    // initialize purchased cow with correct type
                    InicializarAnimal(&vacas[i], VACA, 
                                    (Vector2){Curral.x + (float)GetRandomValue(0, (int)Curral.width), 
                                             Curral.y + (float)GetRandomValue(0, (int)Curral.height)});
                    break;
                }
            }
        }
        
        // Comprar Galinha
        if (CheckCollisionPointRec(mousePoint, cardGalinha) && jogadorMoney >= precoGalinha && GalinhasAtuais < MAX_ANIMALS) {
            jogadorMoney -= precoGalinha;
            GalinhasAtuais++;
            for (int i = 0; i < MAX_ANIMALS; i++) {
                if (!galinhas[i].active) {
                    InicializarAnimal(&galinhas[i], GALINHA, 
                                    (Vector2){Galinheiro.x + (float)GetRandomValue(0, (int)Galinheiro.width), 
                                             Galinheiro.y + (float)GetRandomValue(0, (int)Galinheiro.height)});
                    break;
                }
            }
        }
        
        // Comprar Porco
        if (CheckCollisionPointRec(mousePoint, cardPorco) && jogadorMoney >= precoPorco && PorcosAtuais < MAX_ANIMALS) {
            jogadorMoney -= precoPorco;
            PorcosAtuais++;
            for (int i = 0; i < MAX_ANIMALS; i++) {
                if (!porcos[i].active) {
                    InicializarAnimal(&porcos[i], PORCO, 
                                    (Vector2){Chiqueiro.x + (float)GetRandomValue(0, (int)Chiqueiro.width), 
                                             Chiqueiro.y + (float)GetRandomValue(0, (int)Chiqueiro.height)});
                    break;
                }
            }
        }
        
        // Comprar Ovelha
        if (CheckCollisionPointRec(mousePoint, cardOvelha) && jogadorMoney >= precoOvelha && OvelhasAtuais < MAX_ANIMALS) {
            jogadorMoney -= precoOvelha;
            OvelhasAtuais++;
            for (int i = 0; i < MAX_ANIMALS; i++) {
                if (!ovelhas[i].active) {
                    InicializarAnimal(&ovelhas[i], OVELHA, 
                                    (Vector2){CampodasOvelhas.x + (float)GetRandomValue(0, (int)CampodasOvelhas.width), 
                                             CampodasOvelhas.y + (float)GetRandomValue(0, (int)CampodasOvelhas.height)});
                    break;
                }
            }
        }
    }
}