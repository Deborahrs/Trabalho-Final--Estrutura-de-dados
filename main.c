#include <stdio.h>
#include "funcs.h"
#include <string.h>
#include <locale.h>
typedef struct
{
  char placa[10], nome[25], tipo[15], pgto[10], modelo[20];
  int dia, mes, ano, fabri, cnh;
  float valor;
}Veiculo;
float valorMulta(float a); void registra(Veiculo* ptr);
void boasvindas(); void alternativas();
void linha();
int main()
{
    setlocale(LC_ALL,"");
    FILE *arq;
    int esc; float valor;
    Veiculo v1;
    Veiculo *ptrveiculo = &v1; //O ponteiro ptrveiculo vai recever o endereço da variavel v1, que é do tipo Veiculo.

    boasvindas(); //Puxei a função de boas-vindas.
    alternativas(); //Puxei as funções de alternativas.
    scanf("%d", &esc);//Aqui recebemos a escolha do usuário.
    getchar(); //Aqui vamos limpar o buffer do teclado, pois o scanf deixa o "\n" como "rastro". Sem ele, nosso código não vai rodar corretamente.
    system("cls"); //Usado para limpar a tela
    arq = fopen("multas.txt", "a"); //"a" se houver arquivos existentes, ele irá escrever abaixo, senão, irá criar um arquivo novo.
    switch(esc){
    case 1:
        arq = fopen("multas.txt", "a"); //"a" se houver arquivos existentes, ele irá escrever abaixo, senão, irá criar um arquivo novo.
        registra(ptrveiculo);
        valor = valorMulta(valor);
        system("cls");
        printf("Esses são os dados do condutor e do veículo:\n\nModelo do veículo: %s\nPlaca do veículo: %s\nNome do condutor: %s\nN° da CNH: %d\nValor da multa: %.2f\nConfirmar dados?\n1. Sim\n2. Não\n",ptrveiculo->modelo, ptrveiculo->placa, ptrveiculo->nome, ptrveiculo->cnh, valor);
        scanf("%d", &esc);
        if(esc == 1){
           fprintf(arq, "Modelo do veículo: %s\nPlaca do veículo: %s\nNome do condutor: %s\nN° da CNH: %d\n\nValor da multa: %.2f\n-----------------------------\n",ptrveiculo->modelo,ptrveiculo->placa, ptrveiculo->nome, ptrveiculo->cnh, valor);
            printf("Dados enviados ao arquivo de armazenamento!");
        } else if(esc == 2){
            printf("Confirmação negada!");}
            fclose(arq);
            break;

    case 2:{

        char procura[250];
        int cnhProcurada;
        int tem = 0; // Flag para verificar se encontrou alguma multa
        arq = fopen("multas.txt", "r"); // O "r" irá somente ler o conteúdo do arquivo de texto.

        printf("Digite o número da CNH que deseja consultar: ");
        scanf("%d", &cnhProcurada);
        getchar(); // Limpa o buffer do teclado

        char cnhBusca[50];
        sprintf(cnhBusca, "N° da CNH: %d", cnhProcurada); //O sprintf seria como um strcpy, mas podendo colocar mais algum argumento de sua opção.

        printf("\n----- Multas Encontradas -----\n");

        while (fgets(procura, sizeof(procura), arq) != NULL) { // O fgets vai colocar todos os elementos na variável procura até não ter mais nada "NULL"
            if (strstr(procura, cnhBusca) != NULL) {
                tem = 1; //Se tiver encontrado a CNH vai mudar o valor para 1
                printf("%s", procura);

                while (fgets(procura, sizeof(linha), arq) != NULL && strstr(linha, "-----------------------------") == NULL) {
                    printf("%s", linha);
                }
                printf("-----------------------------\n");
            }
        }

        if (!tem) {
            printf("Nenhuma multa encontrada.\n");
        }
        printf("----- Fim da Consulta -----\n");
        fclose(arq);
        break; }

    default:
        printf("Opção inválida!\n"); }
    return 0; }


void registra(Veiculo* car){
    int esc;
    printf("------Você escolheu registrar uma multa------\n");
    printf("Escreva o modelo do veículo: ");
        fgets(car->modelo, 20, stdin);
        strtok(car->modelo, "\n");
    printf("Escreva a placa do veículo: ");
        fgets(car->placa, 10, stdin);
        strtok(car->placa, "\n");
    printf("Escreva o nome do condutor: ");
        fgets(car->nome, 25, stdin);
        strtok(car->nome, "\n");
    printf("Escreva o n° da CNH do condutor: ");
        scanf("%d", &car->cnh);
}
float valorMulta(float a){
    int b;
    printf("Escolha o peso da infração: \n");
    printf("1.Gravíssima    2.Grave     3.Média     4.Leve\n");
        scanf("%d", &b);
        switch(b){
    case 1: return 293.47;
    case 2: return 195.23;
    case 3: return 130.16;
    case 4: return 88.38;
    default:
        printf("Escolha errada! Tente novamente.");
        return 0;}
    }
