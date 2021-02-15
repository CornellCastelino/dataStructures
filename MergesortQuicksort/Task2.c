#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

// Cornell Castelino 18302358

int Swap=0, Comps=0 , SIZE = 10000;
void MergeSort(int *Arr, int low, int high);
void merge(int *Arr, int low, int mid, int high);
int partition(int *Arr, int start, int end);
void swap(int *x, int *y);
void shuffle(int *array, size_t n);  // from https://stackoverflow.com/questions/6127503/shuffle-array-in-c
void ArrayGen(int *Arr, int Size , int testno);



int main(){
    printf("MergeSort:\n\n");
    for(int j = 1; j <= 5; j++){
        Swap=0;
        Comps=0;
        int x[SIZE];
        char sorted = 'Y';
        
        ArrayGen(x,SIZE,j);//1-5


        MergeSort(x,0,SIZE-1);

        for( int i = 0; i < SIZE-1; i++){
            if(x[i] > x[i+1]){
                sorted = 'N';
                break;
            }
        }

        printf("Sorted: %c", sorted);
        
        printf("\n");
        printf("Swaps : %d\n", Swap);
        printf("Comps : %d\n\n",Comps);
    
        // for(int i = 0; i < SIZE; i++){ //ascending sorted
        //     printf("%d,",x[i]);
        // }
        // printf("\n");
    }
    return 0;
}

void MergeSort(int *Arr, int low, int high){
    int q;
    if ( low < high){
        q = floor((low+high)/2);
        MergeSort(Arr, low, q );
        MergeSort(Arr, q + 1,high);

        merge(Arr,low,q,high);
    }
}
void merge(int *Arr, int low, int mid, int high){
    if(high == low){ //best case
        return;
    }

    int a,b,c;

    int m = mid - low + 1;   //100 
    int n = high - mid;

    int A[m], B[n]; // 

    for(int i = 0; i < m;i++){
        A[i] = Arr[i + low];
    }
    for(int i = 0; i < n;i++){
        B[i] = Arr[i + mid + 1];
    }
    
    a = 0;
    b = 0;
    c = low;

    while( a < m && b < n){ // merge 2 arrays
    Comps++;
        if (A[a] <= B[b]){
            // printf("yes %d,%d\n",A[a] , B[b]);
            Arr[c] =  A[a];
            a++; 
            Swap++;
        }
        else{
            // printf("no %d,%d\n",A[a] , B[b]);
            Arr[c] = B[b];
            b++;
            Swap++;
        }
        c++;
    }
    while ( a < m){
        Arr[c] = A[a];
        a++;
        c++;
    }
    while ( b < n){
        Arr[c] = B[b];
        b++;
        c++;
    }
    
}

int partition(int *Arr, int start, int end){
    if (start == end)
        return start;
    int pivot = Arr[end];
    int low = start-1;
    int high = end;
    

    for(int i = 0;i < end - start; i++){
     
        do{
            low++;
            if (low == end) {break;}
            Comps++;
        }while(Arr[low] < pivot);
        do{
            high--;
            if(high == start){break;}
            Comps++;
        }while (Arr[high] > pivot);
       
        if(low>=high){
            swap(&Arr[low], &Arr[end]);

            return low;
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
