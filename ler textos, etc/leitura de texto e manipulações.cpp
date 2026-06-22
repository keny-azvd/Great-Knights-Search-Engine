#include <iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;




int main(){
    char vetor[4];


    FILE *arquivo;
    arquivo = fopen("arch.txt","wt"); // ponteiro que aponta para o espaço de memoria onde está o nosso arch.txt
                                      // wt gravação
                                      // rt leitura - a append
    if(arquivo == NULL){
        printf("nao foi possivel abrir o arquivo");
        exit(0); // corta execução do programa
    }
    fprintf(arquivo,"olá");   //gravar strings no arquivo
                              //para ler , temos q abir modo leitura
    fclose(arquivo);
    arquivo = fopen("arch.txt","rt");

    if(arquivo == NULL){
        printf("nao foi possivel abrir o arquivo");
        exit(0); // corta execução do programa
    }
    fscanf(arquivo,"%s",&vetor);
    printf(vetor);


    fclose(arquivo);

   return 0;
}
