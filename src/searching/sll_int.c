#ifndef SLL_INT_C
#define SLL_INT_C
#include <stdlib.h>

typedef struct sll_int{
	int key;
	void *value;
	struct sll_int *next; 	
} sll_int_t;

sll_int_t* sll_int_init(int key, void *value){
	sll_int_t *result = malloc(sizeof(sll_int_t));
	result->key = key;
	result->value = value;
	result->next = NULL;
	return result;
}

sll_int_t* sll_int_append(sll_int_t *head, int key, void *value){
	// returns the pointer head if successful, returns NULL if not
	if(head == NULL) return sll_int_init(key, value);
	sll_int_t *new_node = sll_int_init(key, value);	
	sll_int_t *temp = head;
	while(temp->next != NULL){
		if(temp->key == key) return NULL;	
		temp = temp->next;
	}
	temp->next = new_node;
	return head;
}

void* sll_int_find(sll_int_t *s, int key){
	if(s == NULL) return NULL;
	while(s != NULL){
		if(s->key == key) return s->value;
		s = s->next;
	}
	return NULL;
}

#endif
