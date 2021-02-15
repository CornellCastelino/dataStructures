#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int test(char *x );
int main(){
    int  x;
    char i[2] = {'"','d'};
    
    x = test(i);
    printf("test %s",i);
    return 0;
}
int test(char *x){
    x[1] = 'f';
    return 0;
}