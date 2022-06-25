#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../src/searching/hashmap.c"

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

void increment_date(int *date){
	date[0]++;
	if(date[0] == 31){
		date[0] = 1;
		date[1]++;
		if(date[1] == 13){
			date[1] = 1;
			date[2]++;
		}
	}
}

char* date_to_value(int *date){
	char d[10], m[10], y[10];
	itoa_(date[0], d);	
	itoa_(date[1], m);	
	itoa_(date[2], y);	
	char *result = calloc(31, sizeof(char));
	strcat(result, d);
	strcat(result, m);
	strcat(result, y);
	return result;
}

char* date_to_string(int *date){
	char d[10], m[10], y[10];
	itoa_(date[0], d);	
	itoa_(date[1], m);	
	itoa_(date[2], y);	
	char *result = calloc(33, sizeof(char));
	strcat(result, d);
	strcat(result, ".");
	strcat(result, m);
	strcat(result, ".");
	strcat(result, y);
	return result;
}

int main(){
	printf("Enter the number of buckets in the hashmap (this will determine the speed of the searching): ");
	unsigned int bucket_count;
	scanf("%u", &bucket_count);
	hashmap_date_t *database = hashmap_date_init(bucket_count);
	int *date = calloc(3, sizeof(int));
	printf("loading data of  7 200 000 elements\n");
	for(int i = 0; i < 7200000; i++){
		char *date_buffer = date_to_string(date);
		char *value = date_to_value(date);
		hashmap_date_insert(database, date_buffer, value);
		increment_date(date);
		if(i % 720000 == 0 && i != 0) printf("loading data %.0lf%% complete\n", ((double)(i) / 720000) * 10);
	}
	printf("loading data 100%% complete\n\n");
	char *test_data[] = {
		"12.04.681",
		"29.5.1453",
		"07.07.1640",
		"23.12.1656",
		"27.12.1679",
		"01.10.1697",
		"10.03.1702",
		"12.04.2005",
		"23.02.19888",
		"20.03.16432",
		"29.11.19999"
	};
	for(int i = 0; i < 11; i++){
		clock_t begin = clock();
		char *result = hashmap_date_find(database, test_data[i]);
		clock_t end = clock();
		printf("Finding the element %s took %lfs.\n", result, (double) (end - begin)); 
		free(result);
	}
	return 0;
}
