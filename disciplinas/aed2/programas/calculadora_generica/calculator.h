#include <stddef.h> 

typedef void* (*Operation)(const void*, const void*);

typedef struct calculator {
    size_t data_size;
    size_t n_operations;
    Operation *operations; 
} Calculator;

Calculator *calculator_create(size_t data_size, size_t n_operations, const Operation *operations);

void calculator_destroy(Calculator *calc);

void* evaluation(const void *a, const void *b, Operation operation); 

void* add_int (const void *a, const void *b);
void* add_double (const void *a, const void *b);
void* multiply_int (const void *a, const void *b);
void* multiply_double (const void *a, const void *b);

Operation select_operation_int();
Operation select_operation_double();

