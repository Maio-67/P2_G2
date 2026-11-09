#include <stdio.h>
#include <math.h>

#define MAX_LEITURAS_LIMITE 100

void limpar_linha(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_limite_leituras(int *max_leituras) {
    int resultado_leitura;

    printf("Introduza o numero maximo de leituras (1-%d): ", MAX_LEITURAS_LIMITE);
    while ((resultado_leitura = scanf("%d", max_leituras)) != 1
           || *max_leituras <= 0
           || *max_leituras > MAX_LEITURAS_LIMITE) {
        if (resultado_leitura == EOF) {
            return 0;
        }
        printf("Valor invalido. Introduza um inteiro entre 1 e %d: ", MAX_LEITURAS_LIMITE);
        limpar_linha();
    }
    return 1;
}

int executar_programa(void) {
    int max_leituras;
    int sensores[MAX_LEITURAS_LIMITE];
    double temperaturas[MAX_LEITURAS_LIMITE];
    int i;
    double soma = 0.0, media, soma_quadrados = 0.0, desvio_padrao;

    if (!ler_limite_leituras(&max_leituras)) {
        return 1;
    }

    for (i = 0; i < max_leituras; i++) {
        printf("Leitura %d - ID do sensor e temperatura: ", i + 1);
        if (scanf("%d %lf", &sensores[i], &temperaturas[i]) != 2) {
            if (feof(stdin)) {
                max_leituras = i;
                break;
            }
            printf("Entrada invalida. Tente novamente.\n");
            limpar_linha();
            i--;
            continue;
        }
        soma += temperaturas[i];
    }

    if (max_leituras == 0) {
        printf("Nao foram introduzidas leituras.\n");
        return 0;
    }

    media = soma / max_leituras;
    for (i = 0; i < max_leituras; i++) {
        soma_quadrados += pow(temperaturas[i] - media, 2);
    }
    desvio_padrao = sqrt(soma_quadrados / max_leituras);

    printf("\nLeituras registadas: %d\n", max_leituras);
    printf("Media: %.2f\n", media);
    printf("Desvio padrao: %.2f\n", desvio_padrao);

    return 0;
}

int main(void) {
    return executar_programa();
}