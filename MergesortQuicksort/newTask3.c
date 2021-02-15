#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Cornell Castelino 18302358

typedef struct Node Node;
struct Node{
    char title[60],score[3],release_year[5],platform[60];
    Node *next;
};

void MergeSort(Node** list); 
void SplitList(Node* source, Node** front, Node** back); 
void readCSV( FILE *csv, Node **list);
void PrintTable(Node* table, int amt);
Node* MergeSortedList(Node* lst1, Node* lst2) ;
void reverse_list(Node** list);

int main(){
    
    Node *head = NULL;
    FILE *fp = fopen("ign.csv", "r");
    readCSV(fp,&head);
    MergeSort(&head);
    reverse_list(&head);
    printf("test0\n");
    PrintTable(head, 10);
    return 0;
}


void MergeSort(Node** list) 
{ 
	Node* head = *list; 
	Node* ptr1; 
	Node* ptr2; 

  // Base Case
	if ((head == NULL) || (head->next == NULL)) { 
		return; 
	} 

	// Splitting list
	SplitList(head, &ptr1, &ptr2); 

	// Recursively sorting two lists.
	MergeSort(&ptr1); 
	MergeSort(&ptr2); 

	// Sorted List.
	*list = MergeSortedList(ptr1, ptr2); 
} 

void SplitList(Node* source, Node** front, Node** back) 
{ 
	Node* ptr1; 
	Node* ptr2; 
	ptr2 = source; 
	ptr1 = source->next; 

	// ptr1 is incrmented twice and ptr2 is icremented once.
	while (ptr1 != NULL) { 
		ptr1 = ptr1->next; 
		if (ptr1 != NULL) { 
			ptr2 = ptr2->next; 
			ptr1 = ptr1->next; 
		} 
	} 

	// ptr2 is at the midpoint.
	*front = source; 
	*back = ptr2->next; 
	ptr2->next = NULL; 
} 

Node* MergeSortedList(Node* lst1, Node* lst2) 
{ 
	Node* result = NULL; 

	// Base Cases
	if (lst1 == NULL) 
		return (lst2); 
	else if (lst2 == NULL) 
		return (lst1); 

	// recursively merging two lists
	if (atoi(lst1->score) <= atoi(lst2->score)) { 
		result = lst1; 
		result->next = MergeSortedList(lst1->next, lst2); 
	} 
	else { 
		result = lst2; 
		result->next = MergeSortedList(lst1, lst2->next); 
	} 
	return result; 
} 

void readCSV( FILE *csv, Node **list){
    int column, i, quotes = 0;
    char c=' ';
    char buffer[100];
    while(c != EOF){
        Node *head = (Node*)malloc( sizeof(Node));
            column = 0;
        while( column <= 3){
            
            i = 0;
            do{
                c = fgetc(csv);
                if(c == '"' && quotes == 0){
                    quotes = 1;
                }
                else if(c == '"' && quotes == 1) {
                    quotes = 0;
                }
                if ((c == ','   || c == '\n') && quotes == 0) {
                    buffer[i] = '\0';
                    break;   
                }
                // if (c!= '"'){
                    buffer[i] = c;
                    i++;
                // }
            }while(c != EOF); //loop for each word

            switch(column){
                case 0:
                        strcpy(head->title,buffer);
                        break;
                case 1:
                        strcpy(head->platform, buffer);
                        break;
                case 2:
                        strcpy(head->score, buffer);
                        break;
                case 3:
                        strcpy(head->release_year, buffer);
                        break;
            }
            
            if(c == '\n'){break;}  
            column++;

        }          
        head->next = *list;
        *list = head;
        
    }
}
void PrintTable(Node* table, int amt){
    int x = 0;
    Node *tmp = table;
    printf("%-50s|%-25s|%-5s|%-5s\n","Title","Platform","Score","Released Year");
    printf("___________________________________________________________________________________________________\n");
    while(x< amt){
        if ( strcmp(tmp->title , tmp->next->title)){
        printf("%-50s|%-25s|%-5s|%-5s\n", tmp->title,tmp->platform, tmp->score, tmp->release_year);
        }
        else{x = x-1;}
        tmp = tmp->next;
        x++;
    }
   
}
void reverse_list(Node** list){
    Node* pre = NULL;
    Node* cur = *list;    
    Node* Next;
    while(cur != NULL){
        Next = cur->next;   
        cur->next = pre;  
        pre = cur; 
        cur = Next;    
    }
    *list = pre;
}