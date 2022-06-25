#include <string.h>
char encrypt(char text, char keyst)
{
    return text ^ keyst;
}

char decrypt(char text, char keyst)
{

    return text ^ keyst;
}

char *xor_cipher(char *text, char *key, int len)
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

char *xor_decipher(char *text, char *key, int len)
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
