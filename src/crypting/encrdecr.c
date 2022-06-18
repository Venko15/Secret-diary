#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char keyidk;
char encrypt(char text, char keyst){
    int key = keyst-keyidk;
    char res;
    res = keyidk+ (text - keyidk+key);
    
    return res;

}
char decrypt(char text, char keyst){
    int key = keyst-keyidk;
    char res;
    char letter_alphabet_idx = text - keyidk;
    res = keyidk + (letter_alphabet_idx - key);
    
    return res;
}
char *viginere_crypt(char *text, char *key, int keysz){
    int cnt=0;
    char *res = calloc(strlen(text)+1, sizeof(char));
    for(int i = 0;i<strlen(text);i++){
        res[i] = encrypt(text[i], key[(cnt)]); 
        cnt++;
        if(cnt>=keysz){
            cnt = 0;
        }
    }
    res[strlen(text)] = '\0';
    return res;
}
char *viginere_decrypt(char *text, char *key, int keysz){
    int cnt = 0;
    char *res = calloc(strlen(text)+1, sizeof(char));
    for(int i = 0;i<strlen(text);i++){
        res[i] = decrypt(text[i], key[(cnt)%keysz]); 
        //printf("%c = %c    key - %c\n", text[i], res[i], key[cnt]);
        cnt++;
        if(cnt>=keysz){
            cnt = 0;
        }
    }
    res[strlen(text)] = '\0';
    return res;
}


int main(){

    char *key = "tisi gei ";
    int sz = sizeof(key)/sizeof(char);
    keyidk = key[sz];
    char *res=calloc(3000, sizeof(char));
    //char *res = viginere_crypt("Hodi na praida shiban mindil skapan ti izsuhne sichko bez praneto", key,strlen(key));
    //char *res2 = viginere_decrypt(res, key,strlen(key));
    FILE *f = fopen("aa.txt", "r");
    fgets(res,512, f);
    printf("%s\n", viginere_decrypt(res, key, sz+1));
    

}