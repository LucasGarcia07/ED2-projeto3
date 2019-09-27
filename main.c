#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"pessoa.h"
#define m 10000
int main(){
    int *endereco, *colisao, end = 0, coli = 0, num;
    double carga, *n, inseridos = 0.0;
    endereco = &end;
    colisao = &coli;
    *colisao = 0;
    n = &inseridos;
    criaTabelaHash(m);
    FILE* tabelaP;
    tabelaP = fopen("pessoa.dat", "r+b");
    srand(time(NULL));

    while(fatorCarga(n, m) < 0.9){
        num = rand()* 7 % 99999;
        insere2(num, m, tabelaP, endereco, criaPessoa(num, "w/e"), colisao, n);
    }
    
    int coli1 = *colisao;
    
    clock_t Ticks[2];
    Ticks[0] = clock();
    
    insere2(7000, m, tabelaP, endereco, criaPessoa(7000, "lucas"), colisao, n);
    int coli2 = *colisao - coli1;
    remove2(7000, m, tabelaP, endereco, colisao, n);
    int coli3 = *colisao - coli1 - coli2;

    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("\nTempo gasto: %g ms\n.", Tempo);
    
    carga = *n/m;
    printf("Fator de carga: %lf\n", carga);
    printf("Número de colisões: %d\n", coli1);
    printf("Número de colisões por inserção: %d\n", coli2);
    printf("Número de colisões por remoção: %d\n", coli3);
    fseek(tabelaP,0, SEEK_SET);

    return 0;
}