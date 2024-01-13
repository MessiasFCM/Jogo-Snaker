#include "snaker.h"
#include <jogo.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

Snaker* cria_snaker(char *nome, int scoreAtual, int posX, int posY, int backupX, int backupY, int frutaX, int frutaY, int gerarFruta, int continuar, int continuarBackup, int direcaoCobra, int travaTela, int codigoTela, int seqCoordsCont, int velocidade, int skin){
	Snaker *s = (Snaker*)malloc(sizeof(Snaker));
	strcpy(s->nome, nome);
    s->scoreAtual = scoreAtual;
	s->posX = posX;
	s->posY = posY;
	s->backupX = backupX;
    s->backupY = backupY;
	s->frutaX = frutaX;
	s->frutaY = frutaY;
	s->gerarFruta = gerarFruta;
	s->continuar = continuar;
	s->continuarBackup = continuarBackup;
	s->direcaoCobra = direcaoCobra;
	s->travaTela = travaTela;
	s->codigoTela = codigoTela;
	s->seqCoordsCont = seqCoordsCont;
	s->velocidade = velocidade;
	s->skin = skin;
	return s;
}

char* recupera_nome(Snaker *s){ return s->nome; }
int recupera_score(Snaker *s){ return s->scoreAtual; }
int recupera_posX(Snaker *s){ return s->posX; }
int recupera_posY(Snaker *s){ return s->posY; }
int recupera_backupX(Snaker *s){ return s->backupX; }
int recupera_backupY(Snaker *s){ return s->backupY; }
int recupera_frutaX(Snaker *s){	return s->frutaX; }
int recupera_frutaY(Snaker *s){	return s->frutaY; }
int recupera_gerarFruta(Snaker *s){ return s->gerarFruta; }
int recupera_continuar(Snaker *s){	return s->continuar; }
int recupera_continuarBackup(Snaker *s){ return s->continuarBackup; }
int recupera_direcaoCobra(Snaker *s){ return s->direcaoCobra; }
int recupera_travaTela(Snaker *s){ return s->travaTela; }
int recupera_codigoTela(Snaker *s){ return s->codigoTela; }
int recupera_seqCoordsCont(Snaker *s){ return s->seqCoordsCont; }
int recupera_velocidade(Snaker *s){ return s->velocidade; }
int recupera_skin(Snaker *s){ return s->skin; }
void destroi_snaker(Snaker *s){ free(s); }
void imagemCobra(Snaker *s){ // Carrega imagem da cobra na tela
	if(s->continuar == 1){ desenha_imagem(s->backupX+5, s->backupY+5, s->skin == 0 ? "assets/CobraDIREITA.png" : "assets/CobraDIREITA2.png");
	}else if(s->continuar == 2){ desenha_imagem(s->backupX+5, s->backupY+5, s->skin == 0 ? "assets/CobraESQUERDA.png" : "assets/CobraESQUERDA2.png");
	}else if(s->continuar == 3){ desenha_imagem(s->backupX+5, s->backupY+5, s->skin == 0 ? "assets/CobraCIMA.png" : "assets/CobraCIMA2.png");
	}else if(s->continuar == 4){ desenha_imagem(s->backupX+5, s->backupY+5, s->skin == 0 ? "assets/CobraBAIXO.png" : "assets/CobraBAIXO2.png"); }
	for(int i = 10; i <= 620; i++){
		for(int j = 30; j <= 460; j++){
			if(i == s->backupX && j == s->backupY){
			}else if(s->seq[i][j] == 1){ desenha_imagem(i+5, j+5, s->skin == 0 ? "assets/Cobra.png" : "assets/CobraSEGMENTO2.png"); }
		}
	} 
}
void colisao(Snaker *s, int calculo){ // Colisao da cobra com ela mesma
	if(s->seq[s->posX][s->posY] == 1){
		int colisao = 0;
		for(int i = calculo; i <= s->seqCoordsCont; i++){
			if(s->seqCoords[i][0] == s->backupX && s->seqCoords[i][1] == s->backupY){ colisao++; }     
		}    
		if(colisao > 1 && s->scoreAtual>0){ s->codigoTela = 4; }
	}
}
void jogabilidade(Snaker *s){ // Andar da cobra
	if(s->travaTela == 0){
		if (tecla_pressionada(DIREITA)){
			if(s->posX <= 610){
				if((s->posY % 10 == 0) && (s->continuar != 2 || s->scoreAtual == 0)){ s->continuar = 1;
				}else{
					s->travaTela = 1;
					s->direcaoCobra = 1;
				}
			}else{ s->codigoTela = 4; }
		}else if (tecla_pressionada(ESQUERDA)){
			if(s->posX >= 20){
				if((s->posY % 10 == 0) && (s->continuar != 1 || s->scoreAtual == 0)){ s->continuar = 2;
				}else{
					s->travaTela = 1;
					s->direcaoCobra = 2;
				}
			}else{ s->codigoTela = 4; }
		}else if (tecla_pressionada(CIMA)){
			if(s->posY >= 40){
				if((s->posX % 10 == 0) && (s->continuar != 4 || s->scoreAtual == 0)){ s->continuar = 3;
				}else{
					s->travaTela = 1;
					s->direcaoCobra = 3;
				}
			}else{ s->codigoTela = 4; }
		}else if (tecla_pressionada(BAIXO)){
			if(s->posY <= 450){
				if((s->posX % 10 == 0) && (s->continuar != 3 || s->scoreAtual == 0)){ s->continuar = 4;
				}else{
					s->travaTela = 1;
					s->direcaoCobra = 4;
				}
			}else{ s->codigoTela = 4; }
		}
	}else{ mudarDirecao(s); } // Mudar a direção da cobra
	if (s->continuar == 1){
		if(s->posX <= 620){ 
			s->posX+= s->velocidade;
			if(s->posX%10==0){ s->backupX = s->posX; }
		}else{ s->codigoTela = 4; }
	}
	if(s->continuar == 2){
		if(s->posX >= 10){ 
			s->posX-= s->velocidade;
			if(s->posX%10==0){ s->backupX = s->posX; }
		}else{ s->codigoTela = 4; }
	}
	if(s->continuar == 3){
		if(s->posY >= 30){ 
			s->posY-= s->velocidade;
			if(s->posY%10==0){ s->backupY = s->posY; }
		}else{ s->codigoTela = 4;} 
	}
	if(s->continuar == 4){
		if(s->posY <= 460){ 
			s->posY+= s->velocidade;
			if(s->posY%10==0){ s->backupY = s->posY; }
		}else{ s->codigoTela = 4; }
	}
}
void mudarDirecao(Snaker *s){ // Mudar a direção da cobra
	if((s->direcaoCobra == 1) && (s->continuar != 2 || s->scoreAtual == 0)){
		if(s->posY % 10 == 0){
			s->continuar = 1;
			s->travaTela = 0;
			s->direcaoCobra = 0;
		}
	}else if((s->direcaoCobra == 2)  && (s->continuar != 1 || s->scoreAtual == 0)){
		if(s->posY % 10 == 0){
			s->continuar = 2;
			s->travaTela = 0;
			s->direcaoCobra = 0;
		}
	}else if((s->direcaoCobra == 3) && (s->continuar != 4 || s->scoreAtual == 0)){
		if(s->posX % 10 == 0){
			s->continuar = 3;
			s->travaTela = 0;
			s->direcaoCobra = 0;
		}
	}else if((s->direcaoCobra == 4)  && (s->continuar != 3 || s->scoreAtual == 0)){
		if(s->posX % 10 == 0){
			s->continuar = 4;
			s->travaTela = 0;
			s->direcaoCobra = 0;
		}
	}else{
		s->travaTela = 0;
		s->direcaoCobra = 0;
	}
}
void geradorDeFrutas(Snaker *s){ // Gera a fruta na imagem
	if(s->gerarFruta == 0){
		s->frutaX = 10 + rand() % 610;
		s->frutaY = 30 + rand() % 430;
		for(int i = 1; i<10; i++){
			if(s->frutaX%10 == i){
				if(i>=6){ s->frutaX+= 10 - i;
				}else{ s->frutaX-= i; }
			}
		}
		for(int i = 1; i<10; i++){
			if(s->frutaY%10 == i){
				if(i>=6){ s->frutaY+= 10 - i;
				}else{ s->frutaY-= i; }
			}
		}
		if(s->seq[s->frutaX][s->frutaY] == 0){ s->gerarFruta = 1; }
	}
	if(s->gerarFruta == 1){ desenha_imagem(s->frutaX+5, s->frutaY+5, "assets/FrutaVerme.png"); } 
}
void pegarFruta(Snaker *s){ // Pega a fruta na tela 
	if((s->frutaX == s->posX || s->frutaX == s->posX+9) && (s->frutaY == s->posY || s->frutaY == s->posY+9)){
		toca_som("assets/Comendo.mp3");
		s->scoreAtual++;
		s->gerarFruta = 0;
	}else{ s->gerarFruta = 1; }
}
void pausarTela(Snaker *s){ // Pausa o jogo em andamento
	if (tecla_acabou_de_ser_apertada('P')){
		if(s->continuar!=0){
			s->continuarBackup = s->continuar;
			s->continuar = 0;
		}else{ s->continuar = s->continuarBackup; }
	}
	if(s->continuar==0){ desenha_imagem(320, 240, "assets/Fundo_Pausado.png"); }
}
void atualizar(Snaker *s){ // Atualiza a tela em tempo real
	desenha_imagem(320, 240, "assets/Fundo_DificuldadesGrade.png");
	fonte("assets/ubuntu.ttf", 20);
	desenha_texto(15, 20, "Score: %d", s->scoreAtual*s->velocidade);
	if(s->velocidade == 1){ desenha_texto(290, 20, "Lento");
	}else if(s->velocidade == 2){ desenha_texto(290, 20, "Normal");
	}else{ desenha_texto(290, 20, "Rapido"); }
	pausarTela(s);
	if(s->continuar!=0){
		geradorDeFrutas(s);
		segmentoCobra(s);
		jogabilidade(s);
		pegarFruta(s);
	}
}
void segmentoCobra(Snaker *s){ // Segmento da cobra
	int contador = 0;
	if(s->posX%10 == 0 && s->posY%10 == 0){
		s->seq[s->posX][s->posY] = 1;
		s->seqCoords[s->seqCoordsCont][0] = s->posX;
		s->seqCoords[s->seqCoordsCont][1] = s->posY;
		s->seqCoordsCont++;
		for(int i = 10; i <= 620; i++){
			for(int j = 30; j <= 460; j++){
				if(s->seq[i][j] == 1){ contador++; }
			}
		} 
		int calculo = s->seqCoordsCont - contador;
		if(contador <= s->scoreAtual+1){ }else{
			s->seq[s->seqCoords[calculo][0]][s->seqCoords[calculo][1]] = 0;
		}
		colisao(s, calculo);
	}
	imagemCobra(s);
}
void adicionarDados(Snaker *s){ // Adiciona dados ao arquivo texto 
	lerDados(s);
	FILE *arquivo = fopen("assets/ranking.txt", "w");
	if(s->scoreAtual>s->scoreS[4]){
		s->scoreS[4] = s->scoreAtual;
		s->nomeS[4] = s->nome;
	}
	for(int i = 0; i<5; i++){
		for(int j = 0; j<5; j++){
			if(i != j){
				if(s->scoreS[j] < s->scoreS[i]){
					int copiaS = s->scoreS[i];
					s->scoreS[i] = s->scoreS[j];
					s->scoreS[j] = copiaS;   
					char *copiaN = s->nomeS[i];
					s->nomeS[i] = s->nomeS[j] ;
					s->nomeS[j] = copiaN;   
				}
			}
		}
	}
	char vetorScore[10];
	for(int i = 0; i<5; i++){
		itoa(s->scoreS[i], vetorScore, 10);
		fputs(s->nomeS[i], arquivo);
		fputc(',', arquivo);
		fputs(vetorScore, arquivo);
		fputc(',', arquivo);
		fputc('\n', arquivo);
	}
	fclose(arquivo);
}
void lerDados(Snaker *s){ // Le os dados do arquivo texto

	FILE *arquivo = fopen("assets/ranking.txt", "r");
	char buf[125];
	int cont = 0;
	int scoreL; 
	char nomeL[15];

	if(arquivo != NULL){
		fgets(buf, 125, arquivo);
		while(!feof(arquivo) && cont<5){
			strcpy(nomeL, strtok(buf,","));
			scoreL = atoi(strtok(NULL,","));
			// printf("Nome: %s Score: %d\n", nomeL, scoreL);
			s->scoreS[cont] = scoreL;
			for(int i = 0; i<15; i ++){
				s->nomeS[cont][i] = nomeL[i];
			}
			fgets(buf, 125, arquivo);
			cont++;
		}
	}
	fclose(arquivo);
	
	if(s->codigoTela==5){ // Escreve o rank na tela ranking
		cor(BRANCO);
		fonte("assets/ubuntu.ttf", 37);
		desenha_texto(215, 143, "%s - %d", s->nomeS[0], s->scoreS[0]);
		fonte("assets/ubuntu.ttf", 35);
		desenha_texto(225, 200, "%s - %d", s->nomeS[1], s->scoreS[1]);
		fonte("assets/ubuntu.ttf", 30);
		desenha_texto(240, 255, "%s - %d", s->nomeS[2], s->scoreS[2]);
		fonte("assets/ubuntu.ttf", 25);
		desenha_texto(255, 310, "%s - %d", s->nomeS[3], s->scoreS[3]);
		fonte("assets/ubuntu.ttf", 20);
		desenha_texto(265, 360, "%s - %d", s->nomeS[4], s->scoreS[4]);
	}
}