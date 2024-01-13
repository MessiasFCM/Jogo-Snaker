#ifndef SNAKER_H
#define SNAKER_H

typedef struct { // Struct do Snaker
	char nome[15];
    int scoreAtual;
	int posX;
    int posY;
    int backupX;
    int backupY;
    int frutaX;
    int frutaY;
    int gerarFruta;
    int continuar;
    int continuarBackup;
    int direcaoCobra;
    int travaTela;
    int codigoTela;
    int seqCoordsCont;
    int **seq;
    int **seqCoords;
    int *scoreS; 
	char **nomeS;
    int velocidade;
    int skin;
}Snaker;

Snaker* cria_snaker(char *nome, int scoreAtual, int posX, int posY, int backupX, int backupY, int frutaX, int frutaY, int gerarFruta, int continuar, int continuarBackup, int direcaoCobra, int travaTela, int codigoTela, int seqCoordsCont, int velocidade, int skin);
char* recupera_nome(Snaker *s);
int recupera_score(Snaker *s);
int recupera_posX(Snaker *s);
int recupera_posY(Snaker *s);
int recupera_backupX(Snaker *s);
int recupera_backupY(Snaker *s);
int recupera_frutaX(Snaker *s);
int recupera_frutaY(Snaker *s);
int recupera_gerarFruta(Snaker *s);
int recupera_continuar(Snaker *s);
int recupera_continuarBackup(Snaker *s);
int recupera_direcaoCobra(Snaker *s);
int recupera_travaTela(Snaker *s);
int recupera_codigoTela(Snaker *s);
int recupera_seqCoordsCont(Snaker *s);
int recupera_velocidade(Snaker *s);
int recupera_skin(Snaker *s);
void imagemCobra(Snaker *s);
void colisao(Snaker *s, int calculo);
void jogabilidade(Snaker *s);
void mudarDirecao(Snaker *s);
void geradorDeFrutas(Snaker *s);
void pegarFruta(Snaker *s);
void pausarTela(Snaker *s);
void atualizar(Snaker *s);
void segmentoCobra(Snaker *s);
void adicionarDados(Snaker *s);
void lerDados(Snaker *s);
void destroi_snaker(Snaker *s);

#endif