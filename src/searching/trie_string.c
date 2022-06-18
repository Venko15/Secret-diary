#ifndef TRIE_STRING_C
#define TRIE_STRING_C
#include <stdlib.h>
#include <string.h>

typedef struct trie_string_node_t{
	char *value;
	// symbols: [a-z], [A-Z], [,.]
	struct trie_string_node_t *next[54];
} trie_string_node_t;

typedef struct{
	trie_string_node_t *root;	
} trie_string_t;

///////////////////////////// NODE STUFF ///////////////////////////////
trie_string_node_t* trie_string_node_init(char *value){
	trie_string_node_t *result = malloc(sizeof(trie_string_node_t));
	result->value = value;
	for(int i = 0; i < 54; i++) result->next[i] = NULL;
	return result;
}

int trie_string_node_hash(char c){
	// returns the coresponding index in the array
	if(c >= 'a' && c <= 'z') return c - 'a';
	if(c >= 'A' && c <= 'Z') return c - 'A';
	if(c == ',') return 52;
   	if(c == '.') return 53;
	return -1;	
}

int trie_string_node_insert(trie_string_node_t *root, char *name, char *value){
	// returns 0 if successful, -1 if not
	if(root == NULL || name == NULL || value == NULL) return -1;	
	if(name[0] == '\0'){
		root->value = calloc(strlen(value) + 1, sizeof(char));	
		strcpy(root->value, value);
		return 0;
	}
	int next_node_index = trie_string_node_hash(name[0]);
	if(next_node_index == -1) return -1;
	if(root->next[next_node_index] == NULL){
		root->next[next_node_index] = trie_string_node_init(NULL);	
	}
	return trie_string_node_insert(root->next[next_node_index], name + 1, value);
}

char* trie_string_node_find(trie_string_node_t *root, char *name){
	if(root == NULL || name == NULL) return NULL;
	if(name[0] == '\0') return root->value;
	int next_node_index = trie_string_node_hash(name[0]);
	if(next_node_index == -1) return NULL;
	return trie_string_node_find(root->next[next_node_index], name + 1);
}

///////////////////////////// TREE STUFF ///////////////////////////////
trie_string_t* trie_string_init(){
	trie_string_t *result = malloc(sizeof(trie_string_t));
	result->root = trie_string_node_init(NULL);
	return result;
}

int trie_string_insert(trie_string_t *t, char *name, char *value){
	return trie_string_node_insert(t->root, name, value);
}

char* trie_string_find(trie_string_t *t, char *name){
	return trie_string_node_find(t->root, name);
}

#endif
