#include <stdio.h>
#include "func.h"
#include <string.h>
#include <locale.h>

typedef struct{
  char placa[10], nome[25], modelo[20];
  int dia, mes, ano, cnh;
}Veiculo; //defini uma estrutura com nome de "Veiculo", para guardar as informações recebidas do usuários.

typedef struct elemento{ //defini uma estrutura com nome de "elemento", onde vai ficar as informações do veículo.
    Veiculo* veic;
        struct elemento* prox;};

typedef struct elemento Elemento; //Criei um elemento do tipo elemento
Elemento* insere_elemento_final(Elemento* lista, Veiculo* veic); //Protótipo para a função de inserir o elemento no final da lista
void mostra_lista(Elemento* lista, float valormulta); //Protótipo da função para mostrar a lista
Elemento* criar_lista(); //Função para iniciar a lista
void busca_multa(Elemento* lista, int* cnhbuscada); //Protótipo da função de busca de multa
float valorMulta(float a); //Protótipo da função de multa
int* cnhpbusca; //Declarei um ponteiro do tipo inteiro para a função de buscar multa por cnh
void registra(Veiculo* ptr), boasvindas(),alternativas(), linha(), aguarde(),enviar_arquivo(Elemento* lista, FILE* arquivo, float valormulta); //Protótipo das funções feitas
int main(){

    setlocale(LC_ALL,"");
    FILE *arq; //Declarei o ponteiro do tipo FILE, para posteriormente colocar o nome que vai ser criado.
    int esc; float valor; //Declarando a variável "esc" para receber a escolha do usuário / Declarando a variável para recever o valor da multa
    Veiculo *ptrveiculo; //Um ponteiro do tipo "Veiculo" declarado, ele será usado para ser alterado globalmente
    Elemento* lst = criar_lista(); //Aqui eu declarei o ponteiro "lst" e já fiz ele receber a função para criar lista
    while(1){ //O programa vai rodar em um looping infinito, o comando para finalizar o looping fica dentro das funções.
    boasvindas(); //Puxei a função de boas-vindas.
    alternativas(); //Puxei as funções de alternativas.
    scanf("%d", &esc);//Aqui recebemos a escolha do usuário.
    getchar(); //Aqui vamos limpar o buffer do teclado, pois o scanf deixa o "\n" como "rastro". Sem ele, nosso código não vai rodar corretamente.
    system("cls"); //Usado para limpar a tela
    arq = fopen("multas.txt", "a"); //"a" se houver arquivos existentes, ele irá escrever abaixo, senão, irá criar um arquivo novo.
    switch(esc){
    case 1:
        ptrveiculo = malloc(sizeof(Veiculo)); /*Aqui eu peço para o programa alocar espaço na memória para o novo registro, eu poderia usar um condicional
        para conferir se foi alocado, mas como é um programa pequeno não achei necessário*/
        registra(ptrveiculo); //Puxo a função para registrar o veículo, colocando o "ptrveiculo" para suprir o parâmetro.
        lst = insere_elemento_final(lst, ptrveiculo); //Aqui "lst" vai receber o novo valor recebido pela função de inserir elemento.
        getchar(); //Usado para limpar o buffer do teclado, assim o programa só vai dar seguimento no funcionamento após o ENTER
        valor = valorMulta(valor); //Puxei a função para colocar o valor da variável
        system("cls"); //Usado para limpar a tela do CMD, somente para estética. Deixando claro que isso não é recomendado, pois só funciona em windows.
        printf("------Você escolheu registrar uma multa------\n");
        printf("Esses são os dados do condutor e do veículo:\n\nModelo do veículo: %s\nPlaca do veículo: %s\nNome do condutor: %s\nN° da CNH: %d\n\nValor da multa: %.2f\n\nConfirmar dados?\n1. Sim\n2. Não\n",ptrveiculo->modelo, ptrveiculo->placa, ptrveiculo->nome, ptrveiculo->cnh, valor); //Aqui o usuário vai confirmar os dados;
        scanf("%d", &esc); //Aqui eu reutilizo a variável "esc", tendo em vista que o programa vai reinciar mesmo, não tem necessidade fazer outra só para isso
        if(esc == 1){
         printf("Confirmação aprovada!");
            system("cls");
            continue;
        }
        else if(esc == 2){
            printf("Confirmação negada!");
                free(ptrveiculo); //Aqui eu vou limpar as informações que foram colocadas no ponteiro, assim não irá para lista.
                    sleep(5); //Aqui ele vai dar uma pausa de 5 segundos.
                        system("cls");
                            continue;// Usado para voltar para o início do looping.
                            }

    case 2:
        if(lst == NULL){
        printf("Nenhum registro do dia!\nPressione ENTER para reiniciar o programa.\n");
            getchar();
                aguarde(); //Puxei a função de contagem de segundos para reiniciar o programa, também para estética.
                    system("cls");
                        continue;
        }else{
        mostra_lista(lst, valor); //Puxei a função para mostrar a lista de multas registradas até o momento. Suprindo os dois parâmetros pedidos.
            linha(); //Puxei a função que fiz de linha, para não poluir muito o código.
                printf("Essas são as multas do dia!\nAperte na tela ENTER para reinciar o sistema.");}
                    getchar(); // Limpar o buffer
                        aguarde(); // De novo a função aguardar
                            system("cls"); //Limpar tela
                                continue;
    case 3:
    printf("Digite a CNH para busca: ");
        scanf("%d", &cnhpbusca); //Aqui eu coloco o dado inserido pelo usuário na variável "cnhbusca".
            busca_multa(lst, cnhpbusca); //Aqui eu puxo a função de busca. Suprindo os dois parâmetros pedidos.
                getchar();
                    aguarde(); //De novo a função de aguardar
                        system("cls"); //Limpar tela
                            continue;

    case 4:
        if(lst == NULL){ //Se não tiver nenhum registro na lista...
        printf("Nenhum registro do dia!\nPressione ENTER para reiniciar o programa.\n");
            getchar(); //Limpa buffer
            aguarde(); //Função para aguardar
                system("cls");
                    continue;}
            printf("Você escolheu enviar as multas para o arquivo de registro.\n");
                enviar_arquivo(lst, arq, valor);
                        printf("\nOs registros foram enviados ao armazenamento!\nO programa irá encerrar em 5 segundos...");
                            sleep(5);
                                return 0;
    default:
        printf("Escolha inválida, por favor escolha novamente.\n");
            aguarde();
                system("cls");
                    continue;
        }
    }
    fclose(arq); //Sempre fechar o documento depois da abertura.
    return 0;
}

void enviar_arquivo(Elemento* lista, FILE* arquivo, float valormulta){
    Elemento* ptlista = lista;

    while(ptlista != NULL){
    fprintf(arquivo,"-----------------------------\nModelo do veículo: %s\nPlaca do veículo: %s\nNome do condutor: %s\nN° da CNH: %d\nValor da multa: %.2f\n9-----------------------------\n",ptlista->veic->modelo,ptlista->veic->placa,ptlista->veic->nome,ptlista->veic->cnh, valormulta);
        //^ Aqui eu usei o comando "fprint" para mandar os dados para o veículo
        ptlista = ptlista->prox;
    }
}

void busca_multa(Elemento* lista, int* cnhbuscada){
    Elemento* ptlista = lista; int i=0; //Criei um ponteiro para a lista. / E declarei outra local para contar as multas.

    while(ptlista != NULL){ //Enquanto o ponteiro não apontar para o NULL da lista.
        if(ptlista->veic->cnh == cnhbuscada){ //Condicional para ver se a cnhbuscada é igual a que está na nos dados
        printf("Modelo do carro: %s", ptlista->veic->modelo);
        printf("Placa do veículo: %s", ptlista->veic->placa);
        printf("Nome do condutor: %s", ptlista->veic->nome);
        printf("CNH do condutor: %d", ptlista->veic->cnh);
        printf("\n------------------\n"); i++; //Complementa o i para contar a quantidade de multa
        }
        ptlista = ptlista->prox; //Ponteiro vai para a próxima posição da lista.
        }
        getchar();

        if(i == 0){ //Se o i não foi complementado na condicional anterior, vai cair nessa condicional
            printf("Não há multas registradas nessa placa!\nPressione ENTER para reiniciar o programa.");
                getchar();
                }
            }


void mostra_lista(Elemento* lst, float valormulta){
    Elemento* ptlista = lst; //Ponteiro para percorrer a lista

    while(ptlista != NULL){ //Enquanto o ponteiro não apontar para o final da lista
        printf("Modelo do carro: %s", ptlista->veic->modelo);
        printf("Placa do veículo: %s", ptlista->veic->placa);
        printf("Nome do condutor: %s", ptlista->veic->nome);
        printf("CNH do condutor: %d", ptlista->veic->cnh);
        printf("\nValor da multa: %.2f", valormulta);
        linha();
            ptlista = ptlista->prox; //Pula para a próxima posição da lista

    }
}

Elemento* criar_lista(){ //Função para iniciar a lista.
    return NULL;}

Elemento* insere_elemento_final(Elemento* lista, Veiculo* veic){
    Elemento* novo = malloc(sizeof(Elemento)); //Esse elemento vai ser usado para apontar para os valores da lista.
    novo->veic = veic; //O ponteiro novo vai receber os dados do veículos
        novo->prox = NULL;

    if(lista == NULL){ //Se a lista estiver vazia
            return novo; //Ele irá retornar o novo elemento.
    }
    Elemento* atual = lista; //Usado para percorrer a lista.
    while(atual->prox != NULL){ //Usado para chegar no final da lista, quando o próximo foi nulo, para o while
        atual = atual->prox;
    }
    atual->prox = novo; //Aqui o valor do novo registro é colocado no final da lista.
        return lista; //Retorna a lista.


}


void registra(Veiculo* car){
    int esc;
    printf("------Você escolheu registrar uma multa------\n");
    printf("Escreva o modelo do veículo: ");
        fgets(car->modelo, 20, stdin); //Recebe os dados e coloca no car->modelo
    printf("Escreva a placa do veículo: ");
        fgets(car->placa, 10, stdin); //Recebe os dados e coloca no car->placa
    printf("Escreva o nome do condutor: ");
        fgets(car->nome, 25, stdin); //Recebe os dados e coloca no car->nome
    printf("Escreva o n° da CNH do condutor: ");
        scanf("%d", &car->cnh); //Recebe os dados e coloca no car->cnh
}
float valorMulta(float a){
    int b; //Declarei a variável localmente somente para receber a escolha.
    printf("Escolha o peso da infração: \n");
    printf("1.Gravíssima    2.Grave     3.Média     4.Leve\n");
        scanf("%d", &b);
        switch(b){
    case 1: return 293.47;
    case 2: return 195.23;
    case 3: return 130.16;
    case 4: return 88.38;
    default: //Caso for colocado o valor errado.
        printf("Escolha errada! Tente novamente.");}}
