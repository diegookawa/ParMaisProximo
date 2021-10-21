#include <stdio.h>
#include <stdlib.h>

typedef struct ponto {
    
    double x;
    double y;

} Ponto;

Ponto* lerArquivo(char nomeArquivo[], int *tam);
void imprimirVetor(Ponto pontos[], int tam);

int main(){

    Ponto *pontos;
    int tam;

    pontos = lerArquivo("teste.txt", &tam);
    imprimirVetor(pontos, tam);
    
    return 0;

}

Ponto* lerArquivo(char nomeArquivo[], int *tam){

    FILE *arquivo;
    Ponto *pontos;
    arquivo = fopen(nomeArquivo, "r");
    int tamanhoArquivo;

    if(arquivo == NULL){

        printf("ERRO AO ABRIR O ARQUIVO.");
        getchar();
        exit(1);

    }

    fscanf(arquivo, "%d", tam);

    pontos = (Ponto*) malloc ((*tam) * sizeof (Ponto));

    for(int i = 0; i < (*tam); i++)
        fscanf(arquivo, "%lf %lf", &pontos[i].x, &pontos[i].y);
        
    fclose(arquivo);

    return pontos;

}

void imprimirVetor(Ponto pontos[], int tam){

    for(int i = 0; i < tam; i++)
        printf("%lf %lf\n", pontos[i].x, pontos[i].y);

}