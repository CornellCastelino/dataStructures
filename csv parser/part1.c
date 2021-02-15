#include<stdio.h>
// Cornell Castelino 18302358
int main(){
    char name[100];
    int age = 0;

    printf("Enter Name: ");
    scanf("%s",name);
    printf("Enter Age: ");
    scanf("%d",&age);
    printf("Hello %s (%d) ",name,age);

    return 0;
}