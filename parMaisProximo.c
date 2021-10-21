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
void mergeSort(Ponto pontos[], int esquerda, int direita, char coordenada);
void combinarMerge(Ponto pontos[], int esquerda, int direita, int meio, char coordenada);
void imprimirParMaisProximo(Ponto pontosX[], Ponto pontosY[], int tam, double *menorDistancia);
double calcularMenorDistancia(Ponto pontosX[], Ponto pontosY[], int esquerda, int direita);
double calcularMenorDistCombinacao(Ponto pontos[], int itr, double distancia);
double min(double x, double y);
double modulo(double num);

int main(){

    Ponto *pontosX, *pontosY, *parMaisProximo;
    int tam;
    double menorDistancia;

    pontosX = lerArquivo("teste.txt", &tam);
    pontosY = lerArquivo("teste.txt", &tam);

    imprimirParMaisProximo(pontosX, pontosY, tam, &menorDistancia);

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

void mergeSort(Ponto pontos[], int esquerda, int direita, char coordenada){

    if(esquerda < direita){

        int meio = (esquerda + direita) / 2;

        mergeSort(pontos, esquerda, meio, coordenada);
        mergeSort(pontos, meio + 1, direita, coordenada);
        combinarMerge(pontos, esquerda, direita, meio, coordenada);

    }

    return;

}

void combinarMerge(Ponto pontos[], int esquerda, int direita, int meio, char coordenada){

    int itrEsquerda = esquerda, itrDireita = meio + 1, itrAux = 0, tam = direita - esquerda + 1;
    Ponto* aux;
    aux = (Ponto*) malloc (tam * sizeof (Ponto));

    while(itrEsquerda <= meio && itrDireita <= direita){

        if(coordenada == 'x'){

            if(pontos[itrDireita].x > pontos[itrEsquerda].x){

                aux[itrAux] = pontos[itrEsquerda];
                itrEsquerda++;

            }

            else {

                aux[itrAux] = pontos[itrDireita];
                itrDireita++;

            }

        }

        else{

            if(pontos[itrDireita].y > pontos[itrEsquerda].y){

                aux[itrAux] = pontos[itrEsquerda];
                itrEsquerda++;

            }

            else {

                aux[itrAux] = pontos[itrDireita];
                itrDireita++;

            }

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

void imprimirParMaisProximo(Ponto pontosX[], Ponto pontosY[], int tam, double *menorDistancia){

    mergeSort(pontosX, 0, tam - 1, 'x');  
    mergeSort(pontosY, 0, tam - 1, 'y');  

    (*menorDistancia) = calcularMenorDistancia(pontosX, pontosY, 0, tam - 1);

    printf("%lf", (*menorDistancia));

}

double calcularMenorDistancia(Ponto pontosX[], Ponto pontosY[], int esquerda, int direita){

    Ponto *menorDistPar, *aux;
    double menorDistancia, distanciaEsquerda, distanciaDireita, xMeio, menorDistCombinacao;
    int meio = (esquerda + direita) / 2, tam = (direita - esquerda + 1), itrAux = 0;
    xMeio = pontosX[meio].x;
    
    if(tam <= 3){

        menorDistPar = forcaBruta3Pontos(pontosX, &menorDistancia);
        return menorDistancia;

    }

    distanciaEsquerda = calcularMenorDistancia(pontosX, pontosY, esquerda, meio);
    distanciaDireita = calcularMenorDistancia(pontosX, pontosY, meio + 1, direita);
    menorDistancia = min(distanciaEsquerda, distanciaDireita);
    aux = (Ponto*) malloc (tam * sizeof (Ponto));

    for(int i = 0; i < tam; i++){

        if(modulo(pontosX[i].x - xMeio) < menorDistancia){

            aux[itrAux] = pontosX[i];
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

