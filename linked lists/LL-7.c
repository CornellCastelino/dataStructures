#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
struct Node{
    char Data;
    Node* next;
};

void add_node(Node** list, char data);
void print_list(Node* list);
void remove_node(Node** list, char data);
void delete_list(Node** list);
void reverse_list(Node** list);

const int SIZE = 50;

int main(){
    
    Node* head = (Node*)malloc( sizeof( Node ) * SIZE  );

    add_node(&head, 'A');
    add_node(&head, 'B');
    add_node(&head, 'C');
    add_node(&head, 'D');

    remove_node(&head,'A');

    reverse_list(&head);

    print_list(head);

    delete_list(&head);

    return 0;
}
//q7
void add_node(Node** list, char data){
    Node* head = (Node*)malloc(sizeof(Node));
    head->Data = data;
    head->next = *list;
    *list = head;
}
//q3
void print_list(Node* list){
    Node* tmp = list;
    while(tmp != NULL){
        printf("%c\n", tmp->Data);
        tmp = tmp->next;
    }
}
//q4
void remove_node(Node** list, char data){
    Node* pre = NULL;
    Node* curr =  *list;
    Node* next;
    while(curr->Data != data && curr != NULL ){
        pre = curr;
        curr = curr->next;
        next = curr->next;
    }
    if(pre == NULL){
        *list = curr->next;
    }
    else if(curr->Data == data){
        pre->next = next;
        free(curr);
    }
}
//q5
void delete_list(Node** list){
    
    Node* tmp = *list;
    tmp = tmp->next;
    free(*list);
    printf("deleted\n");
    delete_list(&tmp);
    
}
//q6
void reverse_list(Node** list){
    int count = 0;

    Node* pre = NULL;
    count++;
    Node* cur = *list;
    count++;
    Node* Next;
    count++;
    while(cur != NULL){
        Next = cur->next;
        count++;
        cur->next = pre;
        count++;
        pre = cur;
        count++;
        cur = Next;
        count++;
    }
    *list = pre;
    count++;
    printf("Time complexity is T(%d)\n",count);
}