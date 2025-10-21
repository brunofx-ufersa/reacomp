#include <stdbool.h>
#include <stddef.h>

typedef void(*cb_free)(void *);
typedef int(*cb_compare)(void *a, void *b);

typedef struct node {
    void* data;          // Ponteiro genérico para o dado
    struct node* next;
} Node;

typedef struct {
  size_t data_size;
	Node *head;	
  // Funções de callback para o tipo de dado
  cb_free free_data;
  cb_compare compare_data;
} List;


List* list_create(size_t data_size, cb_free free_data, cb_compare compare_data);
void list_add(List *list, void *data);
void list_destroy(List *list);
bool list_contains(List *list, void *data);
