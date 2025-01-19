void linha(){
    printf("\n----------------------------------\n");}
void alternativas(){
printf("Escolha uma das alternativas: \n1. Registrar nova multa.\n2. Consultar multas.\n3. Consultar por CNH.\n4. Enviar ao armazenamento do dia.\n");
}

void boasvindas(){
    printf("-----------------------------\n");
    printf("*****REGISTROS DE MULTAS*****\n");
    printf("-----------------------------\n");}

void aguarde(){
    for(int i= 5; i > 0; i--){
        printf("Seu programa vai reiniciar em %d segundos...", i);
            sleep(1);
                system("cls");
    }
}

