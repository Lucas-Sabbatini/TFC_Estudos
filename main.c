#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 50000

void bubbleSort(int *array, int size) {

  for (int step = 0; step < size - 1; ++step) {
    for (int i = 0; i < size - step - 1; ++i) {
      if (array[i] > array[i + 1]) {
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}

void insertionSort(int *arr, int n){
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
           if(min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}

void shellSort(int array[], int n) {
  // Rearrange elements at each n/2, n/4, n/8, ... intervals
  for (int interval = n / 2; interval > 0; interval /= 2) {
    for (int i = interval; i < n; i += 1) {
      int temp = array[i];
      int j;
      for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
        array[j] = array[j - interval];
      }
      array[j] = temp;
    }
  }
}

void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
 
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void abcSort(int *vet,int i,int j){
    int k;
    if(vet[i] > vet[j]){
        swap(vet+i,vet+j);
    }
    if(i+1>=j)
        return;
    k = (j-i+1)/3;

    abcSort(vet,i,j-k);
    abcSort(vet,i+k,j);
    abcSort(vet,i,j-k);
}

void printTable(double *tempoDeExecucao){
    printf("Bubble Sort:    %f\n",tempoDeExecucao[0]);
    printf("Insertion Sort: %f\n",tempoDeExecucao[1]);
    printf("Selection Sort: %f\n",tempoDeExecucao[2]);
    printf("Shell Sort:     %f\n",tempoDeExecucao[3]);
    printf("Merge Sort:     %f\n",tempoDeExecucao[4]);
    printf("ABC Sort:       %f\n",tempoDeExecucao[5]);
}

int main(){
    int i;
    int *vet = (int *) malloc(TAM*sizeof(int));
    double tempoDeExecucao[6];
    int op;
    clock_t comeco,final;
    srand(time(NULL));

    printf("Ordenando o vetor, Gerando a tabela para um vetor com tamanho %d\n",TAM);
    for(op = 1;op<7;op++){
        for(i=0;i<TAM;i++){
            vet[i] = rand();
            //printf("[%d] ",vet[i]);
        }

        comeco = clock();
        switch (op){
        case 1:
            bubbleSort(vet,TAM);
        break;
        case 2:
            insertionSort(vet,TAM);
        break;
        case 3:
            selectionSort(vet,TAM);
        break;
        case 4:
            shellSort(vet,TAM);
        break;
        case 5:
            mergeSort(vet,0,TAM-1);
        break;
        case 6:
            abcSort(vet,0,TAM-1);
        break;
        }
        final = clock();
        

        tempoDeExecucao[op-1] = (double)(final - comeco) /CLOCKS_PER_SEC;
    }
   
    printTable(tempoDeExecucao);
    free(vet);
    return 0;
}