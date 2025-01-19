#include <stdio.h>
#include "func.h"
#include <string.h>
#include <locale.h>

typedef struct{
  char placa[10], nome[25], modelo[20];
  int dia, mes, ano, cnh;
}Veiculo; //defini uma estrutura com nome de "Veiculo", para guardar as informa��es recebidas do usu�rios.

typedef struct elemento{ //defini uma estrutura com nome de "elemento", onde vai ficar as informa��es do ve�culo.
    Veiculo* veic;
        struct elemento* prox;};

typedef struct elemento Elemento; //Criei um elemento do tipo elemento
Elemento* insere_elemento_final(Elemento* lista, Veiculo* veic); //Prot�tipo para a fun��o de inserir o elemento no final da lista
void mostra_lista(Elemento* lista, float valormulta); //Prot�tipo da fun��o para mostrar a lista
Elemento* criar_lista(); //Fun��o para iniciar a lista
void busca_multa(Elemento* lista, int* cnhbuscada); //Prot�tipo da fun��o de busca de multa
float valorMulta(float a); //Prot�tipo da fun��o de multa
int* cnhpbusca; //Declarei um ponteiro do tipo inteiro para a fun��o de buscar multa por cnh
void registra(Veiculo* ptr), boasvindas(),alternativas(), linha(), aguarde(); //Prot�tipo das fun��es feitas
int main(){

    setlocale(LC_ALL,"");
    FILE *arq; //Declarei o ponteiro do tipo FILE, para posteriormente colocar o nome que vai ser criado.
    int esc; float valor; //Declarando a vari�vel "esc" para receber a escolha do usu�rio / Declarando a vari�vel para recever o valor da multa
    Veiculo *ptrveiculo; //Um ponteiro do tipo "Veiculo" declarado, ele ser� usado para ser alterado globalmente
    Elemento* lst = criar_lista(); //Aqui eu declarei o ponteiro "lst" e j� fiz ele receber a fun��o para criar lista
    while(1){ //O programa vai rodar em um looping infinito, o comando para finalizar o looping fica dentro das fun��es.
    boasvindas(); //Puxei a fun��o de boas-vindas.
    alternativas(); //Puxei as fun��es de alternativas.
    scanf("%d", &esc);//Aqui recebemos a escolha do usu�rio.
    getchar(); //Aqui vamos limpar o buffer do teclado, pois o scanf deixa o "\n" como "rastro". Sem ele, nosso c�digo n�o vai rodar corretamente.
    system("cls"); //Usado para limpar a tela
    arq = fopen("multas.txt", "a"); //"a" se houver arquivos existentes, ele ir� escrever abaixo, sen�o, ir� criar um arquivo novo.
    switch(esc){
    case 1:
        ptrveiculo = malloc(sizeof(Veiculo)); /*Aqui eu pe�o para o programa alocar espa�o na mem�ria para o novo registro, eu poderia usar um condicional
        para conferir se foi alocado, mas como � um programa pequeno n�o achei necess�rio*/
        registra(ptrveiculo); //Puxo a fun��o para registrar o ve�culo, colocando o "ptrveiculo" para suprir o par�metro.
        lst = insere_elemento_final(lst, ptrveiculo); //Aqui "lst" vai receber o novo valor recebido pela fun��o de inserir elemento.
        getchar(); //Usado para limpar o buffer do teclado, assim o programa s� vai dar seguimento no funcionamento ap�s o ENTER
        valor = valorMulta(valor); //Puxei a fun��o para colocar o valor da vari�vel
        system("cls"); //Usado para limpar a tela do CMD, somente para est�tica. Deixando claro que isso n�o � recomendado, pois s� funciona em windows.
        printf("------Voc� escolheu registrar uma multa------\n");
        printf("Esses s�o os dados do condutor e do ve�culo:\n\nModelo do ve�culo: %s\nPlaca do ve�culo: %s\nNome do condutor: %s\nN� da CNH: %d\n\nValor da multa: %.2f\n\nConfirmar dados?\n1. Sim\n2. N�o\n",ptrveiculo->modelo, ptrveiculo->placa, ptrveiculo->nome, ptrveiculo->cnh, valor); //Aqui o usu�rio vai confirmar os dados;
        scanf("%d", &esc); //Aqui eu reutilizo a vari�vel "esc", tendo em vista que o programa vai reinciar mesmo, n�o tem necessidade fazer outra s� para isso
        if(esc == 1){
         printf("Confirma��o aprovada!");
            system("cls");
            continue;
        }
        else if(esc == 2){
            printf("Confirma��o negada!");
                free(ptrveiculo); //Aqui eu vou limpar as informa��es que foram colocadas no ponteiro, assim n�o ir� para lista.
                    sleep(5); //Aqui ele vai dar uma pausa de 5 segundos.
                        system("cls");
                            continue;// Usado para voltar para o in�cio do looping.
                            }

    case 2:
        if(lst == NULL){
        printf("Nenhum registro do dia!\nPressione ENTER para reiniciar o programa.\n");
            getchar();
                aguarde(); //Puxei a fun��o de contagem de segundos para reiniciar o programa, tamb�m para est�tica.
                    system("cls");
                        continue;
        }else{
        mostra_lista(lst, valor); //Puxei a fun��o para mostrar a lista de multas registradas at� o momento. Suprindo os dois par�metros pedidos.
            linha(); //Puxei a fun��o que fiz de linha, para n�o poluir muito o c�digo.
                printf("Essas s�o as multas do dia!\nAperte na tela ENTER para reinciar o sistema.");}
                    getchar(); // Limpar o buffer
                        aguarde(); // De novo a fun��o aguardar
                            system("cls"); //Limpar tela
                                continue;
    case 3:
    printf("Digite a CNH para busca: ");
        scanf("%d", &cnhpbusca); //Aqui eu coloco o dado inserido pelo usu�rio na vari�vel "cnhbusca".
            busca_multa(lst, cnhpbusca); //Aqui eu puxo a fun��o de busca. Suprindo os dois par�metros pedidos.
                getchar();
                    aguarde(); //De novo a fun��o de aguardar
                        system("cls"); //Limpar tela
                            continue;

    case 4:
        if(lst == NULL){ //Se n�o tiver nenhum registro na lista...
        printf("Nenhum registro do dia!\nPressione ENTER para reiniciar o programa.\n");
            getchar(); //Limpa buffer
            aguarde(); //Fun��o para aguardar
                system("cls");
                    continue;}
            printf("Voc� escolheu enviar as multas para o arquivo de registro.\n");
                       fprintf(arq,"-----------------------------\nModelo do ve�culo: %s\nPlaca do ve�culo: %s\nNome do condutor: %s\nN� da CNH: %d\nValor da multa: %.2f\n9-----------------------------\n",ptrveiculo->modelo,ptrveiculo->placa, ptrveiculo->nome, ptrveiculo->cnh, valor);
                        //^ Aqui eu usei o comando "fprint" para mandar os dados para o ve�culo
                        printf("\nOs registros foram enviados ao armazenamento!\nO programa ir� encerrar em 5 segundos...");
                            sleep(5);
                                return 0;
    default:
        printf("Escolha inv�lida, por favor escolha novamente.\n");
            aguarde();
                system("cls");
                    continue;
        }
    }
    fclose(arq); //Sempre fechar o documento depois da abertura.
    return 0;
}

void busca_multa(Elemento* lista, int* cnhbuscada){
    Elemento* ptlista = lista; int i=0; //Criei um ponteiro para a lista. / E declarei outra local para contar as multas.

    while(ptlista != NULL){ //Enquanto o ponteiro n�o apontar para o NULL da lista.
        if(ptlista->veic->cnh == cnhbuscada){ //Condicional para ver se a cnhbuscada � igual a que est� na nos dados
        printf("Modelo do carro: %s", ptlista->veic->modelo);
        printf("Placa do ve�culo: %s", ptlista->veic->placa);
        printf("Nome do condutor: %s", ptlista->veic->nome);
        printf("CNH do condutor: %d", ptlista->veic->cnh);
        printf("\n------------------\n"); i++; //Complementa o i para contar a quantidade de multa
        }
        ptlista = ptlista->prox; //Ponteiro vai para a pr�xima posi��o da lista.
        }
        getchar();

        if(i == 0){ //Se o i n�o foi complementado na condicional anterior, vai cair nessa condicional
            printf("N�o h� multas registradas nessa placa!\nPressione ENTER para reiniciar o programa.");
                getchar();
                }
            }


void mostra_lista(Elemento* lst, float valormulta){
    Elemento* ptlista = lst; //Ponteiro para percorrer a lista

    while(ptlista != NULL){ //Enquanto o ponteiro n�o apontar para o final da lista
        printf("Modelo do carro: %s", ptlista->veic->modelo);
        printf("Placa do ve�culo: %s", ptlista->veic->placa);
        printf("Nome do condutor: %s", ptlista->veic->nome);
        printf("CNH do condutor: %d", ptlista->veic->cnh);
        printf("\nValor da multa: %.2f", valormulta);
        linha();
            ptlista = ptlista->prox; //Pula para a pr�xima posi��o da lista

    }
}

Elemento* criar_lista(){ //Fun��o para iniciar a lista.
    return NULL;}

Elemento* insere_elemento_final(Elemento* lista, Veiculo* veic){
    Elemento* novo = malloc(sizeof(Elemento)); //Esse elemento vai ser usado para apontar para os valores da lista.
    novo->veic = veic; //O ponteiro novo vai receber os dados do ve�culos
        novo->prox = NULL;

    if(lista == NULL){ //Se a lista estiver vazia
            return novo; //Ele ir� retornar o novo elemento.
    }
    Elemento* atual = lista; //Usado para percorrer a lista.
    while(atual->prox != NULL){ //Usado para chegar no final da lista, quando o pr�ximo foi nulo, para o while
        atual = atual->prox;
    }
    atual->prox = novo; //Aqui o valor do novo registro � colocado no final da lista.
        return lista; //Retorna a lista.


}


void registra(Veiculo* car){
    int esc;
    printf("------Voc� escolheu registrar uma multa------\n");
    printf("Escreva o modelo do ve�culo: ");
        fgets(car->modelo, 20, stdin); //Recebe os dados e coloca no car->modelo
    printf("Escreva a placa do ve�culo: ");
        fgets(car->placa, 10, stdin); //Recebe os dados e coloca no car->placa
    printf("Escreva o nome do condutor: ");
        fgets(car->nome, 25, stdin); //Recebe os dados e coloca no car->nome
    printf("Escreva o n� da CNH do condutor: ");
        scanf("%d", &car->cnh); //Recebe os dados e coloca no car->cnh
}
float valorMulta(float a){
    int b; //Declarei a vari�vel localmente somente para receber a escolha.
    printf("Escolha o peso da infra��o: \n");
    printf("1.Grav�ssima    2.Grave     3.M�dia     4.Leve\n");
        scanf("%d", &b);
        switch(b){
    case 1: return 293.47;
    case 2: return 195.23;
    case 3: return 130.16;
    case 4: return 88.38;
    default: //Caso for colocado o valor errado.
        printf("Escolha errada! Tente novamente.");}}
