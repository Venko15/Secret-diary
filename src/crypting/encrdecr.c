#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char encrypt(char text, char keyst)
{
    return text ^ keyst;
}

char decrypt(char text, char keyst)
{

    return text ^ keyst;
}

char *viginere_encrypt(char *text, char *key, int len)
{
    char *res = calloc(len, sizeof(char));

    char *key_temp = calloc(strlen(key) + 1, sizeof(char));
    strcpy(key_temp, key);

    int i = 0;
    for (i = 0; i < len; i++)
    {

        res[i] = encrypt(text[i], key_temp[i % (strlen(key) )]);

        if (i % 7 == 0 && i != 0)
        {
            strncpy(key_temp, &text[i - 7], strlen(key));
            // printf("%s\n", key);
        }
    }
    res[i] = '\0';
    return res;
}

char *viginere_decrypt(char *text, char *key, int len)
{

    char *res = calloc(len, sizeof(char));

    char *key_temp = calloc(strlen(key) + 1, sizeof(char));
    strcpy(key_temp, key);

    int i = 0;
    for (i = 0; i < len; i++)
    {

        res[i] = decrypt(text[i], key_temp[i % (strlen(key))]);

        if (i % 7 == 0 && i != 0)
        {
            strncpy(key_temp, &res[i - 7], strlen(key_temp));

        }
    }
    res[i] = '\0';
    return res;
}

int main()
{

    char text[] = "Satisfied conveying an dependent contented he gentleman agreeable do be. Warrant private blushes removed an in equally totally if. Delivered dejection necessary objection do mr prevailed. Mr feeling do chiefly cordial in do. Water timed folly right aware if oh truth. Imprudence attachment him his for sympathize. Large above be to means. Dashwood do provided stronger is. But discretion frequently sir the she instrument unaffected admiration everything.";
    char key[] = "oho";
    int len = strlen(text)+1;
    char *res = viginere_encrypt(text, key, len);
    char *res2 = viginere_decrypt(res, key, len);
    FILE *f = fopen("a.bin", "wb+");
    fwrite(res,sizeof(char), len, f);
    fclose(f);
    f = fopen("a.bin", "rb");
    char ch;

    int CUR_MAX = 750;
    char *buffer = (char *)malloc(sizeof(char) * CUR_MAX); 
    int length = 0;

    int size = fread(buffer, sizeof(char), CUR_MAX, f);
    char *end = viginere_decrypt(buffer, key, size);
    for(int i = 0 ; i < size; i++){
        printf("%c", end[i]);
    }
}
