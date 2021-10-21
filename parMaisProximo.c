#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ponto {
    
    double x;
    double y;

} Ponto;

Ponto* lerArquivo(char nomeArquivo[], int *tam);
void imprimirVetor(Ponto pontos[], int tam);
Ponto* forcaBruta3Pontos(Ponto pontos[], double *distancia);
double calcularDistanciaPontos(Ponto p1, Ponto p2);
void mergeSort(Ponto pontos[], int esquerda, int direita);
void combinarMerge(Ponto pontos[], int esquerda, int direita, int meio);
void imprimirParMaisProximo(Ponto pontos[], int tam, double *menorDistancia);
double calcularMenorDistancia(Ponto pontos[], int esquerda, int direita);
double calcularMenorDistCombinacao(Ponto pontos[], int itr, double distancia);
double min(double x, double y);
double modulo(double num);

int main(){

    Ponto *pontos, *parMaisProximo;
    int tam;
    double menorDistancia;

    pontos = lerArquivo("teste.txt", &tam);
    imprimirVetor(pontos, tam);

    imprimirParMaisProximo(pontos, tam, &menorDistancia);

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

Ponto* forcaBruta3Pontos(Ponto pontos[], double *distancia){

    Ponto *menorDistPar;

    menorDistPar = (Ponto*) malloc (2 * sizeof (Ponto));

    (*distancia) = calcularDistanciaPontos(pontos[0], pontos[1]);

    for(int i = 0; i < 3; i++){

        for(int j = i + 1; j < 3; j++){

            float aux = calcularDistanciaPontos(pontos[i], pontos[j]);

            if(aux < (*distancia)){

                (*distancia) = aux;
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

void mergeSort(Ponto pontos[], int esquerda, int direita){

    if(esquerda < direita){

        int meio = (esquerda + direita) / 2;

        mergeSort(pontos, esquerda, meio);
        mergeSort(pontos, meio + 1, direita);
        combinarMerge(pontos, esquerda, direita, meio);

    }

    return;

}

void combinarMerge(Ponto pontos[], int esquerda, int direita, int meio){

    int itrEsquerda = esquerda, itrDireita = meio + 1, itrAux = 0, tam = direita - esquerda + 1;
    Ponto* aux;
    aux = (Ponto*) malloc (tam * sizeof (Ponto));

    while(itrEsquerda <= meio && itrDireita <= direita){

        if(pontos[itrDireita].x > pontos[itrEsquerda].x){

            aux[itrAux] = pontos[itrEsquerda];
            itrEsquerda++;

        }

        else {

            aux[itrAux] = pontos[itrDireita];
            itrDireita++;

        }

        itrAux++;

    }

    while(itrEsquerda <= meio){

        aux[itrAux] = pontos[itrEsquerda];
        itrEsquerda++;
        itrAux++;

    }

    while(itrDireita <= direita){

        aux[itrAux] = pontos[itrDireita];
        itrDireita++;
        itrAux++;

    }

    for(itrAux = esquerda; itrAux <= direita; itrAux++)
        pontos[itrAux] = aux[itrAux - esquerda];

    free(aux);

}

void imprimirParMaisProximo(Ponto pontos[], int tam, double *menorDistancia){

    mergeSort(pontos, 0, tam - 1);

    (*menorDistancia) = calcularMenorDistancia(pontos, 0, tam - 1);

    printf("%lf", (*menorDistancia));

}

double calcularMenorDistancia(Ponto pontos[], int esquerda, int direita){

    Ponto *menorDistPar, *aux;
    double menorDistancia, distanciaEsquerda, distanciaDireita, xMeio, menorDistCombinacao;
    int meio = (esquerda + direita) / 2, tam = (direita - esquerda + 1), itrAux = 0;
    xMeio = pontos[meio].x;
    
    if(tam <= 3){

        menorDistPar = forcaBruta3Pontos(pontos, &menorDistancia);
        return menorDistancia;

    }

    distanciaEsquerda = calcularMenorDistancia(pontos, esquerda, meio);
    distanciaDireita = calcularMenorDistancia(pontos, meio + 1, direita);
    menorDistancia = min(distanciaEsquerda, distanciaDireita);
    aux = (Ponto*) malloc (tam * sizeof (Ponto));

    for(int i = 0; i < tam; i++){

        if(modulo(pontos[i].x - xMeio) < menorDistancia){

            aux[itrAux] = pontos[i];
            itrAux++;

        }
            
    }

    menorDistCombinacao = calcularMenorDistCombinacao(aux, itrAux, menorDistancia);

    return min(menorDistancia, menorDistCombinacao);

}

double calcularMenorDistCombinacao(Ponto pontos[], int itr, double distancia){

    return 1;

}

double min(double x, double y){

    return x > y ? y : x;

}

double modulo(double num){

    return num >= 0 ? num : (-1) * num;

}

