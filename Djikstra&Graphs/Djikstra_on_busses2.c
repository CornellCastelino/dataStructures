#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int newcounter = 0;

typedef struct AdjListnode AdjListnode; // adjacency list 
struct AdjListnode{
    int adjV; //vertex
    int w;  //weight
    AdjListnode *next;
};
typedef struct AdjList AdjList;
struct AdjList{
    AdjListnode *head;
};
typedef struct graph graph;
struct graph{
    int v;//num of vertices
    AdjList *array;//array of adjlist
};
int countVerticefile(FILE *fp){
    char c;
    int count=-1;
    while(c != EOF){
        c = fgetc(fp);
        if(c == '\n')
            count++;
    }
    return count;
}

int readNum(FILE *fp, char *buffer){
    char c;
    int i = 0, quotes = 0;
    do{
        c = fgetc(fp);
        if(c == '"'){
            if (quotes == 1){quotes = 0;}
            else{quotes = 1;}
        }
        if ((c == ',' && quotes == 0 ) || c == '\n') {
            buffer[i] = '\0';
            return 0;
        }
        if (c!= '"'){
            buffer[i] = c;
            i++;
        }
    }while(c != EOF);
    return 1;
}

AdjListnode *createNode(int ID,int w){
    AdjListnode *node = (AdjListnode*)malloc(sizeof(AdjListnode));
    node->adjV = ID;
    node->w = w;
    node->next =  NULL;
    newcounter++;
    return node;
}
graph *CreateGraph(int v){
    graph *g = (graph*)malloc(sizeof(graph));   
    g->v =v;
    g->array = malloc(sizeof(AdjList) * v);
    
    //initial each adj list as null
    for(int i=0;i<v;i++){
        g->array[i].head =NULL;
    }
    
    return g;
}
void readEdges(FILE *fp,graph* g ){
    char buffer[10];

    int vert1,vert2,w,check;
    check = readNum(fp,buffer);
    check = readNum(fp,buffer);
    check = readNum(fp,buffer);
    while(1){

        check = readNum(fp,buffer);
        
        if(check ==1){break;}
        vert1 = atoi(buffer);
        
        check = readNum(fp,buffer);
        if(check ==1){
            printf("edge input error\n");
            break;
            }
        vert2 = atoi(buffer);
        check = readNum(fp,buffer);
        if(check ==1){
            printf("edge input errorss\n");
            break;
            }
        w = atoi(buffer);
        // printf("test->%d,%d,%d..\n", vert1,vert2,w);    
        AdjListnode *node = createNode(vert2,w);
        
        node->next = g->array[vert1].head;
        g->array[vert1].head = node;
        // printf("test2->%d,%d,%d..\n", vert1,vert2,w);    
        //undirected graph
        node = createNode(vert1,w);
             
        node->next = g->array[vert2].head;
        // printf("test3->%d,%d,%d..\n", vert1,vert2,w);
        g->array[vert2].head = node;
       
    }
}

typedef struct MinHeapNode MinHeapNode;
struct MinHeapNode{
    int v;
    int dist;
};
typedef struct MinHeap MinHeap;
struct MinHeap{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **array;
};
MinHeapNode* newMinHeapNode(int v, int dist)
                                 
{
    printf("test3, %d, %d\n",v,dist);
    MinHeapNode* minHeap =(MinHeapNode*)malloc(sizeof(MinHeapNode));
    
    minHeap->v = v;
    minHeap->dist = dist;
    
    return minHeap;
}
MinHeap * createMinHeap(int capacity){
    MinHeap *minheap = (MinHeap*)malloc(sizeof(MinHeap));
    minheap->pos = (int*)malloc(sizeof(int));
    minheap->size = 0;
    minheap->capacity = capacity;
    minheap->array = (MinHeapNode**)malloc(sizeof(MinHeapNode)*capacity);
    return minheap;
}

//swap nodes
void swapMinHeapNode(MinHeapNode **x, MinHeapNode **y){
    MinHeapNode *tmp = *x;
    *x = *y;
    *y = tmp;
}

//heapify at given index
void minHeapify(MinHeap *minHeap, int index){
    int small,L,R;
    small = index;
    L = 2 * index +1;
    R = 2* index + 2;

    if(L < minHeap->size && minHeap->array[L]->dist < minHeap->array[small]->dist)
    {
        small = L;
    }
    if(R < minHeap->size && minHeap->array[R]->dist < minHeap->array[small]->dist)
    {
        small = R;
    }
    if(small != index){

        // to swap
        MinHeapNode *smallNode = minHeap->array[small];
        MinHeapNode *indexNode = minHeap->array[index];

        //swap
        minHeap->pos[smallNode->v] = index;
        minHeap->pos[indexNode->v] = small;

        //swap node
        swapMinHeapNode(&minHeap->array[small],&minHeap->array[index]);

        minHeapify(minHeap, small);

    }
}

//check is heap is empty
int isEmpty(MinHeap *minHeap){
    return minHeap->size == 0;
}

MinHeapNode *extractmin(MinHeap *minHeap){
    if(isEmpty(minHeap))
        return NULL;
    //store root
    MinHeapNode* root = minHeap->array[0];

    //replace
    MinHeapNode *last = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = last;

    //update position
    minHeap->pos[root->v] = minHeap->size -1;
    minHeap->pos[last->v] = 0;

    //reduce heap size and root
    minHeap->size = minHeap->size -1;

    minHeapify(minHeap,0);
    return root;
}


void decreaseKey(MinHeap *minHeap, int v, int dist){
    //index of v
    int i = minHeap->pos[v];

    //get node and update
    minHeap->array[i]->dist = dist;

    while(i && minHeap->array[i]->dist < minHeap->array[(i-1)/2]->dist){
        //swap node with parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        swapMinHeapNode(&minHeap->array[i],&minHeap->array[(i-1)/2]);

        i = (i-1)/2;
    }
}
//check if the vertex is present or not
int isInMinHeap(MinHeap *minHeap, int v){
    if(minHeap->pos[v] < minHeap->size){
        return 1;
    }
    return 0;
}

void printArr(int dist[], int n){
    printf("Vertex      Distance from Source\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }
    
}

void Dijkstra(int src, graph *g ){

    //num of vertices
    int v = g->v;
    //dist with minium value to dest
    int dist[10000];

    MinHeap *minHeap = createMinHeap(v);
    
    //initialise minheap
    for(int i = 0; i < v; i++)
    {
        dist[i] = INT_MAX;
        minHeap->array[i] = newMinHeapNode(i,dist[i]);
        
        minHeap->pos[i] = i;
    }
    
    //dist value to src vertex as 0
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap,src,dist[src]);

    minHeap->size = v;
    
    while(isEmpty(minHeap) == 0){

        MinHeapNode *minHeapNode = extractmin(minHeap);

        int u = minHeapNode->v;

        AdjListnode *crawl = g->array[u].head;
        while(crawl != NULL){
            int V = crawl->adjV;

            if(isInMinHeap(minHeap,V) &&  dist[u] != INT_MAX && crawl->w + dist[u] < dist[V]){
                dist[V] = dist[u] + crawl->w;

                decreaseKey(minHeap, V,dist[V]);
            }
            crawl = crawl->next;
        }

    }
    
    printArr(dist,v);
   
}


int main(){

    graph *head;
    FILE *fp = fopen("edges.csv","r");
    int v = 10000; //edges
    printf("%d",v);
    
    head = CreateGraph(v);
    
    readEdges(fp,head);
    printf("test2");
    printf("\ntest %d ",head->v);
    Dijkstra(0,head);
    printf("%d...\n",newcounter);
   
    return 0; 
    
}