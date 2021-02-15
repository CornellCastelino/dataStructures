#include<stdio.h>
#include<math.h>
int arrays[100];
int pos = 0;
void changeint(int arr[],int low, int high){
    if(low<high){
    int x = floor((low + high)/2);
    arrays[pos] = arr[x];
    pos++;
    printf("%d,",arr[x]);
    changeint(arr, low, x);
    changeint( arr, x+1,high);
    }
}


int main(){
    int arr[100];
    for(int i = 0; i<100;i++){
        arr[i] = i;
    }
    changeint(arr,0,100);
    printf("\n");
    for (int i = 0; i < 100; i++){
        printf("%d,",arrays[i]);
    }
    return 0;
}
