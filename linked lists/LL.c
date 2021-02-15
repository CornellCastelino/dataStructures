#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
struct Node{
    char Data;
    Node* next;
};

void add_node(Node** list, char data);

int main(){
    
    Node* head = (Node*)malloc( sizeof( Node ) );
    head->Data = 'a';
    head->next = NULL;
    add_node(&head,'s');

    Node* tmp = head;
    while(tmp != NULL){
        printf("%c\n", tmp->Data);
        tmp = tmp->next;
    }

    return 0;
}

void add_node(Node** list, char data){
    Node* head = (Node*)malloc( sizeof( Node ) );
    head->Data = data;
    head->next = *list;
    *list = head;
}