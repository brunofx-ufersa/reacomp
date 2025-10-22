#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    Operation operations[] = {add_int, multiply_int};
    size_t n_operations = sizeof(operations) / sizeof(operations[0]); 
    
    // 1. CRIAÇÃO E TRATAMENTO DE ERRO
    Calculator* calculator_int = calculator_create(sizeof(int), n_operations, operations);

    if (calculator_int == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar a estrutura Calculator.\n");
        return 1;
    }
    
    // Dados para teste
    int a = 10;
    int b = 2;
    
    // 2. SELEÇÃO E EXECUÇÃO
    Operation selected_op = select_operation_int(); 
    
    if (selected_op == NULL) {
        fprintf(stderr, "Erro: Operação inválida selecionada.\n");
        calculator_destroy(calculator_int); // Limpa o que foi criado
        return 1;
    }

    // Chama evaluation, que aloca o resultado na heap
    void *result_ptr = evaluation(&a, &b, selected_op);
    
    if (result_ptr == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o resultado.\n");
        calculator_destroy(calculator_int); // Limpa o que foi criado
        return 1;
    }
    
    printf("Resultado: %d\n", *(int*)result_ptr);

    // 3. LIMPEZA DA MEMÓRIA
    
    // 3.1 Libera a memória alocada DENTRO do callback
    free(result_ptr); 
    
    // 3.2 Libera a estrutura Calculator e suas operações internas
    calculator_destroy(calculator_int); 
    calculator_int = NULL; // Boa prática: anular o ponteiro
    
    return 0;
}
