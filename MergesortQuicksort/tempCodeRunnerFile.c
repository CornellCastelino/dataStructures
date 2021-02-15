#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.


void calculate_the_maximum(int n, int k) {
    //Write your code here.
    int max[3] = {0,0,0};
    for(int i = 1; i <= n-1; i++){
        for(int j = 2; j <=n-1; j++){
            if((i & j) > max[0]&&(i & j) < k)
                max[0] = i & i+1;
            if((i | j) > max[1]&&(i | j) < k)
                max[1] = i | i+1;
            if((i ^ j) > max[2]&&(i ^ j) < k)
                max[2] = i ^ i+1;
        }
    }
    printf("%d\n%d\n%d\n",max[0],max[1],max[2]);
}

int main() {
    int n, k;
  
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
 
    return 0;
}
