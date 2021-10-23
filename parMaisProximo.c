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
void imprimirParMaisProximo(Ponto pontos[], Ponto pontosX[], Ponto pontosY[], int tam, double *menorDistancia);
double calcularMenorDistancia(Ponto pontos[], Ponto pontosX[], Ponto pontosY[], int tam);
double calcularMenorDistCombinacao(Ponto pontos[], int itr, double distancia);
double min(double x, double y);
double modulo(double num);
double algoritmoForcaBruta(Ponto pontos[], int tam);

int main(){

    Ponto *pontos, *pontosX, *pontosY, *parMaisProximo;
    int tam;
    double menorDistancia;

    pontos = lerArquivo("teste.txt", &tam);
    pontosX = lerArquivo("teste.txt", &tam);
    pontosY = lerArquivo("teste.txt", &tam);

    imprimirParMaisProximo(pontos, pontosX, pontosY, tam, &menorDistancia);
    //printf("\n%lf", algoritmoForcaBruta(pontosX, tam));

    free(pontosX);
    free(pontosY);
    free(pontos);

    return 0;

}

Ponto* lerArquivo(char nomeArquivo[], int *tam){

    FILE *arquivo;
    Ponto *pontos;
    arquivo = fopen(nomeArquivo, "r");

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

void imprimirParMaisProximo(Ponto pontos[], Ponto pontosX[], Ponto pontosY[], int tam, double *menorDistancia){

    mergeSort(pontosX, 0, tam - 1, 'x');  
    mergeSort(pontosY, 0, tam - 1, 'y');  

    (*menorDistancia) = calcularMenorDistancia(pontos, pontosX, pontosY, tam);

    printf("%lf", (*menorDistancia));

}

double calcularMenorDistancia(Ponto pontos[], Ponto pontosX[], Ponto pontosY[], int tam){

    int meio = tam / 2, itrAux = 0, itrYEsquerda = 0, itrYDireita = 0;
    Ponto *menorDistPar, *aux, *pontosXDireita = pontosX + meio, yEquerda[meio], yDireita[tam - meio];;
    double menorDistancia, distanciaEsquerda, distanciaDireita, xMeio, menorDistCombinacao;
    xMeio = pontosX[meio].x;
    
    if(tam <= 3){

        menorDistPar = forcaBruta3Pontos(pontosX, &menorDistancia);
        return menorDistancia;

    }

    for(int i = 0; i < tam; i++){

        if(pontosY[i].x < xMeio){

            yEquerda[itrYEsquerda] = pontosY[i];
            itrYEsquerda++;

        }

        else{

            yDireita[itrYDireita] = pontosY[i];
            itrYDireita++;

        }

    }

    distanciaEsquerda = calcularMenorDistancia(pontos, pontosX, yEquerda, meio);
    distanciaDireita = calcularMenorDistancia(pontos, pontosXDireita, yDireita,  tam - meio);
    menorDistancia = min(distanciaEsquerda, distanciaDireita);

    aux = (Ponto*) malloc (tam * sizeof (Ponto));

    for(int i = 0; i < tam; i++){

        if(modulo(pontosY[i].x - xMeio) < menorDistancia){

            aux[itrAux] = pontosY[i];
            itrAux++;

        }
            
    }

    menorDistCombinacao = calcularMenorDistCombinacao(aux, itrAux, menorDistancia);

    free(aux);

    return min(menorDistancia, menorDistCombinacao);

}

double calcularMenorDistCombinacao(Ponto pontos[], int itr, double distancia){

    for(int i = 0; i < itr; i++){

        int j = i + 1;

        while(j < itr && (pontos[j].y - pontos[i].y) < distancia){

            double aux = calcularDistanciaPontos(pontos[i], pontos[j]);
            if(aux < distancia)
                distancia = aux;

            j++;

        }

    }

    return distancia;

}

double min(double x, double y){

    return x > y ? y : x;

}

double modulo(double num){

    return num >= 0 ? num : (-1) * num;

}

double algoritmoForcaBruta(Ponto pontos[], int tam){

    double distancia = calcularDistanciaPontos(pontos[0], pontos[1]);

    for(int i = 0; i < tam; i++){

        for(int j = 0; j < tam; j++){

            double aux = calcularDistanciaPontos(pontos[i], pontos[j]);
            if(aux < distancia && aux != 0)
                distancia = aux;

        }

    }

    return distancia;

}