#include <stdio.h>
#include "funcs.h"
#include <string.h>
#include <locale.h>
#define gravi 293,47
#define grave 195,23
#define media 130,16
#define leve 88,38
typedef struct
{
  char placa[10], nome[25], tipo[15], pgto[10], modelo[20];
  int dia, mes, ano, fabri, cnh;
  float valor;
}Veiculo;

void registra(Veiculo* ptr);
void boasvindas();
void alternativas();
void linha();
int main()
{
    setlocale(LC_ALL,"");
    FILE *arq;
    int esc;
    Veiculo v1;
    Veiculo *ptrveiculo = &v1; //O ponteiro ptrveiculo vai recever o endere�o da variavel v1, que � do tipo Veiculo.

    boasvindas(); //Puxei a fun��o de boas-vindas.
    alternativas(); //Puxei as fun��es de alternativas.
    scanf("%d", &esc); //Aqui recebemos a escolha do usu�rio.
    getchar(); //Aqui vamos limpar o buffer do teclado, pois o scanf deixa o "\n" como "rastro". Sem ele, nosso c�digo n�o vai rodar corretamente.
    arq = fopen("multas.txt", "a");
    switch(esc){
    case 1:
        registra(ptrveiculo);
        printf("Esses s�o os dados do condutor e do ve�culo:\nModelo do ve�culo: %s\nPlaca do ve�culo: %s\nNome do condutor: %s\nN� da CNH: %d\nConfirmar dados?\n1. Sim\n2. N�o",ptrveiculo->modelo, ptrveiculo->placa, ptrveiculo->nome, ptrveiculo->cnh);
        scanf("%d", &esc);
        if(esc == 1){
            printf("Escolha o peso da infra��o:1.Grav�ssima     2.Grave    3.M�dia     4.Leve    ");
                scanf("%d", &esc);
           switch(esc){
        case 1: ptrveiculo->valor = gravi; case 2: ptrveiculo->valor = grave; case 3: ptrveiculo->valor = media; case 4: ptrveiculo->valor = leve; default: printf("Escolha errada!"); break;
           fprintf(arq, "Modelo do ve�culo: %s\nPlaca do ve�culo: %s\nNome do condutor: %s\nN� da CNH: %d\n",ptrveiculo->modelo,ptrveiculo->placa, ptrveiculo->nome, ptrveiculo->cnh);
            printf("Dados enviados ao arquivo de armazenamento!");
        }
        }

    return 0;
}


void registra(Veiculo* car){
    int esc;
    printf("Escreva o modelo do ve�culo: ");
        fgets(car->modelo, 20, stdin); getchar();
    printf("Escreva a placa do ve�culo: ");
        fgets(car->placa, 10, stdin); getchar();
    printf("Escreva o nome do condutor: ");
        fgets(car->nome, 25, stdin); getchar();
    printf("Escreva o n� da CNH do condutor: ");
        scanf("%d", &car->cnh); getchar();
}

