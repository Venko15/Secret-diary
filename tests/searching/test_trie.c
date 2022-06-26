#include <stdio.h>
#include <stdlib.h>
#include <time.h> // za testvane

#include "../../src/searching/trie.c"

int increment_char(char *c){
	if(*c == 'Z'){
		*c = 'A';
		return 1;
	}else{
		*c = *c + 1;
	}
	return 0;
}

void increment(char *string){
	int index = 4;	
	for(int i = 0; i < 5; i++){
		if(!increment_char(&string[index - i])) return;
	}
}

void reverse(char s[]){
     int i, j;
     char c;
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
	}
}

void itoa_(int n, char s[]){
	int i, sign;
    if ((sign = n) < 0)  /* record sign */
	    n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
	    s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
   	if (sign < 0)
    	s[i++] = '-';
 	s[i] = '\0';
	reverse(s);
}

int main(){
	int count = 1;
	char name[] = "AAAAA";
	trie_string_t *database = trie_string_init();
	printf("loading data of 11 881 365 elements\n");
	for(int i = 0; i < 11881375; i++){
		char *buffer = calloc(9, sizeof(char));
		itoa_(count, buffer);
		trie_string_insert(database, name, buffer);
		count++;
		increment(name);
		if((i+1) % 456976 == 0){
			printf("loading data %.0lf%% complete\n", ((double)(i) / 456975) * 3.85f);
		}
	}
	printf("loading data 100%% complete\n\n");

	char *test_data[11] = {
		"AAAAC",
		"MFYWP",
		"JDSVG",
		"EHHRX",
		"XIRGH",
		"XHWLO",
		"JXWUD",
		"KKXIE",
		"HRFFM",
		"WCEFD",
		"BCBCB"};
	for(int i = 0; i < 11; i++){
		clock_t begin = clock();
		char* result = trie_string_find(database, test_data[i]);
		clock_t end = clock();
		printf("Finding the element %s took %lfs.\n", result, (double)(end - begin) / CLOCKS_PER_SEC);
	}
	return 0;
}
