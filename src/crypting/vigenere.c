#include <string.h>
#include <stdlib.h>
char shift(char text, char keyst)
{
    return (text+keyst)%127;
}

char invert(char text, char keyst)
{
    return (127+(text - keyst))%127;
}

char *vigenere_encrypt(char *text, char *key, int len)
{
    char *res = calloc(len, sizeof(char));

    char *key_temp = calloc(strlen(key) + 1, sizeof(char));
    strcpy(key_temp, key);

    int i = 0;
    for (i = 0; i < len; i++)
    {

        res[i] = shift(text[i], key_temp[i % (strlen(key) )]);
        if (i % (strlen(key) ) == 0 && i != 0)
        {
            strncpy(key_temp, &text[i - (strlen(key))], strlen(key));
            // printf("%s\n", key);
        }
    }
    res[i] = '\0';
    return res;
}
char *vigenere_decrypt(char *text, char *key, int len)
{
    char *res = calloc(len, sizeof(char));

    char *key_temp = calloc(strlen(key) + 1, sizeof(char));
    strcpy(key_temp, key);

    int i = 0;
    for (i = 0; i < len; i++)
    {

        res[i] = invert(text[i], key_temp[i % (strlen(key) )]);
        if (i % (strlen(key) )  == 0 && i != 0)
        {
            strncpy(key_temp, &res[i - (strlen(key))], strlen(key_temp));

        }

    }
    res[i] = '\0';
    return res;
}