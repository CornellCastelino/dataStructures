#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define size 7   // amount of elements in the graph
#define col 2

int indexofChar(char arr[], char x){
    for(int i = 0; i < size;i++){
        if(x == arr[i]){
            return i;
        }

    }
}
int minDistance(int dist[],int sptSet[]){
    int min = INT_MAX;
    int minIndex;
    for(int i = 0; i<size; i++){
        if(sptSet[i] == 0 && dist[i]<min){
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}
void Dijkstra(int  src, int edge[size][size], char vertice[]){
    int dist[size] = {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX };
    int sptSet[size] = {0,0,0,0,0,0,0};
    int order[size] = {0,0,0,0,0,0,0};
    dist[src] = 0;

    for(int i = 0; i < size; i++){
        int u = minDistance(dist,sptSet);
        sptSet[u] = 1;
        order[i] = u;
        for(int j = 0; j <size; j++){
                if((sptSet[j] == 0) ){
                    if(edge[u][j] != 0){
                        if (dist[u] != INT_MAX) {
                            if (dist[u]+edge[u][j] < dist[j])
                                dist[j] = dist[u] + edge[u][j];
                        }
                    }
                }
        }
    }

    
    printf("shortest distance from A to all other nodes:\n");
    printf("%-20s %-30s\n","vertice","Distance from source");
    for(int i = 0; i < size; i++){
        printf("%-20c %-30d\n",vertice[i],dist[i]);
    }
    printf("\n");
    printf("Order of nodes made permanent: ");
    for(int i = 0; i<size;i++){
        printf("%c ",vertice[order[i]]);
    }

}
int main(){
    char *alphabets = "ABCDEF";
    char vertice[] = {'A','B','C','D','E','F','G'};
    int graph[size][size]={{0,1,3,0,0,10,0},
                            {1,0,1,7,5,0,2 },
                            {3,1,0,9,3,0,0 },
                            {0,7,9,0,2,1,12},
                            {0,5,3,2,0,2,0 },
                            {10,0,0,1,2,0,0},
                            {0,2,0,12,0,0,0}
                           };
    Dijkstra( indexofChar(vertice,'A'),graph, vertice);
    return 0; 
    
}