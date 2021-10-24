#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ponto {
    
    double x;
    double y;

} Ponto;

typedef struct distanciaPar {

    Ponto p1;
    Ponto p2;
    double distancia;

} DistanciaPar;

Ponto* lerArquivo(char nomeArquivo[], int *tam);
DistanciaPar forcaBruta3Pontos(Ponto pontos[]);
double calcularDistanciaPontos(Ponto p1, Ponto p2);
void mergeSort(Ponto pontos[], int esquerda, int direita, char coordenada);
void combinarMerge(Ponto pontos[], int esquerda, int direita, int meio, char coordenada);
void imprimirParMaisProximo(Ponto pontosX[], Ponto pontosY[], int tam, DistanciaPar distanciaPar);
DistanciaPar calcularMenorDistancia(Ponto pontosX[], Ponto pontosY[], int tam);
DistanciaPar calcularMenorDistCombinacao(Ponto pontos[], int itr, DistanciaPar menorDistanciaPar);
void preencherSubVetoresY(Ponto pontosY[], Ponto yEsquerda[], Ponto yDireita[], int tam, double xMeio, int *itrYEsquerda, int *itrYDireita);
void preencherVetorFronteira(Ponto pontosY[], Ponto fronteira[], int tam, int *itrFronteira, int menorDistancia, int xMeio);
double min(double x, double y);
double modulo(double num);
double algoritmoForcaBruta(Ponto pontos[], int tam);

int main(){

    Ponto *pontos, *pontosX, *pontosY;
    DistanciaPar distanciaPar;
    int tam;

    pontosX = lerArquivo("auxiliar/input.txt", &tam);
    pontosY = lerArquivo("auxiliar/input.txt", &tam);

    imprimirParMaisProximo(pontosX, pontosY, tam, distanciaPar);
    //printf("\n%lf", algoritmoForcaBruta(pontosX, tam));

    free(pontosX);
    free(pontosY);

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

DistanciaPar forcaBruta3Pontos(Ponto pontos[]){

    DistanciaPar distanciaPar;

    distanciaPar.distancia = calcularDistanciaPontos(pontos[1], pontos[2]);
    distanciaPar.p1 = pontos[1];
    distanciaPar.p2 = pontos[2];

    for(int i = 1; i < 3; i++){

        float aux = calcularDistanciaPontos(pontos[0], pontos[i]);

        if(aux < distanciaPar.distancia){

            distanciaPar.distancia = aux;
            distanciaPar.p1 = pontos[0];
            distanciaPar.p2 = pontos[i];

        }

    }

    return distanciaPar;

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

        else {

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

void imprimirParMaisProximo(Ponto pontosX[], Ponto pontosY[], int tam, DistanciaPar distanciaPar){

    mergeSort(pontosX, 0, tam - 1, 'x');  
    mergeSort(pontosY, 0, tam - 1, 'y');  

    distanciaPar = calcularMenorDistancia(pontosX, pontosY, tam);

    printf("X1: %lf   Y1: %lf\nX2: %lf   Y2 %lf\nDistancia: %lf\n", distanciaPar.p1.x, distanciaPar.p1.y, distanciaPar.p2.x, distanciaPar.p2.y, distanciaPar.distancia);

}

DistanciaPar calcularMenorDistancia(Ponto pontosX[], Ponto pontosY[], int tam){

    DistanciaPar distanciaParEsquerda, distanciaParDireita, distanciaPar, distanciaParCombinacao;
    int meio = tam / 2, itrFronteira = 0, itrYEsquerda = 0, itrYDireita = 0;
    Ponto *fronteira, *pontosXDireita = pontosX + meio, yEsquerda[meio], yDireita[tam - meio];
    double menorDistancia, xMeio = pontosX[meio].x;
    
    if(tam <= 3)
        return forcaBruta3Pontos(pontosX);

    preencherSubVetoresY(pontosY, yEsquerda, yDireita, tam, xMeio, &itrYEsquerda, &itrYDireita);

    distanciaParEsquerda = calcularMenorDistancia(pontosX, yEsquerda, meio);
    distanciaParDireita = calcularMenorDistancia(pontosXDireita, yDireita,  tam - meio);
    menorDistancia = min(distanciaParEsquerda.distancia, distanciaParDireita.distancia);

    distanciaPar = (distanciaParEsquerda.distancia == menorDistancia) ? distanciaParEsquerda : distanciaParDireita;

    fronteira = (Ponto*) malloc (tam * sizeof (Ponto));

    preencherVetorFronteira(pontosY, fronteira, tam, &itrFronteira, menorDistancia, xMeio);

    distanciaParCombinacao = calcularMenorDistCombinacao(fronteira, itrFronteira, distanciaPar);

    free(fronteira);

    return menorDistancia < distanciaParCombinacao.distancia ? distanciaPar : distanciaParCombinacao;

}

void preencherSubVetoresY(Ponto pontosY[], Ponto yEsquerda[], Ponto yDireita[], int tam, double xMeio, int *itrYEsquerda, int *itrYDireita){

    for(int i = 0; i < tam; i++){

        if(pontosY[i].x < xMeio){

            yEsquerda[(*itrYEsquerda)] = pontosY[i];
            (*itrYEsquerda)++;

        }

        else{

            yDireita[(*itrYDireita)] = pontosY[i];
            (*itrYDireita)++;

        }

    }

}

void preencherVetorFronteira(Ponto pontosY[], Ponto fronteira[], int tam, int *itrFronteira, int menorDistancia, int xMeio){

    for(int i = 0; i < tam; i++){

        if(modulo(pontosY[i].x - xMeio) < menorDistancia){

            fronteira[(*itrFronteira)] = pontosY[i];
            (*itrFronteira)++;

        }
            
    }

}

DistanciaPar calcularMenorDistCombinacao(Ponto pontos[], int itr, DistanciaPar menorDistanciaPar){

    for(int i = 0; i < itr; i++){

        int j = i + 1;

        while(j < itr && (pontos[j].y - pontos[i].y) < menorDistanciaPar.distancia){

            double aux = calcularDistanciaPontos(pontos[i], pontos[j]);
            if(aux < menorDistanciaPar.distancia){

                menorDistanciaPar.p1 = pontos[i];
                menorDistanciaPar.p2 = pontos[j];
                menorDistanciaPar.distancia = aux;

            }
                
            j++;

        }

    }

    return menorDistanciaPar;

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