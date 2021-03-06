#include <stdio.h>
#include <stdlib.h>
#include "../../src/crypting/encrypt.c"
#include "../../src/searching/hashmap.c"
char* fix_date(char *date){
    int *tokens = tokenize_date(date);    
    if(tokens[0] > 31 || tokens[1] > 12) return NULL;
    char *result = calloc(11, sizeof(char));
    result[10] = '\0';
    result[2] = '.';
    result[5] = '.';
    for(int i = 0; i < 2; i++){
        result[3 * i] = '0' + tokens[i] / 10;    
        result[1 + 3 * i] = '0' + tokens[i] % 10;
    }
    for(int i = 0; i < 4; i++){
        result[6 + i] = '0' + (tokens[2] / intpow(10, 3 - i)) % 10;
    }
    return result;
}
int main(){
    //printf("%s\n", fix_date("1.1.1"));
    char plaintext[] = "Do am he horrible distance marriage so although. Afraid assure square so happen mr an before. His many same been well can high that. Forfeited did law eagerness allowance improving assurance bed. Had saw put seven joy short first. Pronounce so enjoyment my resembled in forfeited sportsman. Which vexed did began son abode short may. Interested astonished he at cultivated or me. Nor brought one invited she produce her.";
    char key[] = "Az sum Venelin Novakov";

    char *date = calloc(20, sizeof(char));
    scanf("%s",date);
    date = fix_date(date);
    int date_len = strlen(date);
    int text_len = strlen(plaintext)+date_len+1;

    char *text = calloc(text_len,sizeof(char));
    strcat(text,date);
    strcat(text,"$") ;
    strcat(text,plaintext);

    char *encrypted = encrypt(text,key,text_len);
    FILE *f = fopen("test.bin", "wb");
    fwrite(encrypted,sizeof(char), text_len, f);
    fclose(f);
    f = fopen("test.bin", "rb");

    int file_sz ;
    fseek(f, 0, SEEK_END);
    file_sz = ftell(f);
    rewind(f);
    //printf("%d\n", file_sz);
    char *buffer = (char *)calloc(file_sz,sizeof(char)); 
    
    fread(buffer, sizeof(char), file_sz, f);
    char *end = decrypt(buffer, key, file_sz);
    char *decrypted = calloc(strlen(end)+1, sizeof(char));

    for(int i = 0; end[i]!='$' ;i++){
        printf("%c", end[i]);
    }

    strcpy(decrypted,end+date_len+1);
    printf("\n%s",decrypted);
}