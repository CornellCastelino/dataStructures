#include<stdio.h>
void swap( int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
void printArray(int arr[], int n){
    int i;
    for (i = 0; i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void selectionSort(int arr[], int n){
    int small;
    int i,j;
    for (i=0; i<n-1; i++){
        small = i;
        for(j=i+1; j<n; j++){
            if (arr[j] <= arr[small]){
                small = j;
            }
        }
        swap(&arr[i],&arr[small]);    
    }
}


int main(){
    int test[] = {12,13,4,2,1};
    int n = 5;
    selectionSort(test,n);
    printf("sorted array: ");
    printArray(test,n);
    return 0;
}