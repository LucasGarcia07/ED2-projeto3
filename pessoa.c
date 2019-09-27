#include "pessoa.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

void imprime(Pessoa *func) {
    printf("\nPessoa de código ");
    printf("%d", func->chave);
    printf("\nNome: ");
    printf("%s", func->nome);
}

Pessoa *criaPessoa(int chave, char *nome) {
    Pessoa *func = (Pessoa *) malloc(sizeof(Pessoa));

    if (func) memset(func, 0, sizeof(Pessoa));

    func->chave = chave;
    strcpy(func->nome, nome);
    return func;
}

void salva(Pessoa *func, FILE *out) {
    fwrite(&func->chave, sizeof(int), 1, out);
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
}

Pessoa *le(FILE *in) {
    Pessoa *func = (Pessoa *) malloc(sizeof(Pessoa));
    if (0 >= fread(&func->chave, sizeof(int), 1, in)) {
	free(func);
	return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    return func;
}

int tamanho() {
    return sizeof(int) + sizeof(char) * 50;
}

double fatorCarga(double *n, int m){
    return *n/m;
}


int buscaAberto1(int chave, int m, FILE *in, int *endereco, int *colisao){
    int a = 3, k = 0;
    Pessoa *p;
    rewind(in);
    while(k < m){
        *endereco = hash1(chave, k, m);
        fseek(in, (*endereco) * tamanho(), SEEK_SET);
        p = le(in);
        fseek(in, (*endereco) * tamanho(), SEEK_SET);
        if(p->chave == chave){
            a = 1;
            k = m;
        }else if(p->chave == -1){
            a = 2;
            k = m;
        }else{
            k++;
            *colisao+= 1;
        }
    }
    return a;
}

int buscaAberto2(int chave, int m, FILE *in, int *endereco, int *colisao){
    int a = 3, k = 0;
    Pessoa *p;
    rewind(in);
    while(k < m){
        *endereco = hash2(chave, k, m);
        fseek(in, (*endereco) * tamanho(), SEEK_SET);
        p = le(in);
        fseek(in, (*endereco) * tamanho(), SEEK_SET);
        if(p->chave == chave){
            a = 1;
            k = m;
        }else if(p->chave == -1){
            a = 2;
            k = m;
        }else{
            k++;
            *colisao+=1;
        }
    }
    return a;
}

int buscaAberto3(int chave, int m, FILE* in, int *endereco, int *colisao){
    int a = 3, k = 0;
    Pessoa *p;
    rewind(in);
    while(k < m){
        *endereco = hash3(chave, k, m);
        fseek(in, (*endereco) * tamanho(), SEEK_SET);
        p = le(in);
        fseek(in, (*endereco) * tamanho(), SEEK_SET);
        if(p->chave == chave){
            a = 1;
            k = m;
        }else if(p->chave == -1){
            a = 2;
            k = m;
        }else{
            k++;
            *colisao+=1;
        }
    }
    return a;
}

int hash1(int chave, int k, int m){
    return ((chave % 43) + k) % m; 
}

int hash2(int chave, int k, int m){
    return ((chave % 43) + 3*k+2*k*k)% m;
}

int hash3(int chave, int k, int m){
    return ((chave %43) + (chave % 37) * k) % m;
}

void insere1(int chave, int m, FILE *in, int *endereco, Pessoa *p, int *colisao, double *n){
    int a = buscaAberto1(chave, m, in, endereco,colisao);
    if(a == 2){
        *n+=1;
        
        salva(p, in);
    }
}

void insere2(int chave, int m, FILE* in, int *endereco, Pessoa *p,  int *colisao, double *n){
    int a = buscaAberto2(chave, m, in, endereco, colisao);
    if(a == 2){
        *n+=1;
        salva(p, in);
    }
}

void insere3(int chave, int m, FILE* in, int *endereco, Pessoa *p,  int *colisao, double *n){
    int a = buscaAberto3(chave, m, in, endereco, colisao);
    if(a == 2){
        *n+=1;
        salva(p, in);
    }
}

void remove1(int chave, int m, FILE* in, int *endereco, int *colisao, double *n){
    
    Pessoa *p;
    int a = buscaAberto1(chave, m, in, endereco, colisao);
    p = le(in);
    printf("\nchave: %d", p->chave);
    printf("\nnome: %s\n", p->nome);
    if(a == 2){
        printf("\npessoa não está na tabela\n");
    }else{
        fseek(in, (*endereco) * tamanho(), SEEK_SET);
        salva(criaPessoa(-1, "vazio"), in);
        *n-=1;
    }
}

void remove2(int chave, int m, FILE* in, int *endereco,  int *colisao, double *n){
    Pessoa *p;
    int a = buscaAberto2(chave, m, in, endereco, colisao);
    p = le(in);
    if(a == 2){
        printf("\npessoa não está na tabela\n");
    }else{
        printf("\nchave: %d", p->chave);
        printf("\nnome: %s", p->nome);
        fseek(in, (*endereco) * tamanho(), SEEK_SET);
        salva(criaPessoa(-1, "vazio"), in);
        *n-=1;
    }
}

void remove3(int chave, int m, FILE* in, int *endereco,  int *colisao, double *n){
    Pessoa *p;
    int a = buscaAberto3(chave, m, in, endereco,colisao);
    p = le(in);
    if(a == 2){
        printf("\npessoa não está na tabela\n");
    }else{
        printf("\nchave: %d", p->chave);
        printf("\nnome: %s", p->nome);
        fseek(in, (*endereco) * tamanho(), SEEK_SET);
        salva(criaPessoa(-1, "vazio"), in);
        *n-=1;
    }
}   

void criaTabelaHash(int tam){
    FILE *in;
    in = fopen("pessoa.dat", "wb");
    for(int i = 0; i < tam; i++){
        salva(criaPessoa(-1, "vazio"), in);
    }
    fclose(in);
}