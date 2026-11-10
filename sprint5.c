#include <stdio.h>
#include <math.h>

#define MAX_LEITURAS      5
#define VALOR_TERMINO     -1

double converter_sensor_para_temperatura(int valor_sensor) {
    return 260.0 * valor_sensor / 1023 - 20.0;
}

int temperatura_valida(double temperatura) {
    return temperatura > -10.0 && temperatura < 190.0;
}

int ler_inteiro(void) {
    int valor;
    int c;
    int i = 1;

    while (i) {
        int ok = scanf("%d", &valor);
        c = getchar();
        if (ok == i && (c == '\n' || c == EOF)) {
            return valor;
        }
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
        if (c == EOF) {
            return VALOR_TERMINO;      // a entrada acabou
        }
        printf("Valor inválido, tente novamente.\n");
    }
}

int ler_sequencia(int valores_sensor[], double temperaturas[], int max_leituras) {
    int total = 0;

    while (total < max_leituras) {
        int valor = ler_inteiro();
        if (valor == VALOR_TERMINO) {
            break;
        }
        double temperatura = converter_sensor_para_temperatura(valor);
        if (temperatura_valida(temperatura)) {
            printf("%.2f\n", temperatura);
            valores_sensor[total] = valor;
            temperaturas[total] = temperatura;
            total++;
        } else {
            printf("Valor fora da gama\n");
        }
    }
    return total;
}

double calcular_minimo(const double valores[], int total) {
    double minimo = valores[0];
    for (int i = 1; i < total; i++) {
        if (valores[i] < minimo) minimo = valores[i];
    }
    return minimo;
}

double calcular_maximo(const double valores[], int total) {
    double maximo = valores[0];
    for (int i = 1; i < total; i++) {
        if (valores[i] > maximo) maximo = valores[i];
    }
    return maximo;
}

double calcular_media(const double valores[], int total) {
    double soma = 0.0;
    for (int i = 0; i < total; i++) {
        soma += valores[i];
    }
    return soma / total;
}

double calcular_desvio_padrao(const double valores[], int total) {
    double media = calcular_media(valores, total);
    double soma_quadrados = 0.0;
    for (int i = 0; i < total; i++) {
        soma_quadrados += (valores[i] - media) * (valores[i] - media);
    }
    return sqrt(soma_quadrados / total);
}

void apresentar_resultados(const int valores_sensor[], const double temperaturas[], int total) {
    printf("\nValores lidos (sensor -> temperatura):\n");
    for (int i = 0; i < total; i++) {
        printf("%d -> %6.2f\n", valores_sensor[i], temperaturas[i]);
    }

    printf("\nNúmero de valores lidos: %d\n", total);
    if (total > 0) {
        printf("Temperatura mínima:%10.2f\n", calcular_minimo(temperaturas, total));
        printf("Temperatura máxima:%10.2f\n", calcular_maximo(temperaturas, total));
        printf("Temperatura média: %10.2f\n", calcular_media(temperaturas, total));
        printf("Desvio-padrão:     %10.2f\n", calcular_desvio_padrao(temperaturas, total));
    }
}

int main(void) {
    int valores_sensor[MAX_LEITURAS];
    double temperaturas[MAX_LEITURAS];

    int total = ler_sequencia(valores_sensor, temperaturas, MAX_LEITURAS);
    apresentar_resultados(valores_sensor, temperaturas, total);

    return 0;
}