#include <stdio.h>
#include <math.h>
#include <string.h>
unsigned long int mod_pow(long long x, unsigned int y, int p) // calculates (x^y) % p
{
    int res = 1;     
    x = x % p; 
    if (!x) return 0;
    while (y > 0)
    {
        if (y & 1){
            res = (res*x) % p;
        }

        y = y>>1; 
        x = (x*x) % p;
    }
    return res;
}

void rsa_encrypt(char* input, unsigned long long int crypted[], int e, int N){

	for(int i=0; input[i] != '\0'; i++){
		crypted[i] = mod_pow(input[i], e, N);
	}

}

void rsa_decrypt(unsigned long long int crypted[], unsigned long long int decrypted[], int d, int N, int len){
	for(int i=0; i < len; i++){
		decrypted[i] = mod_pow(crypted[i], d, N);
	}
}

int rsa(char *input){
    FILE *f=fopen("pass.bin", "rb");

    unsigned long long int crypted[100];
	unsigned long long int decrypted[100];
	int e = 13;
    int p = 19;
    int q = 349;
    int fn = (p-1)*(q-1);
	int d = 0; // 29
	int N = p*q;
    if(!f){
        f=fopen("pass.bin", "wb");
        rsa_encrypt(input, crypted, e, N);
        printf("Encrypted: ");
        for(int i=0; input[i] != '\0'; i++){
            printf("%lld ", crypted[i]);
        }

        printf("\n");
        
        int sz = sizeof(crypted)/sizeof(unsigned long long int);
        fwrite(&sz,sizeof(int),1, f);
        fwrite(crypted,sizeof(unsigned long long int),sz,f);

        printf("Decrypted: ");
        fclose(f);
    }

    f=fopen("pass.bin", "rb");

    int len;
    fread(&len,sizeof(int),1, f);

    unsigned long long int ddz[len];
    fread(ddz,sizeof(unsigned long long int), len,f);
	rsa_decrypt(ddz, decrypted, d, N, strlen(input));
    char decr[len];
	for(int i=0; input[i] != '\0'; i++){
		decr[i] = (char)decrypted[i];
	}
    if(strcmp(input, decr)){
        return 1;
    }
    return 0;
}