#ifndef PESSOA_H
#define PESSOA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Pessoa {
    int chave;
    char nome[50];

} Pessoa;

void imprime(Pessoa *func);

Pessoa *criaPessoa(int chave, char *nome);

void salva(Pessoa *func, FILE *out);

Pessoa *le(FILE *in);

int tamanho();

void criaTabelaHash(int tam);

double fatorCarga(double *n, int m);

int buscaAberto1(int chave, int m, FILE *in, int *endereco,  int *colisao);

int buscaAberto2(int chave, int m, FILE *in, int *endereco,  int *colisao);

int buscaAberto3(int chave, int m, FILE* in, int *endereco,  int *colisao);

int hash1(int chave, int k, int m);

int hash2(int chave, int k, int m);

int hash3(int chave, int k, int m);

void insere1(int chave, int m, FILE* in, int *endereco, Pessoa *p,  int *colisao, double *n);

void insere2(int chave, int m, FILE* in, int *endereco, Pessoa *p,  int *colisao, double *n);

void insere3(int chave, int m, FILE* in, int *endereco, Pessoa *p,  int *colisao, double *n);

void remove1(int chave, int m, FILE* in, int *endereco,  int *colisao, double *n);

void remove2(int chave, int m, FILE* in, int *endereco,  int *colisao, double *n);

void remove3(int chave, int m, FILE* in, int *endereco,  int *colisao, double *n);

#endif