#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


List *list_create(size_t data_size, cb_free free_data, cb_compare compare_data) {
	assert(data_size > 0);	

	List *list = malloc(sizeof(List));
	list->data_size = data_size;
	list->head = NULL;
	list->free_data = free_data;
	list->compare_data = compare_data;
	return list;
}

void list_add(List *list, void *data) {
    assert(list != NULL);
    assert(data != NULL);

    Node *newNode = calloc(1, sizeof(Node));
    newNode->data = malloc(list->data_size);
    memcpy(newNode->data, data, list->data_size);

    newNode->next = list->head;
    list->head = newNode;
}

static void free_node_data(cb_free free_data, void *data) { 
	if (free_data != NULL) 
		free_data(data); 
	else 
		free(data); 
}

void list_destroy(List *list){
	assert(list != NULL);
	
	Node *node = list->head;
		
	while (node != NULL){
		Node *next = node->next; // guarda o próximo antes de liberar
		free_node_data(list->free_data, node->data);
		free(node);
		node = next;
	}
	
	free(list);
}

bool list_contains(List *list, void *data) {
	assert(list->compare_data != NULL);
	
	Node *node = list->head;
	while (node != NULL)	{
		if (list->compare_data(node->data, data) == 0)
			return true;		
		node = node->next;
	}
	return false;
}
