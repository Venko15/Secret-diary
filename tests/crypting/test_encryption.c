#include <stdio.h>
#include <stdlib.h>
#include "../../src/crypting/encrypt.c"


int main(){

    char text[] = "Do am he horrible distance marriage so although. Afraid assure square so happen mr an before. His many same been well can high that. Forfeited did law eagerness allowance improving assurance bed. Had saw put seven joy short first. Pronounce so enjoyment my resembled in forfeited sportsman. Which vexed did began son abode short may. Interested astonished he at cultivated or me. Nor brought one invited she produce her.";
    char key[] = "hoh";
    int len = strlen(text)+1;
    char *res = encrypt(text,key,len);
    FILE *f = fopen("test.bin", "wb");
    fwrite(res,sizeof(char), len, f);
    fclose(f);
    f = fopen("test.bin", "rb");

    int file_sz ;
    fseek(f, 0L, SEEK_END);
    file_sz = ftell(f);
    rewind(f);
    printf("%d\n", file_sz);
    char *buffer = (char *)calloc(file_sz,sizeof(char)); 
    int length = 0;

    int size = fread(buffer, sizeof(char), file_sz, f);
    char *end = decrypt(buffer, key, file_sz);
    printf("%s\n", end);
}