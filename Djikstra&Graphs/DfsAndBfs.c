#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 10   // amount of elements in the graph
#define col 2

void enqueue(char x,char q[]){
    int i = 0;
    while(q[i]!= ' '){
        i++;
    }
    q[i] = x;
}
char dequeue(char q[]){
    char x = q[0];
    for(int i=0; i < size-1;i++){
        q[i] = q[i+1];
    }
    return x;
}
int isEmpty(char q[]){
    for(int i = 0; i < size;i++){
        if(q[i] != ' '){
            return 0;
        }
    }
    return 1;
}
int isVisited(char input,char v[]){
    for(int i = 0; i < size; i++){
        if(v[i] == input){
            return 1;
        }
    }
    return 0;
}
void BFS(char input, char arr[size][col]){
    char Q[size];
    char visited[size];
    for(int i = 0; i < size; i++){
        Q[i] = ' ';
        visited[i] = ' ';
    }
    enqueue(input,Q);
    enqueue(input,visited);

    while(isEmpty(Q) != 1){

        char v = dequeue(Q);

        for(int i = 0; i < size; i++){
            if(arr[i][0] == v){
                if(isVisited(arr[i][1], visited) == 0){
                    enqueue(arr[i][1],Q);
                    enqueue(arr[i][1],visited);
                }
            }
        }
    }
    printf("BFS: ");
    for(int i = 0; i < size; i++){
        printf("%c ", visited[i]);
    }
    printf("\n");
}
char pop(char q[]){
    char x;
    for(int i = 0; i<size; i++){
        if(q[i] == ' '){
            if(i>0){
                x = q[i-1];
                q[i-1] = ' ';
                return x;
            }
            else{
                printf("invalid usage of pop()\n");
                return 'X';
            }    
        }
    }
}
void DFS(char input, char arr[size][col]){
    char stack[size], visited[size], stack2[size];
    for(int i = 0; i < size; i++){
        stack[i] = ' ';
        stack2[i] = ' ';
        visited[i] = ' ';

    }
    enqueue(input, stack);
    while(isEmpty(stack) == 0){
        char v = pop(stack);
        if( isVisited(v,visited) == 0){    
            enqueue(v,visited);
            for(int i = 0; i < size; i++){
                if(arr[i][0] == v){
                    enqueue(arr[i][1],stack2);
                }
            }while( isEmpty(stack2) != 1){
            enqueue(pop(stack2),stack);
            }
        }
    }
     printf("DFS: ");
    for(int i = 0; i < size; i++){
        printf("%c ", visited[i]);
    }
    printf("\n");

}

int main(){
    char *alphabets = "ABCDEF";
    char graph[size][2]={   {'A','B'},
                            {'A','D'},
                            {'A','E'},
                            {'B','C'},
                            {'B','D'},
                            {'C','B'},
                            {'C','D'},    
                            {'D','F'},
                            {'E','D'},
                            {'F','C'}
                        };
                        printf("Sample output:\n");
    BFS('A',graph);
    DFS('A',graph);
    return 0; 
    
}