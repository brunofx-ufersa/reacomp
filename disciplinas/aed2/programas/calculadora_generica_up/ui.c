#include "calculator.h"
#include "ui.h"
#include <stdio.h>

Operation select_operation_int() {
    int option = 0;
    
    printf("Escolha sua operação:\n");
    printf("1. Soma\n");
    printf("2. Multiplicação\n");
    printf("Digite: ");
    scanf("%d", &option);

    if (option == 1) return add_int;
    else if (option == 2) return multiply_int;
    else return NULL; // Retorna NULL como ponteiro de função inválido
}

Operation select_operation_double() {
    int option = 0;
    
    printf("Escolha sua operação:\n");
    printf("1. Soma\n");
    printf("2. Multiplicação\n");
    printf("Digite: ");
    scanf("%d", &option);

    if (option == 1) return add_double;
    else if (option == 2) return multiply_double;
    else return NULL; // Retorna NULL como ponteiro de função inválido
}

