#include <stdio.h>
#include <math.h>

#define MAX_LEITURAS 20

int main(void) {
    int max_leituras = MAX_LEITURAS;

    printf("Introduza o numero maximo de leituras (ex: 5): ");
    while (scanf("%d", &max_leituras) != 1 || max_leituras <= 0) {
        printf("Valor invalido. Introduza um numero inteiro positivo para o limite de leituras: ");
        while (getchar() != '\n'); 
    }
 
    int sensores[max_leituras];
    double temperaturas[max_leituras];
    int count = 0;
    int valor_sensor;

    printf("Introduza os valores do sensor (ou -1 para terminar):\n");

    while (count < max_leituras) {
        printf("Leitura %d: ", count + 1);
        if (scanf("%d", &valor_sensor) != 1) {
            printf("(valor rejeitado, e pedido novo valor)*\n");
            while (getchar() != '\n'); 
            continue;
        }
        if (valor_sensor == -1) {
            break;
        }
        double temp = (260.0 * valor_sensor / 1023.0) - 20.0;
        if (temp < -10.0 || temp > 190.0) {
            printf("Valor fora da gama\n");
            continue; 
        }
        sensores[count] = valor_sensor;
        temperaturas[count] = temp;
        count++;
    }
    if (count == 0) {
        printf("\nNenhum valor valido foi registado.\n");
        return 0;
    }
    printf("\nValores lidos (sensor -> temperatura):\n");
    for (int i = 0; i < count; i++) {
        printf("%d -> %.2f\n", sensores[i], temperaturas[i]);
    }
    double soma = 0;
    double min = temperaturas[0];
    double max = temperaturas[0];

    for (int i = 0; i < count; i++) {
        soma += temperaturas[i];
        if (temperaturas[i] < min) min = temperaturas[i];
        if (temperaturas[i] > max) max = temperaturas[i];
    }

    double media = soma / count;
    double soma_diferencas_quadrado = 0;
    for (int i = 0; i < count; i++) {
        soma_diferencas_quadrado += pow(temperaturas[i] - media, 2);
    }
    double desvio_padrao = sqrt(soma_diferencas_quadrado / count);
    printf("\nNumero de valores lidos: %d\n", count);
    printf("Temperatura minima:      %.2f\n", min);
    printf("Temperatura maxima:      %.2f\n", max);
    printf("Temperatura media:       %.2f\n", media);
    printf("Desvio-padrao:           %.2f\n", desvio_padrao);

    return 0;
}