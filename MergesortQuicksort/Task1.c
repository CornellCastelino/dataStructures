#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

// Cornell Castelino 18302358


int Swap=0, Comps=0 , SIZE = 10000;
void QuickSort(int *Arr, int low, int high);
int partition(int *Arr, int start, int end);
void swap(int *x, int *y);
void shuffle(int *array, size_t n);  // from https://stackoverflow.com/questions/6127503/shuffle-array-in-c
void ArrayGen(int *Arr, int Size , int testno);

int main(){
 
    printf("MergeSort:\n\n");
    for(int j = 1; j <= 5; j++){// loop for 5 tests
        Swap=0;
        Comps=0;
        int x[SIZE];
        char sorted = 'Y';
        
        ArrayGen(x,SIZE,j);//1-5

        QuickSort(x,0,SIZE);

        for( int i = 0; i < SIZE-1; i++){ // check for sorted
            if(x[i] > x[i+1]){
                sorted = 'N';
                break;
            }
            
        }

        printf("Sorted: %c", sorted);
        
        printf("\n");
        printf("Swaps : %d\n", Swap);
        printf("Comps : %d\n\n",Comps);
   
    }
    return 0;
}

void QuickSort(int *Arr, int low, int high){
    int r;
    if ( low < high){
        r = partition(Arr, low, high);
      
        QuickSort(Arr, low, r );
        QuickSort(Arr, r + 1,high);
    }
}
int partition(int *Arr, int start, int end){
    if (start == end)   //best case
        return start;
    int x = (start + end)/2;
    int pivot = Arr[x];
    int low = start-1;
    int high = end+1;

    
    for(;;){
        do{
            low++;
            Comps++;
        }
        while(Arr[low] < pivot);
        
        do{
            high--;
            Comps++;
        }while(Arr[high]>pivot);
        // printf("%d,%d\n",high,low);
        if(low >= high){
            Comps++;
            return high;
        }
        swap(&Arr[low], &Arr[high]);
    }

}
void swap(int *x, int *y){
    Swap++;
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
void shuffle(int *arr, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}
void ArrayGen(int *Arr, int Size , int testno){
    if(testno == 1){
        for(int i = 0; i < Size; i++){ //  array with no duplicates
            Arr[i] = i;
        }
        printf("Test  : random no duplicates\n");
        shuffle(Arr,Size);
    }
    else if(testno == 2){
        srand(time(NULL));
        for(int i = 0; i < Size; i++){    // array with duplicates
            Arr[i] = rand()%Size;
        }
        printf("Test  : random with duplicates\n");
    }

    else if(testno == 3){
        for(int i = 0; i < Size; i++){ //ascending sorted
            Arr[i] = i;
        }
        printf("Test  : Ascending sorted\n");
    }
    else if(testno == 4){
        for(int i = Size; i > 0; i--){ //descending sorted
            Arr[i] = i;
        }
        printf("Test  : Descending sorted\n");
    }
    else if(testno == 5){
        for(int i = 0; i < Size; i++){ //uniform
            Arr[i] = 0;
        }
        printf("Test  : Uniform\n");
    }
    else{
        printf("Invalid test number.\n");
    }
}
