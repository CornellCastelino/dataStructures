#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define SIZE 10000
int newcounter = 0;

typedef struct AdjList AdjList; // adjacency list 
struct AdjList{
    int adjV; //vertex
    int w;  //weight
    AdjList *next;
};

typedef struct graph graph;
struct graph{
    int v;//num of vertices
    AdjList **array;//array of adjlist
};
graph *CreateGraph(int v){
    graph *g = (graph*)malloc(sizeof(graph));   
    g->v =v;
    g->array = malloc(sizeof(AdjList) * v);
    
    //initial each adj list as null
    for(int i=0;i<v;i++){
        g->array[i] =NULL;
    }
    
    return g;
}
AdjList *createNode(int ID,int w){
    AdjList *node = malloc(sizeof(AdjList));
    node->adjV = ID;
    node->w = w;
    node->next =  NULL;
    newcounter++;
    return node;
}

int readNum(FILE *fp, char *buffer){// parser 
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
void readEdges(FILE *fp,graph** g ){
    char buffer[10];

    int vert1,vert2,w,check;
    check = readNum(fp,buffer);// removes the first line
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
        // printf("..test, %d,%d,%d..",vert1,vert2,w);
        AdjList *node = createNode(vert2,w); // for an undirected graph
        if((*g)->array[vert1] != NULL){
            node->next = (*g)->array[vert1];
            (*g)->array[vert1] = node;
        }
        else
            (*g)->array[vert1] = node;
        node = createNode(vert1,w);
        if((*g)->array[vert2] != NULL){
            node->next = (*g)->array[vert2];
            (*g)->array[vert2] = node;
        }
        else
            (*g)->array[vert2] = node;
    }
}
void readVertices(FILE *fp,graph** g ){ // this will read vertices

}
int minDistance(int *d, int *s, int v)// distance,shortest pth and num of vertice 
{
    int minpos, min;
    min = INT_MAX;
    minpos = -1;
    for(int i=0;i<v;i++){
        // printf("test");
        if(d[i]<min&&!s[i]){
            
            min=d[i];
            minpos=i;
        }
    }
    return minpos;
}
void Dijkstra(int v, int *d, int *path, graph *G ){
    printf("test ");
    
    AdjList *p;
    p = G->array[v];
    int *s;

    if(v<0 || v>(G->v - 1)){
        printf("error, Invalid graph\n");
        return;
    }

    s = (int*)malloc(sizeof(int)*G->v);
    for(int i=0;i<G->v;i++){
        s[i] = 0;
        path[i] = -1;
        d[i] = INT_MAX;
    }

    while(p){
        d[p->adjV]=p->w;
        
        if(p->adjV!=v && d[p->adjV]<INT_MAX){
            path[p->adjV]=v;
        }
        p=p->next;
        printf("test ... %d",p->w);
    }
    printf("test\n");
    s[v] = 1;
    d[v] = 0;
    for(int i=0;i<G->v;i++){
        int k = minDistance(d,s,G->v);
        printf("test,%d  ,",k);
        if(k == -1){
            continue;
        }
        s[k] = 1;
       
        if(G->array[k]==NULL){
            
            continue;
        }
         p=G->array[k];
        while(p){
            if(!s[p->adjV] && d[k]+p->w < d[p->adjV]){
                d[p->adjV]= d[k]+p->w;
                path[p->adjV] = k;
            }
            p=p->next;
        }
    }
}
void printDjikstra(graph *G){
    int x,y;
    printf("input source and dest:\n");
    scanf("%d %d",&x,&y);
    int d[SIZE];// taking from the file
    int path[SIZE];
    Dijkstra(x,d,path,G);
    
    // for (int i = 0; i < G->v; i++)
    // {
    //     //     printf("test");
    //     // printf("Test path-> %d\n",G->array[i]->adjV);
    // }
    

    printf("path: ");
    if(path[x] == -1){
        printf("None\n");
        return;
    }
    while(path[x] !=1){
        printf("%d <-- ",x);
        x = path[x];
    }
    printf("%d\n",y);
}

int main(){

    graph *head;
    FILE *fp = fopen("edges.csv","r");
    int v = 10000; //edges
    printf("%d",v);
    
    head = CreateGraph(v);// creates a graph with 10000 adj list since counting the list and the Id in the list is different
    
    readEdges(fp,&head); // reads and updates the head ptr.
    printf("Loaded edges..\n");
    printf("%d...\n",newcounter); // counter to check how many times adjlist is created
    
    printDjikstra(head); //prints djikstra shortest path
    return 0; 
    
}