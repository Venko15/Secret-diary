#include <stdio.h>
#include <math.h>
#include <string.h>


unsigned long int mod_pow(long long x, unsigned int y, int p) // calculates (x^y) % p
{
    int res = 1;     // Initialize result
 
    x = x % p; // Update x if it is more than or
                // equal to p
  
    if (x == 0) return 0; // In case x is divisible by p;
 
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

void rsa_encrypt(char* input, 
	unsigned long long int crypted[], int e, int N){
	for(int i=0; input[i] != '\0'; i++){
		crypted[i] = mod_pow(input[i], e, N);
	}
}

void rsa_decrypt(unsigned long long int crypted[], 
	unsigned long long int decrypted[], 
	int d, int N, int len){
	for(int i=0; i < len; i++){
		decrypted[i] = mod_pow(crypted[i], d, N);
	}
}

int rsa(char *input){
	unsigned long long int crypted[100];
	unsigned long long int decrypted[100];
	int e = 5;
	int d = 77; // 29
	int N = 221;
    FILE *f=fopen("pass.bin", "rb");

    if(!f){
        f=fopen("pass.bin", "wb");
        rsa_encrypt(input, crypted, e, N);
        printf("Encrypted: ");


        printf("\n");
        
        fwrite(crypted,sizeof(unsigned long long int),strlen(input),f);

        //printf("Decrypted: ");
        fclose(f);
    }

    f=fopen("pass.bin", "rb");

    unsigned long long int ddz[strlen(input)];
    fread(ddz,sizeof(unsigned long long int), strlen(input),f);
	rsa_decrypt(ddz, decrypted, d, N, strlen(input));
    char decr[strlen(input)];
	printf("\n");

	//printf("Decrypted: ");
	//rsa_decrypt(crypted, decrypted, d, N, strlen(input));
	for(int i=0; input[i] != '\0'; i++){
        //printf("%c", (char)decrypted[i]);
		if(input[i] != (char)decrypted[i]){
            return 1;
        }
	}


}