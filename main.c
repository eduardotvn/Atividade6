#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int encontrarMaximo(int *vetor, int size) {
    int maximo = vetor[0];

    #pragma omp parallel for
    for (int i = 1; i < size; ++i) {
        #pragma omp critical
        {
            if (vetor[i] > maximo) {
                maximo = vetor[i];
            }
        }
    }

    return maximo;
}

int indiceMaximo(int* vetor, int size, int max)
{
    int indice; 

    #pragma omp parallel for
    for (int i = 1; i < size; ++i) {
        #pragma omp critical
        {
            if (vetor[i] == max) {
                indice = i;
            }
        }
    }
    
    return indice; 
}

int main() {
    int size;

    printf("Digite o tamanho do vetor(ele sera preenchido aleatoriamente entre 0 e 10000): ");
    scanf("%d", &size);

    int *vetor = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        vetor[i] = rand() % 10000;  
    }

    printf("Vetor gerado:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    double start_time = omp_get_wtime();
    int maximo = encontrarMaximo(vetor, size);
    double end_time = omp_get_wtime();

    printf("O maior valor no vetor eh: %d\n", maximo);
    printf("Tempo de execucao: %f segundos\n", end_time - start_time);
    printf("O indice e: %d", indiceMaximo(vetor, size ,maximo));
    free(vetor);  

    return 0;
}
