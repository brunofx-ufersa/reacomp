#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h" 


typedef struct student {
    char *name;
    int id;
} Student;

int compare_student(void *a, void *b) {
    Student *student_a = (Student *)a;
    Student *student_b = (Student *)b;

    return student_a->id - student_b->id;
}

void free_student(void *data) {
    Student *student_ptr = (Student *)data;
    
    if (student_ptr == NULL) return; 
    if (student_ptr->name != NULL) free(student_ptr->name); 
    
    free(student_ptr);
}

Student *create_student(const char *name, int id) {
    Student *new_student = (Student *)malloc(sizeof(Student));
    if (new_student == NULL) {
        perror("Erro ao alocar Student");
        exit(EXIT_FAILURE);
    }

    new_student->id = id;
    new_student->name = strdup(name); 
    
    if (new_student->name == NULL) {
        free(new_student); 
        perror("Erro ao alocar nome");
        exit(EXIT_FAILURE);
    }

    return new_student;
}

int main() {

    List *list = list_create(sizeof(Student), free_student, compare_student);
    const char *names[] = {"Alice", "Bob", "Charlie", "Diana"};
    int ids[] = {101, 205, 303, 408};

    for (int i = 0; i < 4; i++) {
        Student *s = create_student(names[i], ids[i]);
        list_add(list, s); 
        printf("Aluno %s com ID %d adicionado\n", s->name, s->id);
    }
   printf("----------------------------------------\n");

    Student search_key = {.name = NULL, .id = 303}; 
    
    printf("Procurando aluno com ID: %d...\n", search_key.id);
    if (list_contains(list, &search_key)) {
        printf("-> Sucesso: Aluno ID %d encontrado!\n", search_key.id);
    } else {
        printf("-> Falha: Aluno ID %d não encontrado.\n", search_key.id);
    }
    printf("----------------------------------------\n");

    printf("Destruindo a lista e liberando toda a memória restante.\n"); 
    list_destroy(list);
    list = NULL;	

    printf("Programa concluído. Memória limpa com sucesso.\n");

    return 0;

/*
 int item[5] = {2, 5, 3, 8, 9};

    // Adicionando elementos
    for (int i = 0; i < 5; i++) {
        int *data = malloc(sizeof(int));
        *data = item[i];
        list_add(list, data);

        free(data);
    }

    // Verificar se um valor está na lista
    int valor = 4;
    if (list_contains(list, &valor)) {
        printf("Valor %d encontrado na lista!\n", valor);
    } else {
        printf("Valor %d não encontrado.\n", valor);
    }

    
    // Verificar se um valor está na lista
    valor = 5;
    list_iterate(list, procurar_valor, &valor);


    // Iterar e imprimir elementos
    printf("Conteúdo da lista:\n");
    list_iterate(list, print_int, NULL);

    int total = 0;
    list_iterate(list, somar_elementos, &total);
    printf("Soma = %d\n", total);
    list_iterate(list, contar_pares, NULL);
    list_iterate(list, dobrar_valores, NULL);
    list_iterate(list, print_int, NULL);

    list_destroy(list);
    list = NULL;
*/
    return 0;
}