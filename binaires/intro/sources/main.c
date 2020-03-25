#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

typedef struct {
    char infos[50];
    uint8_t cle[16];
}process;

void win() {
    printf("Cette fonction ne devrait pas s'exécuter...\n");
}

void hexdump(void *ptr, int buflen) {
    unsigned char *buf = (unsigned char*)ptr;
    int i, j;
    for (i=0; i<buflen; i+=16) {
        printf("%06x: ", i);
        for (j=0; j<16; j++) 
            if (i+j < buflen)
                printf("%02x ", buf[i+j]);
            else
                printf("   ");
        printf(" ");
        for (j=0; j<16; j++) 
            if (i+j < buflen)
                printf("%c", isprint(buf[i+j]) ? buf[i+j] : '.');
        printf("\n");
    }
}


void afficherInfos(int max, process* s) {
    for (int i = 0; i < max; ++i) {
        printf("Itération %d\n----------\n", i);
        hexdump(s[i].infos, 50*sizeof(char));
        printf("\n");
    }
}


// teacrypt
void encrypt (uint32_t* v, uint32_t* k) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;
    uint32_t delta=0x9e3779b9;
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3]; 
    for (i=0; i < 32; i++) {
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                        
    v[0]=v0; v[1]=v1;
}

int showWrite(char* a, char* b) {
    volatile int w = 32;
    char buffer[50];

    printf("Ecrivez %s: ", a);
    gets(buffer);
    memcpy(b, buffer, sizeof(buffer));

    if(w!=32) {
        win();
    }
    return 0;
}

int main() {
    int max = 5;
    process s[10];

    for (int i = 0; i < max; ++i) {
        memset(s[i].infos, 0, sizeof(s[i].infos));
        memset(s[i].cle, 0, sizeof(s[i].cle));
        printf("Itération %d\n----------\n", i);
        showWrite("a", s[i].infos);
        showWrite("b", s[i].cle);
        for(int y=0; y<50; y+=4) {
            encrypt((uint32_t*)(s[i].infos+y), (uint32_t*)s[i].cle);
        }
        printf("\n");
    }
    printf("Résultats:\n\n");

    afficherInfos(max, s);
    
    return 0;
}
