#ifndef HASHMAP_C
#define HASHMAP_C
#include <stdlib.h>
#include <string.h>
#include "sll_int.c"

typedef struct{
	const unsigned int length;
	sll_int_t **heads;	
	sll_int_t **tails;
} hashmap_int_t;

typedef struct{
	hashmap_int_t *data;
} hashmap_date_t;

/////////////////////////// HASHMAP_INT ///////////////////////////////////
hashmap_int_t* hashmap_int_init(unsigned int bucket_count){
	hashmap_int_t *result = malloc(sizeof(hashmap_int_t));
	// here we dereference the constantness of the members
	*(unsigned int *) &result->length = bucket_count;
	result->heads = calloc(result->length, sizeof(sll_int_t*));
	result->tails = calloc(result->length, sizeof(sll_int_t*));
	return result;
}

int hashmap_int_insert(hashmap_int_t *h, int key, void *value){
	// returns 0 if successful, -1 if not
	// the hash function is just modulo divison by the bucket count
	sll_int_t *result = sll_int_append(h->tails[key % h->length], key, value);	
	if(result != NULL){
		h->tails[key % h->length] = result;
		if(h->heads[key % h->length] == NULL) h->heads[key % h->length] = result;
	}
	return result == NULL;
}

void* hashmap_int_find(hashmap_int_t *h, int key){
	return sll_int_find(h->heads[key % h->length], key);
}

/////////////////////////// HASHMAP_DATE //////////////////////////////////
hashmap_date_t* hashmap_date_init(unsigned int bucket_count){
	hashmap_date_t *result = malloc(sizeof(hashmap_date_t)); 
	result->data = hashmap_int_init(bucket_count); 
	return result;
}

int* tokenize_date(char *date){
	// tokenize date format "dd.mm.yyyy" to [dd, mm, yyyy]
	char buffer[5];
	int buffer_index = 0;
	int *result = calloc(3, sizeof(int));
	int result_index = 0;
	for(int i = 0; date[i] != '\0'; i++){
		if(date[i] == '.'){
			result[result_index++] = atoi(buffer);
			if(result_index > 3){
				free(result);
				return NULL;
			}
			buffer_index = 0;
			continue;
		}		
		buffer[buffer_index++] = date[i];
		buffer[buffer_index] = '\0';
	}	
	result[result_index++] = atoi(buffer);
	return result;	
}

unsigned int intlen(unsigned int n){
	unsigned int result = 0;
	while(n != 0){
		result++;
		n /= 10;
	}	
	return result;
}

int intpow(int n, int power){
	int result = 1; 
	for(int i = 0; i < power; i++) result *= n;
	return result;
}

unsigned long long hash_date(char *date){
	// converts date format "dd.mm.yyyy" to integer "dd0mm0yyyy"
	int *date_tokens = tokenize_date(date);
	unsigned long long result = date_tokens[0];
	for(int i = 1; i <= 2; i++){
		result *= intpow(10, intlen(date_tokens[i]) + 1);
		result += date_tokens[i];
	}
	return result;
}

int hashmap_date_insert(hashmap_date_t *h, char *date, void *value){
	unsigned long long index = hash_date(date);	
	return hashmap_int_insert(h->data, index, value);
}

char* hashmap_date_find(hashmap_date_t *h, char *date){
	unsigned long long index = hash_date(date);
	return hashmap_int_find(h->data, index);
}
#endif

