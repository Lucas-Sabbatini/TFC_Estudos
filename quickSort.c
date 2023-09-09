#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10000
#define nMetodos 4
#define nVetores 4

void troca(int *a,int *b);
int particao(int *vet,int esq,int dir);
void quickSortBasico(int *vet,int esq,int dir);
int pivoAleatorio(int esq,int dir);
void quickSortAleatorio(int *vet,int esq, int dir);
void quickSortMediana3(int *vet,int esq,int dir);
void quickSortTresPartes(int *vet,int esq,int dir);
void imprimeResultado(double tempoDeExecucao[nMetodos][nVetores]);

int main(){
    srand(time(NULL));
    int vet[TAM],i,j,k;
    clock_t comeco,final;
    double tempoDeExecucao[nMetodos][nVetores];

    for(j=0;j<nMetodos;j++){
        for(k=0;k<nVetores;k++){
            switch (k){
                case 0:
                    //Aleatório
                    for(i=0;i<TAM;i++){
                        vet[i] = rand();
                    }
                break;
                case 1:
                    //Ordenado
                    for(i=0;i<TAM;i++){
                        vet[i] = i;
                    }
                break;
                case 2:
                    //Invertido
                    for(i=0;i<TAM;i++){
                        vet[i] = TAM - i;
                    }
                break;
                case 3:
                    //Repetidos
                    for(i=0;i<TAM;i++){
                        vet[i] = rand() %10;
                    }
                break;
            }
            comeco = clock();
            switch (j){
                case 0:
                    quickSortBasico(vet,0,TAM-1);
                break;
                case 1:
                    quickSortAleatorio(vet,0,TAM-1);
                break;
                case 2:
                    quickSortMediana3(vet,0,TAM-1);
                break;
                case 3: 
                    quickSortTresPartes(vet,0,TAM-1);
                break;
            }
            final = clock();

            tempoDeExecucao[j][k] = (double) (final - comeco)/CLOCKS_PER_SEC;
        }
    }

    imprimeResultado(tempoDeExecucao);
    return 0;
}

void troca(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particao(int *vet,int esq,int dir){
    int i,pivo;
    pivo = esq;

    for(i=esq+1;i<=dir;i++){
        if(vet[i] < vet[esq]){
            pivo ++;
            troca(&vet[i],&vet[pivo]);
        }
    }
    troca(&vet[esq],&vet[pivo]);
    return pivo;
}

void quickSortBasico(int *vet,int esq,int dir){
    int part;

    if(esq>=dir) return;
    part = particao(vet,esq,dir);

    quickSortBasico(vet,esq,part-1);
    quickSortBasico(vet,part+1,dir);
}

int pivoAleatorio(int esq,int dir){
    double r;
    r = (double) rand()/RAND_MAX;
    return (int)(esq + (dir-esq)*r);
}

void quickSortAleatorio(int *vet,int esq, int dir){
    int part;

    if(esq>=dir) return;
    troca(&vet[pivoAleatorio(esq,dir)],&vet[esq]);

    part = particao(vet,esq,dir);
    quickSortAleatorio(vet,esq,part-1);
    quickSortAleatorio(vet,part+1,dir);
}

void quickSortMediana3(int *vet,int esq,int dir){
    int part;

    if(esq>=dir) return;
    troca(&vet[(esq+dir)/2],&vet[esq+1]);
    if(vet[esq] > vet[esq+1]){
        troca(&vet[esq] , &vet[esq+1]);
    }
    if(vet[esq] > vet[dir]){
        troca(&vet[esq] , &vet[dir]);
    }
    if(vet[esq+1] > vet[dir]){
        troca(&vet[esq+1],&vet[dir]);
    }

    part = particao(vet,esq+1,dir-1);
    quickSortMediana3(vet,esq,part-1);
    quickSortMediana3(vet,part+1,dir);
}

void quickSortTresPartes(int *vet,int esq,int dir){
    int k, i = esq-1,j = dir,p = esq-1,q = dir;
    int pivo = vet[dir];

    if(esq>=dir) return;
    for(;;){
        while(vet[++i]< pivo);
        while(pivo < vet[--j])
            if(j==esq) break;
        if(i>=j) break;
        troca(&vet[i],&vet[j]);
        if(vet[i]==pivo){ p++;troca(&vet[p],&vet[i]);}
        if(vet[j]==pivo){q--;troca(&vet[j],&vet[q]);}
    }
    troca(&vet[i],&vet[dir]);
    j = i -1;
    i = i + 1;
    for(k=esq; k<=p;k++,j--){
        troca(&vet[k],&vet[j]);
    }
    for(k = dir-1;k >=q;k--,i++){
        troca(&vet[i],&vet[k]);
    }

    quickSortTresPartes(vet,esq,j);
    quickSortTresPartes(vet,i,dir);
}
void imprimeResultado(double tempoDeExecucao[nMetodos][nVetores]){
    int i,j;
                printf("\n\n N elementos: %d |Aleatorio|Ordenado|Invertido|Repetidos\n",TAM);
    for(i=0;i<nVetores;i++){
        switch (i){
            case 0:
                printf(" Quick Sort .......:   ");
            break;
            case 1:
                printf(" Pivo Aleatorio ...:   ");
            break;
            case 2:
                printf(" Mediana de 3 .....:   ");
            break;
            case 3:
                printf(" Particao em 3 vias:   ");
            break;
        }
        for(j=0;j<nMetodos;j++){
            printf("%.3f    ",tempoDeExecucao[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

