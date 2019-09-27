#include<stdio.h>



int main(){
    int *a, b = 0;

    a = &b;

    *a = 10;

    float c = 3.0/2;
    printf("%f", c);


    return 0;
}