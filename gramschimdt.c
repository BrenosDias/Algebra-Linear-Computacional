#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

//CERTOOO

void Metodo_gramSchmidt(double** vetores, int numVetor, int tamVetor) ;


int main() {
    // Exemplo de uso
    clock_t Ticks[2];
    Ticks[0] = clock();
    double vetores[][3] = 
    {{9.0, 7.22, 6.8308}, 
    {7.22, 6.8308, 7.1269}, 
    {6.8308, 7.1269, 7.8605}}
    ;
    int numVetor = sizeof(vetores) / sizeof(vetores[0]);
    int tamVetor = sizeof(vetores[0]) / sizeof(double);
    
    double** ponteirosVetor = (double**)malloc(numVetor * sizeof(double*));
    for (int i = 0; i < numVetor; i++) {
        ponteirosVetor[i] = vetores[i];
    }
    
    Metodo_gramSchmidt(ponteirosVetor, numVetor, tamVetor);
    
    // Liberando a memória alocada
    free(ponteirosVetor);
    
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto: %g ms.", Tempo);
    getchar();
    return 0;
}

void Metodo_gramSchmidt(double** vetores, int numVetor, int tamVetor) 
{
    double** vetoresOrtogonalizados = (double**)malloc(numVetor * sizeof(double*));
    int i = 0;
    while(i < numVetor)
    {
        vetoresOrtogonalizados[i] = (double*)malloc(tamVetor * sizeof(double));
         i++;
    }
    
    for (int i = 0; i < numVetor; i++) {
        for (int j = 0; j < tamVetor; j++) {
            vetoresOrtogonalizados[i][j] = vetores[i][j];
        }
        
        for (int j = 0; j < i; j++) {
            double produtoEscalar = 0.0;
            double norma = 0.0;
            
            for (int k = 0; k < tamVetor; k++) {
                produtoEscalar =  produtoEscalar + (vetoresOrtogonalizados[j][k] * vetores[i][k]);
                norma = norma + (vetoresOrtogonalizados[j][k] * vetoresOrtogonalizados[j][k]);
            }
            
            double escalar = produtoEscalar / norma;
            
            for (int k = 0; k < tamVetor; k++) {
                vetoresOrtogonalizados[i][k] = vetoresOrtogonalizados[i][k] - (escalar * vetoresOrtogonalizados[j][k]);
            }
        }
    }
    
    // Printando os vetores ortogonalizados
    printf("Vetores ortogonalizados:\n");
    for (int i = 0; i < numVetor; i++) {
        for (int j = 0; j < tamVetor; j++) {
            printf("%f ", vetoresOrtogonalizados[i][j]);
        }
        printf("\n");
    }
    
    // Liberando a memória alocada
    while(i < numVetor)
    {
        free(vetoresOrtogonalizados[i]);
        i++;
    }
    free(vetoresOrtogonalizados);
}

