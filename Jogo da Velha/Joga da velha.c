#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char VJ[3][3]={{'-','-','-'},{'-','-','-'},{'-','-','-'}};
int linha, coluna, cont;

void printGame(){
  printf("\n\n\n                     !!! JOGO DA VELHA !!!");
  printf("\n================================================================================\n\n");
  printf("                            C1  C2  C3 \n\n");
  printf("                       L1 | %c | %c | %c | L1\n                       L2 | %c | %c | %c | L2\n                       L3 | %c | %c | %c | L3\n\n", VJ[0][0], VJ[0][1], VJ[0][2], VJ[1][0], VJ[1][1], VJ[1][2], VJ[2][0], VJ[2][1], VJ[2][2]);
  printf("                            C1  C2  C3 \n\n");
  printf("================================================================================\n\n");

}

void initial(){
  cont = 0;
  VJ[0][0] = '-';
  VJ[0][1] = '-';
  VJ[0][2] = '-';
  VJ[1][0] = '-';
  VJ[1][1] = '-';
  VJ[1][2] = '-';
  VJ[2][0] = '-';
  VJ[2][1] = '-';
  VJ[2][2] = '-';

}

void playerRound(char player[8]){
  printf("\n    %s é a sua vez! \n", player);
  printf("\n      Selecione a linha: ");
  scanf("%d", &linha);
  printf("\n      Selecione a coluna: ");
  scanf("%d", &coluna);

  if (linha > 0 && linha < 4 && coluna > 0 && coluna < 4) {

    if (VJ[linha - 1][coluna - 1] == '-') {

      if (strcmp(player, "Player1") == 0) {
        VJ[linha - 1][coluna - 1] = 'X';
      }
      else {
        VJ[linha - 1][coluna - 1] = 'O';
      }
      
    }
    else {
      printf("\n      Posição inválida! Escolha outra. \n");
      playerRound(player);
    }
  }

  else {
    printf("\n      Posição inválida! Escolha outra entre 1 a 3. \n");
    playerRound(player);
  }

  
}

bool verifyGame(){
  bool winner = false;

  for (int i = 0; i < 3; i++){

    // Verifica se a sequência na linha está igual
    if ((VJ[i][0] == VJ[i][1] && VJ[i][1] == VJ[i][2]) && (VJ[i][0] != '-')){
      winner = true;
    }

    // Verificar se a sequência na coluna está igual
    if ((VJ[0][i] == VJ[1][i] && VJ[1][i] == VJ[2][i]) && (VJ[0][i] != '-')){
      winner = true;
    }
  }

  // Verificar se a sequência na primeira diagonal está igual
  if ((VJ[0][0] == VJ[1][1] && VJ[1][1] == VJ[2][2]) && (VJ[0][0] != '-')){
      winner = true;
    }

  // Verificar se a sequência na segunda diagonal está igual
  if ((VJ[0][2] == VJ[1][1] && VJ[1][1] == VJ[2][0]) && (VJ[0][2] != '-')){
      winner = true;
    }

  return winner;
}

int main()
{
  char resposta[5];
  bool playgame;
  bool playagain = true;

  system("@cls||clear");
  
  printGame();

  printf("                       !!!COMO JOGAR!!!\n");
  printf("Nesse jogo voce tem que escolher a casa em que voce querer colocar o ( X ) ou ( O ).\nPara escolher a casa basta indicar a linha e a coluna, de acordo com as numerações indicadas.\nO jogo é feito por rodadas entre o Player1 e o Player2. O jogo indicara a vez do jogador.\n");

  printf("\n    !!!!PRONTOS PARA COMECAR!!!!\n");
  printf("            Sim ou Nao:");
  scanf("%s", resposta);

  while (playagain){

    if((strcmp(resposta, "Sim") == 0) || (strcmp(resposta, "sim") == 0)){
        playgame = true;
        initial();
        system("@cls||clear");
        printGame();
    }

    while (playgame){

      if (cont % 2 == 0){
        playerRound("Player1");
        system("@cls||clear");
        printGame();

        if (verifyGame()){
          playgame = false;
          printf("\n    Player 1 é o vencedor! Parabéns! \n");
        }

      }
      else {
        playerRound("Player2");
        system("@cls||clear");
        printGame();

        if (verifyGame()){
          playgame = false;
          printf("\n    Player 2 é o vencedor! Parabéns! \n");
        }
      }

      cont ++;

    }

    printf("\n    Você gostaria de jogar novamente? \n");
    printf("            Sim ou Nao:");
    scanf("%s", resposta);

    if((strcmp(resposta, "Nao") == 0) || (strcmp(resposta, "nao") == 0)){
      playagain = false;

    }

  }

  printf("                       !!!FIM DE JOGO!!!\n");

}