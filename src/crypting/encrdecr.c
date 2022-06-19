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
    char *res3=calloc(3000, sizeof(char));
    char *res = viginere_crypt("Super customers** - only smartasses,Sleeky tycoons ...v Ooo.Super customers - only smartasseSleeky tycoons ... Ooo.Ale-le-ley, again... Ale-le-ley, again..Ale-le-ley, again... Ale-le-ley, again...ll of them are in Saint-Tropez, others are at the Maldives,In Dubai are the rest (of them)! Ah, le-le-le...All of them are in Saint-Tropez -others are in the MaldivesIn Dubai are the rest (of them)! Ah, le-le-le...Ale-le-ley, again... Ale-le-ley, again...Ale-le-ley, again... Ale-le-ley, again", key,strlen(key));
    char *res2 = viginere_decrypt(res, key,strlen(key));
    FILE *f = fopen("aa.txt", "w");
    fprintf(f, res);
    fgets(res3,512, f);
    printf("%s\n", viginere_decrypt(res, key, sz+1));
    

}