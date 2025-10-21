#include "calculator.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

Calculator *calculator_create(size_t data_size, size_t n_operations, const Operation *operations) {
	assert(data_size > 0);
    assert(n_operations > 0); 	
    assert(operations != NULL); 
    
	Calculator *calc = (Calculator *)malloc(sizeof(Calculator));
	calc->data_size = data_size;
    calc->n_operations = n_operations;
    calc->operations = (Operation *)malloc(sizeof(Operation) * n_operations);

    if (calc->operations == NULL) {
        free(calc);
        return NULL;
    }

    memcpy(calc->operations, operations, sizeof(Operation) * n_operations);

    return calc;
}


void calculator_destroy(Calculator *calc) {
    if (calc == NULL) return;
    
    if (calc->operations != NULL) {
        free(calc->operations);
        calc->operations = NULL; 
    }
    
    free(calc);
}


void* evaluation(const void *a, const void *b, Operation operation){
    return operation(a, b);
} 

// Callbacks para Soma 
void* add_int (const void *a, const void *b){
    int *result = malloc(sizeof(int));
    *result = *(int*)a + *(int*)b; 
    
    return (void*)result; 
}

void* add_double (const void *a, const void *b){
    double *result = malloc(sizeof(double));
    *result = *(double*)a + *(double*)b; 
    
    return (void*)result; 
}

// Callbacks para Multiplicação 
void* multiply_int (const void *a, const void *b){
    int *result = malloc(sizeof(int));
    *result = *(int*)a * *(int*)b; 
    
    return (void*)result; 
}


void* multiply_double (const void *a, const void *b){
    double *result = malloc(sizeof(double));
    *result = *(double*)a * *(double*)b; 
    
    return (void*)result; 
}


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

