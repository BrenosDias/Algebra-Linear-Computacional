#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// dá erro a partir da segunda linha da matriz

void householder(double **a, double **v, int m, int n) {
    int i, j;
    double norma_v, produtoInterno_v_a, somaQuadradosRestantes_v;

    for (i = 0; i < n; i++) {
        /* define v[i] como um subvetor a[i][i : m] */
        for (j = 0; j < m - i; j++) {
            v[i][j] = a[i][i + j];
        }

        /* somaQuadradosRestantes_v = ||v[i]||^2 - v[i][0] * v[i][0]; como somaQuadradosRestantes_v
           não é afetado pela mudança em v[i][0], armazenar esse valor
           evita a necessidade de recalcular toda a norma de v[i]
           após atualizar v[i][0] no próximo passo */
        somaQuadradosRestantes_v = 0.0;
        for (j = 1; j < m - i; j++) {
            somaQuadradosRestantes_v = somaQuadradosRestantes_v + ( v[i][j] * v[i][j] );
        }

        /* define v[i][0] = v[i][0] + sign(v[i][0]) * ||v[i]|| */
        if (v[i][0] < 0) {
            v[i][0] =  v[i][0] - ( sqrt(v[i][0] * v[i][0] + somaQuadradosRestantes_v) );
        } else {
            v[i][0] = v[i][0] + ( sqrt(v[i][0] * v[i][0] + somaQuadradosRestantes_v) );
        }

        /* normaliza v[i] */
        norma_v = sqrt(v[i][0] * v[i][0] + somaQuadradosRestantes_v);
        for (j = 0; j < m - i; j++) {
            v[i][j] /= norma_v;
        }

        for (j = i; j < n; j++) {
            /* define a[j][i:m] = a[j][i:m] - 2 * (v[i]^T a[j][i:m]) * v[i] */
            produtoInterno_v_a = 0.0;
            for (int k = 0; k < m - i; k++) {
                produtoInterno_v_a = produtoInterno_v_a + ( v[i][k] * a[j][i + k] );
            }
            produtoInterno_v_a *= 2;
            for (int k = 0; k < m - i; k++) {
                a[j][i + k] = a[j][i + k] - ( produtoInterno_v_a * v[i][k] );
            }
        }
    }
}

int main() {
    clock_t Ticks[2];
    Ticks[0] = clock();
    int i, j, m, n;
    double x;

    /* permitir que o usuário defina a dimensão da matriz A */
    printf("Digite a dimensão m (onde A é uma matriz m por n): ");
    scanf("%i", &m);
    printf("Digite a dimensão n (onde A é uma matriz m por n): ");
    scanf("%i", &n);

    /* verificar se m < n */
    if (m < n) {
        printf("Para uma fatoração bem-sucedida, esta implementação requer n <= m.\nEncerrando o programa.\n");
        return 0;
    }

    /* alocar memória para A e os vetores v */
    double **a = (double **)malloc(n * sizeof(double *));
    double **v = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        a[i] = (double *)malloc(m * sizeof(double));
        v[i] = (double *)malloc((m - i) * sizeof(double));
    }

    a[0][0] = 9.0;
    a[0][1] = 7.22;
    a[0][2] = 6.8308;
    a[1][0] = 7.22;
    a[1][1] = 6.8308;
    a[1][2] = 7.1269;
    a[2][0] = 6.8308;
    a[2][1] = 7.1269;
    a[2][2] = 7.8605;

    /* inicializar os valores na matriz A */
   /* for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (j < i) {
                a[i][j] = 0;
            } else {
                a[i][j] = j - i + 1; // esta escolha de valores foi arbitrária
            }
        }
    }

    /* imprimir a matriz A antes de chamar a função householder */
    printf("A = \n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%9.6g ", a[j][i]);
        }
        printf("\n");
    }
    printf("\n");

    householder(a, v, m, n);

    /* imprimir a matriz R (armazenada em A) após chamar a função householder */
    printf("R = \n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%9.6g ", a[j][i]);
        }
        printf("\n");
    }
    printf("\n");

    /* imprimir os vetores v após chamar a função householder */
    for (i = 0; i < n; i++) {
        printf("v[%i] = ", i);
        for (j = 0; j < m - i; j++) {
            printf("%9.6g ", v[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* imprimir evidência numérica de que os vetores v estão normalizados */
    printf("Verificação numérica de que v_1, ..., v_%i estão normalizados:\n", n);
    for (i = 1; i < n; i++) {
        x = 0.0;
        for (j = 0; j < m - i + 1; j++) {
            x += v[i - 1][j] * v[i - 1][j];
        }
        printf("||v[%i]|| = %lg, ", i, x);
        if (i % 5 == 0) {
            printf("\n");
        }
    }
    x = 0.0;
    for (j = 0; j < m - n + 1; j++) {
        x += v[n - 1][j] * v[n - 1][j];
    }
    printf("||v[%i]|| = %lg.", n, x);
    if (n % 5 != 0)
        printf("\n");
    printf("\n");

    /* liberar memória */
    for (i = 0; i < n; i++) {
        free(a[i]);
        free(v[i]);
    }
    free(a);
    free(v);
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto: %g ms.", Tempo);
    getchar();
    return 0;
}