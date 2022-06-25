#include "vigenere.c"
#include "xor_cipher.c"
#pragma once
char *ini_vector="klfc'w[dy jsadsawq2w";
char *encrypt(char *text, char *key, int len){
    char *res = vigenere_encrypt(text, ini_vector, len);
    char *res2 = xor_cipher(res, key, len);
    return res2;
}
char *decrypt(char *text, char *key, int len){
    char *res = xor_decipher(text, key, len);
    char *res2 = vigenere_decrypt(res, ini_vector, len);
    return res2;
}