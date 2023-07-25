#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

void givens(double** matriz, int numLinhas, int numColunas);

int main() {
    clock_t Ticks[2];
    Ticks[0] = clock();
    // Exemplo de uso
    double matriz[][3] = 
    {{9.0, 7.22, 6.8308}, 
    {7.22, 6.8308, 7.1269}, 
    {6.8308, 7.1269, 7.8605}}
    ;
    int numLinhas = sizeof(matriz) / sizeof(matriz[0]);
    int numColunas = sizeof(matriz[0]) / sizeof(double);
    
    double** matrizPonteiros = (double**)malloc(numLinhas * sizeof(double*));
    for (int i = 0; i < numLinhas; i++) {
        matrizPonteiros[i] = matriz[i];
    }
    
    givens(matrizPonteiros, numLinhas, numColunas);
    
    // Liberando a memÃ³ria alocada
    free(matrizPonteiros);
    
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto: %g ms.", Tempo);
    getchar();
    return 0;
}

void givens(double** matriz, int numLinhas, int numColunas) {
    for (int j = 0; j < numColunas; j++) {
        for (int i = numLinhas - 1; i > j; i--) {
            if (matriz[i][j] != 0) {
                double r = hypot(matriz[i][j], matriz[i-1][j]);
                double c = matriz[i-1][j] / r;
                double s = matriz[i][j] / r;
                
                for (int k = 0; k < numColunas; k++) {
                    double temp = c * matriz[i-1][k] + s * matriz[i][k];
                    matriz[i][k] = -s * matriz[i-1][k] + c * matriz[i][k];
                    matriz[i-1][k] = temp;
                }
            }
        }
    }
    
    // Imprimindo a matriz triangular resultante
    printf("Matriz triangular:\n");
    for (int i = 0; i < numLinhas; i++) {
        for (int j = 0; j < numColunas; j++) {
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
    
}