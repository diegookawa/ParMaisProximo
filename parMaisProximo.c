#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ponto {
    
    double x;
    double y;

} Ponto;

Ponto* lerArquivo(char nomeArquivo[], int *tam);
void imprimirVetor(Ponto pontos[], int tam);
Ponto* forcaBruta3Pontos(Ponto pontos[]);
double calcularDistanciaPontos(Ponto p1, Ponto p2);

int main(){

    Ponto *pontos, *menor;
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

Ponto* forcaBruta3Pontos(Ponto pontos[]){

    Ponto *menorDistPar;

    menorDistPar = (Ponto*) malloc (2 * sizeof (Ponto));

    double distancia = calcularDistanciaPontos(pontos[0], pontos[1]);

    for(int i = 0; i < 3; i++){

        for(int j = i + 1; j < 3; j++){

            float aux = calcularDistanciaPontos(pontos[i], pontos[j]);

            if(aux < distancia){
                distancia = aux;
                menorDistPar[0] = pontos[i];
                menorDistPar[1] = pontos[j];

            }
                
        }

    }

    return menorDistPar;

}

double calcularDistanciaPontos(Ponto p1, Ponto p2){

    double distancia;

    distancia = sqrt(pow((p1.x - p2.x) , 2) + pow((p1.y - p2.y), 2));

    return distancia;

}