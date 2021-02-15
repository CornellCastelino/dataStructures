#include<stdio.h>

int main(){
    int x = 0;
    while(x<10){
        printf("x is %d\n",x);
        while(x>5){
            if(x > 5){
                printf("test");
                break;
                printf("test2");
            }
        }
        x++;
    }

    return 0;
}