#ifndef HASHMAP_C
#define HASHMAP_C
#include <stdlib.h>
#include <string.h>
#include "sll_int.c"

typedef struct{
	const unsigned int length;
	sll_int_t **array;	
} hashmap_int_t;

typedef struct{
	const unsigned int year_buckets, month_buckets, day_buckets;
	hashmap_int_t *data;
} hashmap_date_t;

/////////////////////////// HASHMAP_INT ///////////////////////////////////
hashmap_int_t* hashmap_int_init(unsigned int bucket_count){
	hashmap_int_t *result = malloc(sizeof(hashmap_int_t));
	// here we dereference the constantness of the members
	*(unsigned int *) &result->length = bucket_count;
	result->array = calloc(result->length, sizeof(sll_int_t*));
	return result;
}

int hashmap_int_insert(hashmap_int_t *h, int key, void *value){
	// returns 0 if successful, -1 if not
	// the hash function is just modulo divison by the bucket count
	sll_int_t *result = sll_int_append(h->array[key % h->length], key, value);	
	if(result != NULL) h->array[key % h->length] = result;
	return result == NULL;
}

void* hashmap_int_find(hashmap_int_t *h, int key){
	return sll_int_find(h->array[key % h->length], key);
}

/////////////////////////// HASHMAP_DATE //////////////////////////////////
hashmap_date_t* hashmap_date_init(unsigned int day_buckets, unsigned int month_buckets, unsigned int year_buckets){
	hashmap_date_t *result = malloc(sizeof(hashmap_date_t)); 
	*(unsigned int*) &result->year_buckets = year_buckets;
	*(unsigned int*) &result->month_buckets = month_buckets;
	*(unsigned int*) &result->day_buckets = day_buckets;
	result->data = hashmap_int_init(year_buckets); 
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

int hashmap_date_insert(hashmap_date_t *h, char *date, char *message){
	// returns 0 if successful, -1 if not
	int *date_buffer = tokenize_date(date);
	hashmap_int_t *month_hashmap = hashmap_int_find(h->data, date_buffer[2]); 
	if(month_hashmap == NULL){
		month_hashmap = hashmap_int_init(h->month_buckets);
		hashmap_int_insert(h->data, date_buffer[2], month_hashmap);
	}
	hashmap_int_t *date_hashmap = hashmap_int_find(month_hashmap, date_buffer[1]);
	if(date_hashmap == NULL){
		date_hashmap = hashmap_int_init(h->day_buckets);
		hashmap_int_insert(month_hashmap, date_buffer[1], date_hashmap);
	}
	char *result = hashmap_int_find((hashmap_int_t*) date_hashmap, date_buffer[0]);
	if(result != NULL) return -1;
	hashmap_int_insert(date_hashmap, date_buffer[0], message);
	return 0;
}

char* hashmap_date_find(hashmap_date_t *h, char *date_buffer){
	if(h == NULL) return NULL;
	int *date = tokenize_date(date_buffer);
	hashmap_int_t *month_hashmap = hashmap_int_find(h->data, date[2]);
	hashmap_int_t *day_hashmap = hashmap_int_find(month_hashmap, date[1]);
	char *result = hashmap_int_find(day_hashmap, date[0]);
	return result;
}
#endif
