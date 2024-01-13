#include <jogo.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "snaker.h"

#define MAX_TAM 100

// Variaveis Gerais
char nome[15];
static int travaZero = 0;

int main() { // Classe main
    printf("\nBEM VINDO SNAKER\n");
    printf("Insira seu nick: ");
    scanf("%s", nome); // Nick
    printf("\nCarregando jogo...\n");
    Snaker *s = cria_snaker(nome, 0, 320, 240, 320, 240, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0); // Iniciando a struct
    s->seq = malloc(sizeof(int *) * 621); 
    for (int i=0; i<621; i++){ s->seq[i] = (int*) malloc (461 * sizeof(int));}
    s->seqCoords = malloc(sizeof(int *) * 262300);
    for (int i=0; i<262300; i++){ s->seqCoords[i] = (int*) malloc (2 * sizeof(int)); }
    s->nomeS = malloc(sizeof(char *) * 5);
    for (int i=0; i<5; i++){ s->nomeS[i] = (char*) malloc (15 * sizeof(char)); }
    s->scoreS = malloc(sizeof(int *) * 5);

    abre_janela(640, 480); // Abrir tela

    while (janela_esta_aberta()){ // Carregar Jogo

        if(!som_esta_tocando("assets/TopGear.mp3")){ // Tocar música
            toca_som_em_loop("assets/TopGear.mp3");
        }

        if (tecla_pressionada(ESC)){ janela_deve_fechar(); } // Fechar Tela
        if(s->codigoTela == 0){ // Tela Inicial - MENU
            s->scoreAtual = 0;
            travaZero = 0;
            desenha_imagem(320, 240, "assets/Fundo.png"); 
            if (tecla_pressionada('C')){ s->skin = 0; }
            if (tecla_pressionada('R')){ s->skin = 1; }
            if (tecla_pressionada('1') || (botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) && mouse_x >= 70 && mouse_x <= 220 && mouse_y >= 245 && mouse_y <= 320)){ s->codigoTela = 1;
            }else if (tecla_pressionada('2') || botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) && mouse_x >= 240 && mouse_x <= 390 && mouse_y >= 245 && mouse_y <= 320){ s->codigoTela = 2;
            }else if (tecla_pressionada('3') || botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) && mouse_x >= 410 && mouse_x <= 560 && mouse_y >= 245 && mouse_y <= 320){ s->codigoTela = 3;
            }else if (tecla_pressionada('4') || botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) && mouse_x >= 260 && mouse_x <= 370 && mouse_y >= 345 && mouse_y <= 380){ s->codigoTela = 5; }  
        }
        if(s->codigoTela == 1){ s->velocidade = 1; atualizar(s); } // Tela Dificuldade Fácil
        if(s->codigoTela == 2){ s->velocidade = 2; atualizar(s); } // Tela Dificuldade Normal
        if(s->codigoTela == 3){ s->velocidade = 5; atualizar(s); } // Tela Dificuldade Difícil
        if(s->codigoTela == 4){ // Tela Game Over
            desenha_imagem(320, 240, "assets/Fundo_GameOver.png");
            if(!som_esta_tocando("assets/Morri.mp3") && travaZero == 0){ 
                s->scoreAtual = s->scoreAtual * s->velocidade;
                toca_som("assets/Morri.mp3"); 
                adicionarDados(s); // Adiciona dados ao arquivo texto
            }
            cor(PRETO);
            fonte("assets/ubuntu.ttf", 40);
            if(s->scoreAtual>999){ 
                desenha_texto(230, 278, "Score: %d", s->scoreAtual);
            }else if(s->scoreAtual>99){ 
                desenha_texto(240, 278, "Score: %d", s->scoreAtual);
            }else{
                desenha_texto(250, 278, "Score: %d", s->scoreAtual);
            }
            cor(BRANCO);

            for(int i = 10; i < 621; i++){
                for(int j = 30; j < 461; j++){ 
                    s->seq[i][j] = 0; 
                }
            }
            for(int i = 0; i < 262300; i++){
                for(int j = 0; j < 2; j++){ 
                    s->seqCoords[i][j] = 0; 
                }
            }
            travaZero = 1;
            s->posX = 320;
            s->posY = 240;
            s->backupX = 320;
            s->backupY = 240;
            s->frutaX = 0;
            s->frutaY = 0;
            s->gerarFruta = 0;
            s->continuar = 4;
            s->continuarBackup = 4;
            s->direcaoCobra = 0;
            s->travaTela = 0;
            s->seqCoordsCont = 0;
            s->velocidade = 0;
            if (tecla_pressionada(ESPACO) || (botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) && mouse_x >= 220 && mouse_x <= 415 && mouse_y >= 312 && mouse_y <= 360)){ s->codigoTela = 0;
            } else if (tecla_pressionada(ENTER) || botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) && mouse_x >= 260 && mouse_x <= 370 && mouse_y >= 370 && mouse_y <= 405){ s->codigoTela = 5; }
        }
        if(s->codigoTela == 5){ // Tela Ranking
            desenha_imagem(320, 240, "assets/Fundo_Ranking.png");
            lerDados(s);
            if (tecla_pressionada(ESPACO) || botao_mouse_acabou_de_ser_apertado(BOTAO_ESQUERDO) && mouse_x >= 270 && mouse_x <= 366 && mouse_y >= 401 && mouse_y <= 435){ s->codigoTela = 0; }
        }
    }
    fecha_janela();
}