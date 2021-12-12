#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Desenvolver um jogo de batalha naval em C que permita ao usuário jogar contra o computador.

int campo, acertosUsuario = 0, acertosComp = 0, i = 0; 
bool ganhador = false;

typedef struct {
  int pontoUsuario;
  int pontoComp;
} navios;

typedef struct{
  int pontoUsuario;
  int pontoComp;
} hidroaviao;

typedef struct {
  int pontoUsuario;
  int pontoComp;
} portaaviao;

// Requisito:	Utilização de structs para armazenar dados de usuários e ranking dos jogadores 
typedef struct {
  char nome[50];
  int pontos;
  int classificacao;
} jogadores;

navios navio;
hidroaviao hidro;
portaaviao porta;
jogadores jogador[3];

// Inicializa todas as posições do tabuleiro para o valor default de -1. Função sem retorno com parâmetros.

void inicializaTabuleiro (int tabuleiro[][campo]) {
  int lin, col;

  for (lin = 0; lin < campo; lin ++) {
    for (col = 0; col < campo; col ++) {
      tabuleiro[lin][col] = -1;
    }
  }
}

// Função que irá reconstruir o tabuleiro e mostrar na tela. Função sem retorno com parâmetros.

void mostraTabuleiro (int tabuleiro[][campo])
{
  int linha, coluna;

  if (campo == 10){
    printf("\n\t\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8 \t9 \t10");
    printf("\n");
    printf("\t_______________________________________");
    printf("\n");
  }
  else {
    printf("\n\t\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8 \t9 \t10 \t11 \t12 \t13 \t14 \t15");
    printf("\n");
    printf("\t________________________________________________________________");
    printf("\n");
  }
  
  for (linha = 0; linha < campo ; linha ++ ) {
    if (linha < 9){
      printf(" %d |", linha + 1);
    }
    else {
      printf("%d |", linha + 1);
    }

    // Requisito: Aloca e exibe nos mapas os tiros de cada jogador (usuário e computador). “-” para tiros na água. “X” para tiros certos. 

    for (coluna = 0; coluna < campo ; coluna ++ ) {

      if ((tabuleiro [linha][coluna] == -1) || (tabuleiro [linha][coluna] == 2) || (tabuleiro [linha][coluna] == 3) || (tabuleiro [linha][coluna] == 4)){
        printf("\t ");
        
      } else if (tabuleiro [linha][coluna] == 0) {
        printf("\t-");

      } else if (tabuleiro [linha][coluna] == 1) {
        printf("\tX");
      }
    }
    printf("\n");
  }
}

// Irá tornar o mapa do jogo visivel apenas para o usuário, para facilitar no momento de posicionar as embarcações. Função sem retorno com parâmetros.

void preVisu_Tabuleiro (int tabuleiro[][campo])
{
  int linha, coluna;

  if (campo == 10){
    printf("\n\t\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8 \t9 \t10");
    printf("\n");
    printf("\t_______________________________________");
    printf("\n");
  }
  else {
    printf("\n\t\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8 \t9 \t10 \t11 \t12 \t13 \t14 \t15");
    printf("\n");
    printf("\t________________________________________________________________");
    printf("\n");
  }
  
  for (linha = 0; linha < campo ; linha ++ ) {
    if (linha < 9){
      printf(" %d |", linha + 1);
    }
    else {
      printf("%d |", linha + 1);
    }

    for (coluna = 0; coluna < campo ; coluna ++ ) {

      if (tabuleiro [linha][coluna] == -1){
        printf("\t ");

      } else if ((tabuleiro [linha][coluna] == 2) || (tabuleiro [linha][coluna] == 3) || (tabuleiro [linha][coluna] == 4)) {
        printf("\tX");
      }
    }
    printf("\n");
  }
}

// Insere as embarcações de maneira randômica pelo tabuleiro (2 navios, 1 porta avião e 2 hidroaviões). Função sem retorno com parâmetros.

void inserirEmbarcacoes (int tabuleiro[][campo]){
  int linha, coluna, navio, limiteCol, limiteLin;
  int portaaviao, hidroaviao;
  bool repeat;

  limiteCol = campo - 2;
  limiteLin = campo - 1;
  repeat = true;

  // Insere os 2 navios (3 posições seguidas)
  // Requisito: Navios => 3 espaços 

  for (navio = 0; navio < 2; navio ++) {
    linha = rand() % campo;
    coluna = rand() % limiteCol;

    // Confirmar se a posição escolhida, não está sobrepondo outra.
    while (repeat){
      if ((tabuleiro[linha][coluna] == 2) || (tabuleiro[linha][coluna + 1] == 2) || (tabuleiro[linha][coluna + 2] == 2)) {
        linha = rand() % campo;
        coluna = rand() % limiteCol;
      }
      else {
        break;
      }
    }

    // Requisito: Ao acertar uma embarcação, o sistema deverá informar o tipo de embarcação. Assim, o usuário ou o computador que está jogando poderá ter noção espacial do próximo tiro;
    tabuleiro[linha][coluna] = 2;
    tabuleiro[linha][coluna + 1] = 2;
    tabuleiro[linha][coluna + 2] = 2;
  }

  // Insere os 2 hidroaviões (3 posições que se alteraram entre 2 linhas)
  // Requisito: Hidroaviões => 3 espaços 

  for (hidroaviao = 0; hidroaviao < 2; hidroaviao ++) {
    linha = 1 + rand() % limiteLin;
    coluna = rand() % limiteCol;

    // Confirmar se a posição escolhida, não está sobrepondo outra.
    while (repeat){
      if ((tabuleiro[linha][coluna] == 2) || (tabuleiro[linha][coluna + 1] == 2) || (tabuleiro[linha][coluna + 2] == 2) || (tabuleiro[linha - 1][coluna + 1] == 2)) {
        linha = rand() % campo;
        coluna = rand() % limiteCol;
      }
      else {
        break;
      }
    }

    // Requisito: Ao acertar uma embarcação, o sistema deverá informar o tipo de embarcação. Assim, o usuário ou o computador que está jogando poderá ter noção espacial do próximo tiro;
    tabuleiro[linha][coluna] = 3;
    tabuleiro[linha - 1][coluna + 1] = 3;
    tabuleiro[linha][coluna + 2] = 3;
  }

  // Insere os 1 porta aviões (4 posições seguidas)
  // Requisito: Porta avios => 4 espaços 

  limiteCol = campo - 3;
  
  for (portaaviao = 0; portaaviao < 1; portaaviao ++) {
    linha = rand() % campo;
    coluna = rand() % limiteCol;

    // Confirmar se a posição escolhida, não está sobrepondo outra.
    while (repeat){
      if ((tabuleiro[linha][coluna] == 2) || (tabuleiro[linha][coluna + 1] == 2) || (tabuleiro[linha][coluna + 2] == 2) || (tabuleiro[linha][coluna + 3] == 2)) {
        linha = rand() % campo;
        coluna = rand() % limiteCol;
      }
      else {
        break;
      }
    }

    // Requisito: Ao acertar uma embarcação, o sistema deverá informar o tipo de embarcação. Assim, o usuário ou o computador que está jogando poderá ter noção espacial do próximo tiro;
    tabuleiro[linha][coluna] = 4;
    tabuleiro[linha][coluna + 1] = 4;
    tabuleiro[linha][coluna + 2] = 4;
    tabuleiro[linha][coluna + 3] = 4;
  }
}

// Função que irá permitir ao usuário selecionar a linha e a coluna desejada. Função sem retorno com parâmetros.
// Requisito: Uso de ponteiros e passagem por referência

void escolhaLin_Col(int limiteLinMin, int limiteLinMax, int limiteColMin, int limiteColMax, int * lin, int * col) {

  int linha, coluna;

  printf ("Linha: ");
  scanf ("%d", &linha);

  linha = linha - 1;

  // Valida se o valor inserido para a linha é válido
  while (linha < limiteLinMin || linha > limiteLinMax){
    printf("\nPosição inválida. Por favor, insira um novo valor dentro do recomendado.\n");
    printf ("Linha: ");
    scanf ("%d", &linha);

    linha = linha - 1;
  }

  printf ("Coluna: ");
  scanf ("%d", &coluna);

  coluna = coluna - 1;

  // Valida se o valor inserido para a coluna é válido
  while (coluna < limiteColMin || coluna > limiteColMax){
    printf("\nPosição inválida. Por favor, insira um novo valor dentro do recomendado.\n");
    printf ("Coluna: ");
    scanf ("%d", &coluna);

    coluna = coluna - 1;
  }

  *lin = linha;
  *col = coluna;
}

// Insere as embarcações de maneira manual pelo tabuleiro (2 navios, 1 porta avião e 2 hidroaviões). Função sem retorno com parâmetros.

void inserirEmb_Man (int tabuleiro[][campo]){
  int linha, coluna, navio, portaaviao, hidroaviao;
  bool repeat = true;

  // Insere os 2 navios (3 posições seguidas)
  // Requisito: Navios => 3 espaços 

  printf("\n\nPosicione seus 2 navios (O navio tem 3 espaços, então escolha uma linha de 1 a 10 (ou 15 para mapa 15x15) e uma coluna de 1 a 8 (ou 13 para mapa 15x15) para a posição inicial).\n");

  for (navio = 0; navio < 2; navio ++) {

    printf("\nPré-Visualização do Tabuleiro do(a) %s\n", jogador[i].nome);
    preVisu_Tabuleiro(tabuleiro);

    escolhaLin_Col(0, campo - 1, 0, campo - 3, &linha, &coluna);

    // Confirmar se a posição escolhida, não está sobrepondo outra.
    while (repeat){
      if ((tabuleiro[linha][coluna] == 2) || (tabuleiro[linha][coluna + 1] == 2) || (tabuleiro[linha][coluna + 2] == 2)) {
        printf("\nSuas embarcações colidiram. Por favor, escolha outra posição inicial.\n");
        escolhaLin_Col(0, campo - 1, 0, campo - 3, &linha, &coluna);
      }
      else {
        break;
      }
    }

    // Requisito: Ao acertar uma embarcação, o sistema deverá informar o tipo de embarcação. Assim, o usuário ou o computador que está jogando poderá ter noção espacial do próximo tiro;
    tabuleiro[linha][coluna] = 2;
    tabuleiro[linha][coluna + 1] = 2;
    tabuleiro[linha][coluna + 2] = 2;
  }

  // Insere os 2 hidroaviões (3 posições que se alteraram entre 2 linhas)
  // Requisito: Hidroaviões => 3 espaços 

  printf("\n\nPosicione seus 2 hidroaviões (O hidroavião tem 3 espaços, alterando entre 2 linhas, então escolha uma linha de 2 a 10 (ou 15 para mapa 15x15), e uma coluna de 1 a 8 (ou 13 para mapa 15x15) para a posição inicial).\n");

  for (hidroaviao = 0; hidroaviao < 2; hidroaviao ++) {

    printf("\nPré-Visualização do Tabuleiro do(a) %s\n", jogador[i].nome);
    preVisu_Tabuleiro(tabuleiro);

    escolhaLin_Col(1, campo - 1, 0, campo - 3, &linha, &coluna);

    // Confirmar se a posição escolhida, não está sobrepondo outra.
    while (repeat){
      if ((tabuleiro[linha][coluna] == 2) || (tabuleiro[linha][coluna + 1] == 2) || (tabuleiro[linha][coluna + 2] == 2) || (tabuleiro[linha - 1][coluna + 1] == 2)) {
        printf("\nSuas embarcações colidiram. Por favor, escolha outra posição inicial.\n");
        escolhaLin_Col(1, campo - 1, 0, campo - 3, &linha, &coluna);
      }
      else {
        break;
      }
    }

    // Requisito: Ao acertar uma embarcação, o sistema deverá informar o tipo de embarcação. Assim, o usuário ou o computador que está jogando poderá ter noção espacial do próximo tiro;
    tabuleiro[linha][coluna] = 3;
    tabuleiro[linha - 1][coluna + 1] = 3;
    tabuleiro[linha][coluna + 2] = 3;
  }

  // Insere os 1 porta aviões (4 posições seguidas)
  // Requisito: Porta avios => 4 espaços 

  printf("\n\nPosicione seu porta avião (O porta avião tem 4 espaços, então escolha uma linha de 1 a 10 (ou 15 para mapa 15x15) e uma coluna de 1 a 7 (ou 12 para mapa 15x15) para a posição inicial).\n");
  
  for (portaaviao = 0; portaaviao < 1; portaaviao ++) {
    
    printf("\nPré-Visualização do Tabuleiro do(a) %s\n", jogador[i].nome);
    preVisu_Tabuleiro(tabuleiro);

    escolhaLin_Col(0, campo - 1, 0, campo - 4, &linha, &coluna);

    // Confirmar se a posição escolhida, não está sobrepondo outra.
    while (repeat){
      if ((tabuleiro[linha][coluna] == 2) || (tabuleiro[linha][coluna + 1] == 2) || (tabuleiro[linha][coluna + 2] == 2) || (tabuleiro[linha][coluna + 3] == 2)) {
        printf("\nSuas embarcações colidiram. Por favor, escolha outra posição inicial.\n");
        escolhaLin_Col(0, campo - 1, 0, campo - 4, &linha, &coluna);
      }
      else {
        break;
      }
    }

    // Requisito: Ao acertar uma embarcação, o sistema deverá informar o tipo de embarcação. Assim, o usuário ou o computador que está jogando poderá ter noção espacial do próximo tiro;
    tabuleiro[linha][coluna] = 4;
    tabuleiro[linha][coluna + 1] = 4;
    tabuleiro[linha][coluna + 2] = 4;
    tabuleiro[linha][coluna + 3] = 4;
  }
}

// Função que permite ao usuário escolher a posição (linha x coluna) para tentar afundar alguma embarcação do oponente. Função com retorno com parâmetros.

bool darTiroUsuario (int tabuleiro[][campo]){

  bool posicaoInvalida = true;
  int linha, coluna;

  printf ("\nEscolha a posição em que você acredita que esteja a embarcação do oponente. \n");

  while (posicaoInvalida) {
    escolhaLin_Col(0, campo - 1, 0, campo - 1, &linha, &coluna);

    // Requisito: Ao acertar uma embarcação, o sistema deverá informar o tipo de embarcação. Assim, o usuário ou o computador que está jogando poderá ter noção espacial do próximo tiro;

    if ((tabuleiro[linha][coluna] == 2) || (tabuleiro [linha][coluna] == 3) || (tabuleiro [linha][coluna] == 4)) {
      
      if (tabuleiro[linha][coluna] == 2) {
        printf("\nAcertou um navio!\n");
        navio.pontoUsuario = navio.pontoUsuario + 1;
      }
        
      else if (tabuleiro[linha][coluna] == 3) {
        printf("\nAcertou um hidroavião!\n");
        hidro.pontoUsuario = hidro.pontoUsuario + 1;
      }

      else if (tabuleiro[linha][coluna] == 4) {
        printf("\nAcertou um porta avião!\n");
        porta.pontoUsuario = porta.pontoUsuario + 1;
      }

      tabuleiro[linha][coluna] = 1;
      posicaoInvalida = false;
      return true;
    }

    else if (tabuleiro[linha][coluna] == -1) {
      tabuleiro[linha][coluna] = 0;
      posicaoInvalida = false;
      return false;
    }

    else {
      printf("\nPosição inválida, tente novamente.\n");
    }
  }

  return false;
}

// Função que permite ao computador escolher a posição (linha x coluna) de maneira randômica para tentar afundar alguma embarcação do oponente. Função com retorno com parâmetros.

bool darTiroComp (int tabuleiro[][campo]){

  bool posicaoInvalida = true;
  int linha, coluna;

  while (posicaoInvalida) {
    linha = rand() % campo;
    coluna = rand() % campo;

    // Requisito: Ao acertar uma embarcação, o sistema deverá informar o tipo de embarcação. Assim, o usuário ou o computador que está jogando poderá ter noção espacial do próximo tiro;

    if ((tabuleiro[linha][coluna] == 2) || (tabuleiro [linha][coluna] == 3) || (tabuleiro [linha][coluna] == 4)) {
      
      if (tabuleiro[linha][coluna] == 2) {
        printf("\nAcertou um navio!\n");
        navio.pontoComp = navio.pontoComp + 1;
      }
        
      else if (tabuleiro[linha][coluna] == 3) {
        printf("\nAcertou um hidroavião!\n");
        hidro.pontoComp = hidro.pontoComp + 1;
      }

      else if (tabuleiro[linha][coluna] == 4) {
        printf("\nAcertou um porta avião!\n");
        porta.pontoComp = porta.pontoComp + 1;
      }

      tabuleiro[linha][coluna] = 1;
      posicaoInvalida = false;
      return true;
    }

    else if (tabuleiro[linha][coluna] == -1) {
      tabuleiro[linha][coluna] = 0;
      posicaoInvalida = false;
      return false;
    }  
  }

  return false;
}

// Função que irá validar o número de acertos, e verificar quem ganhou. Função com retorno sem parâmetros.
// Requisito: o	Vence o jogo o jogador que afundar 3 embarcações primeiro.

bool validarGanhador() {

  if (acertosUsuario >= 9) {
    if (porta.pontoUsuario == 4) {
      if ((navio.pontoUsuario == 6) || (hidro.pontoUsuario == 6) || (navio.pontoUsuario == 3 && hidro.pontoUsuario == 3)){
        printf("\n\t\tParabéns, o(a) %s ganhou!\n", jogador[i].nome);
        return true;
      }
      else {
        return false;
      }
    }
    else if ((navio.pontoUsuario == 6 && hidro.pontoUsuario == 3) || (navio.pontoUsuario == 3 && hidro.pontoUsuario == 6)){
      printf("\n\t\tParabéns, o(a) %s ganhou!\n", jogador[i].nome);
      return true;
    }
    else {
      return false;
    }
    
  }

  else if (acertosComp >= 9) {
    if (porta.pontoComp == 4) {
      if ((navio.pontoComp == 6) || (hidro.pontoComp == 6) || (navio.pontoComp == 3 && hidro.pontoComp == 3)){
        printf("\n\t\tO computador ganhou! Tente novamente na próxima.\n");
        return true;
      }
      else {
        return false;
      }
    }
    else if ((navio.pontoComp == 6 && hidro.pontoComp == 3) || (navio.pontoComp == 3 && hidro.pontoComp == 6)){
      printf("\n\t\tO computador ganhou! Tente novamente na próxima.\n");
      return true;
    }
    else {
      return false;
    }
  }
}

// Função que irá apresentar o ranking
// Requisito:	Utilização de structs para armazenar dados de usuários e ranking dos jogadores. Função sem retorno sem parâmetros

void classificacaoUsuarios() {

  printf("\n\t\t\tRanking de vitórias.\n");

  if ((jogador[0].pontos > jogador[1].pontos) && (jogador[0].pontos > jogador[2].pontos)) {
    printf("\nO(a) jogador(a) em primeiro lugar é: %s. Com %d pontos.\n", jogador[0].nome, jogador[0].pontos);
    jogador[0].classificacao = 1;

    if (jogador[1].pontos > jogador[2].pontos) {
      printf("\nO(a) jogador(a) em segundo lugar é: %s. Com %d pontos.\n", jogador[1].nome, jogador[1].pontos);
      jogador[1].classificacao = 2;
      printf("\nO(a) jogador(a) em terceiro lugar é: %s. Com %d pontos.\n", jogador[2].nome, jogador[2].pontos);
      jogador[2].classificacao = 3;
    }
    else {
      printf("\nO(a) jogador(a) em segundo lugar é: %s. Com %d pontos.\n", jogador[2].nome, jogador[2].pontos);
      jogador[2].classificacao = 2;
      printf("\nO(a) jogador(a) em terceiro lugar é: %s. Com %d pontos.\n", jogador[1].nome, jogador[1].pontos);
      jogador[1].classificacao = 3;
    }
  }
  else if (jogador[1].pontos > jogador[2].pontos) {
    printf("\nO(a) jogador(a) em primeiro lugar é: %s. Com %d pontos.\n", jogador[1].nome, jogador[1].pontos);
    jogador[1].classificacao = 1;

    if (jogador[0].pontos > jogador[2].pontos) {
      printf("\nO(a) jogador(a) em segundo lugar é: %s. Com %d pontos.\n", jogador[0].nome, jogador[0].pontos);
      jogador[0].classificacao = 2;
      printf("\nO(a) jogador(a) em terceiro lugar é: %s. Com %d pontos.\n", jogador[2].nome, jogador[2].pontos);
      jogador[2].classificacao = 3;
    }
    else {
      printf("\nO(a) jogador(a) em segundo lugar é: %s. Com %d pontos.\n", jogador[2].nome, jogador[2].pontos);
      jogador[2].classificacao = 2;
      printf("\nO(a) jogador(a) em terceiro lugar é: %s. Com %d pontos.\n", jogador[0].nome, jogador[0].pontos);
      jogador[0].classificacao = 3;
    }
  }
  else {
    printf("\nO(a) jogador(a) em primeiro lugar é: %s. Com %d pontos.\n", jogador[2].nome, jogador[2].pontos);
    jogador[2].classificacao = 1;

    if (jogador[0].pontos > jogador[1].pontos) {
      printf("\nO(a) jogador(a) em segundo lugar é: %s. Com %d pontos.\n", jogador[0].nome, jogador[0].pontos);
      jogador[0].classificacao = 2;
      printf("\nO(a) jogador(a) em terceiro lugar é: %s. Com %d pontos.\n", jogador[1].nome, jogador[1].pontos);
      jogador[1].classificacao = 3;
    }
    else {
      printf("\nO(a) jogador(a) em segundo lugar é: %s. Com %d pontos.\n", jogador[1].nome, jogador[1].pontos);
      jogador[1].classificacao = 2;
      printf("\nO(a) jogador(a) em terceiro lugar é: %s. Com %d pontos.\n", jogador[0].nome, jogador[0].pontos);
      jogador[0].classificacao = 3;
    }
  }
}

// Jogada do Usuário - Chamada das funções que irão compor a jogada. Função sem retorno com parâmetros.

void jogadaUsuario (int tabuleiro[][campo]){

  bool acertou;

  printf("\n\t\t\tUsuário realize sua jogada.\n");
  printf("\nTabuleiro do Computador.\n");
  mostraTabuleiro(tabuleiro);
  acertou = darTiroUsuario(tabuleiro);

  if (acertou){
    printf("\nTabuleiro do Computador.\n");
    mostraTabuleiro(tabuleiro);
    acertosUsuario = acertosUsuario + 1;

    if (acertosUsuario >= 9) {

      // Em caso de ter acertado um porta avião, e a embarcação não ter sida afundada por completo, é preciso de uma verificação mais detalhada.
      ganhador = validarGanhador();

      if (ganhador == false) {
        // Requisito: Enquanto o jogador estiver acertando embarcações continua atirando.
        jogadaUsuario(tabuleiro);
      }
      else {
        jogador[i].pontos = jogador[i].pontos + 1;
      }
    }
    else {
      // Requisito: Enquanto o jogador estiver acertando embarcações continua atirando.
      jogadaUsuario(tabuleiro);
    }
  }
  else {
    printf("\nErrou!\n");
    printf("\nTabuleiro do Computador.\n");
    mostraTabuleiro(tabuleiro);
  }
}

// Jogada do Computador - Chamada das funções que irão compor a jogada. Função sem retorno com parâmetros.

void jogadaComp (int tabuleiro[][campo]){
  
  bool acertou, ganhador = false;

  printf("\n\t\t\tComputador realize sua jogada.\n");
  acertou = darTiroComp(tabuleiro);

  if (acertou){
    printf("\nTabuleiro do(a) %s.\n", jogador[i].nome);
    mostraTabuleiro(tabuleiro);
    acertosComp = acertosComp + 1;

    if (acertosComp >= 9) {

      // Em caso de ter acertado um porta avião, e a embarcação não ter sida afundada por completo, é preciso de uma verificação mais detalhada.
      ganhador = validarGanhador();

      if (ganhador == false) {
        // Requisito: Enquanto o jogador estiver acertando embarcações continua atirando.
        jogadaComp(tabuleiro);
      }
    }
    else {
      // Requisito: Enquanto o jogador estiver acertando embarcações continua atirando.
      jogadaComp(tabuleiro);
    }
  }
  else {
    printf("\nErrou!\n");
    printf("\nTabuleiro do(a) %s.\n", jogador[i].nome);
    mostraTabuleiro(tabuleiro);
  }
}

// Função principal

int main() {

  system("@cls||clear");

  bool playAgain = true;
  char decisao, insercao, comecar, nome;

  navio.pontoUsuario = 0;
  navio.pontoComp = 0;
  hidro.pontoUsuario = 0;
  hidro.pontoComp = 0;
  porta.pontoUsuario = 0;
  porta.pontoComp = 0;

  printf("Insira o primeiro nome do(a) Jogador(a): ");
  scanf("%50s", jogador[i].nome);

  while (playAgain) {

    // Usuário pode escolher o tamanho do mapa [10x10] ou [15x15].

    printf("Bem vindo a Batalha Naval! Você gostaria de jogar em um campo 10x10 (digite 10) ou 15x15 (digite 15) ?  ");
    scanf("%d", &campo);

    if (campo != 10 && campo != 15) {
      printf("\nValor inválido, por favor reinicie o jogo!");
    }

    else {

      // Requisito: Armazenamento do mapa do jogo em matriz que deve ter o tamanho escolhido pelo usuário ao iniciar o jogo. Matrizes 10x10 ou 15x15.

      int tabuleiroUsuario[campo][campo];
      int tabuleiroComp[campo][campo];
      int primeiroJog, segundoJog;

      // Requisito: Na sequência, através de uma interface definida pelo sistema, o usuário irá posicionar suas embarcações (2 navios, 1 porta aviões e 2 hidroaviões). 

      inicializaTabuleiro(tabuleiroUsuario);

      // Usuário pode escolher que ele quer que as embarcações sejam colocadas manual ou automaticamente.
      // Requisito:	Ao iniciar o jogo, o usuário será solicitado a escolher o tamanho do mapa (10x10 ou 15x15). 

      printf ("\nGostaria de inserir as embarcações manual (digite M) ou automaticamente (digite A): ");

      // Limpar o buffer da variável "insercao"
      while ((insercao = getchar()) != '\n' && insercao != EOF);
      scanf (" %c", &insercao);

      while (insercao != 'M' && insercao != 'm' && insercao != 'A' && insercao != 'a'){
        printf("\nEscolha inválida, por favor digite apenas M ou A: ");
        while ((insercao = getchar()) != '\n' && insercao != EOF);
        scanf (" %c", &insercao);
      }

      if (insercao == 'M' || insercao == 'm') {
        inserirEmb_Man(tabuleiroUsuario);
      }

      else {
        inserirEmbarcacoes(tabuleiroUsuario);
        printf("\nSuas embarcações foram posicionadas da seguinte maneira.\n");
      }

      // Requisito: Após o usuário fazer suas escolhas, o sistema sorteará automaticamente as posições de suas embarcações no mapa.
      
      inicializaTabuleiro(tabuleiroComp);
      inserirEmbarcacoes(tabuleiroComp);

      printf("\nTabuleiro do %s.\n", jogador[i].nome);
      preVisu_Tabuleiro(tabuleiroUsuario);
      // printf("\n\nTabuleiro do Computador.\n");
      // preVisu_Tabuleiro(tabuleiroComp);

      printf("\nPressione Enter para continuar.\n");
      system("read -p 'Press Enter to continue...' var");

      system("@cls||clear");

      // Para escolher quem irá iniciar o jogo haverá um sorteio de 0 a 19.
      // Requisito:	O sistema sorteará quem começará o jogo: o usuário ou o sistema.

      primeiroJog = rand() %20;

      // Caso o número seja par, o usuário iniciará jogando.
      if (primeiroJog % 2 == 0) {
        printf("\nO %s começa jogando.\n", jogador[i].nome);
        segundoJog = 1;
      }

      else {
        printf("\nO Computador começa jogando.\n");
        segundoJog = 1;
      }

      while ((acertosUsuario < 16) && (acertosComp < 16) && (ganhador == false)){

        system("@cls||clear");

        if (primeiroJog % 2 == 0){
          jogadaUsuario(tabuleiroComp);
          jogadaComp(tabuleiroUsuario);
        }

        else {
          jogadaComp(tabuleiroUsuario);
          jogadaUsuario(tabuleiroComp);
        }

        system("@cls||clear");

        printf("\nTabuleiro do(a) %s.\n", jogador[i].nome);
        mostraTabuleiro(tabuleiroUsuario);
        printf("\n\nTabuleiro do Computador.\n");
        mostraTabuleiro(tabuleiroComp);

        printf("\nPressione Enter para continuar.\n");
        system("read -p 'Press Enter to continue...' var");

        // Em caso de ter acertado um porta avião, e a embarcação não ter sida afundada por completo, é preciso de uma verificação mais detalhada.
        if (acertosComp >= 9 || acertosUsuario >= 9) {
          ganhador = validarGanhador();
        }
      }      
    }

    classificacaoUsuarios();

    // Requisito: Ao final de cada partida, o sistema pergunta se deseja continuar para um novo jogo ou encerrar.

    printf ("\nGostaria de jogar novamente (digite S para Sim ou N para Não)? ");
    scanf (" %c", &decisao);

    while (decisao != 'S' && decisao != 's' && decisao != 'N' && decisao != 'n'){
      printf("Escolha inválida, por favor digite apenas S ou N: ");
      scanf (" %c", &decisao);
    }

    if (decisao == 'N' || decisao == 'n'){
      playAgain = false;
    }

    // Inicialização das variáveis para nova partida
    else {
      acertosUsuario = 0;
      acertosComp = 0; 
      ganhador = false;

      navio.pontoUsuario = 0;
      navio.pontoComp = 0;
      hidro.pontoUsuario = 0;
      hidro.pontoComp = 0;
      porta.pontoUsuario = 0;
      porta.pontoComp = 0;

      printf("Deseja utilizar o mesmo nome? (S/N) ");
      scanf (" %c", &nome);

      while (nome != 'S' && nome != 's' && nome != 'N' && nome != 'n'){
        printf("Escolha inválida, por favor digite apenas S ou N: ");
        scanf (" %c", &nome);
      }

      if (nome == 'N' || nome == 'n'){
        i = i + 1;
        printf("Insira o primeiro nome do(a) Jogador(a): ");
        scanf("%50s", jogador[i].nome);
      }     
    }
  }
}