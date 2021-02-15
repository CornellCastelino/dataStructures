#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node Node;
struct Node{
    char title[60],score[3],release_year[5],platform[60];
    Node *next;
};

void MergeSort(Node** list); // for  released year
Node* MergeSortedList(Node* lst1, Node* lst2) ;

void ScoreSort(Node **list); // for score
void MergeSort_score(Node** list); // for  released year
Node* MergeSortedList_score(Node* lst1, Node* lst2) ;

void readCSV( FILE *csv, Node **list);
void PrintTable(Node* table, int amt);
void reverse_list(Node** list);
void SplitList(Node* source, Node** front, Node** back); 


int main(){
    
    Node *head = NULL;
    FILE *fp = fopen("ign.csv", "r");
    readCSV(fp,&head);
    MergeSort(&head);
    reverse_list(&head);
    ScoreSort(&head);
    printf("test0\n");
    PrintTable(head, 40);
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
    int x = atoi(lst1->release_year);
    int y =atoi(lst2->release_year);
	// recursively merging two lists
	if (x <= y) { 
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
    while(tmp != NULL){
        while(x< amt){
            if ( strcmp(tmp->title , tmp->next->title)){
            printf("%-50s|%-25s|%-5s|%-5s\n", tmp->title,tmp->platform, tmp->score, tmp->release_year);
            }
            tmp = tmp->next;
            x++;
        }
        tmp = tmp->next;
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
void ScoreSort(Node **list){
    Node *head = *list;
    Node *tmp = head;
    Node *ptr = tmp;
    Node *ptr3 = NULL;
    int count = 0;
    while(tmp != NULL){
       int year = atoi(tmp->release_year);
        
        while(atoi(tmp->release_year) != year -1 ){ // move until the transition of 2016-2015 
            ptr = tmp;
            tmp = tmp->next;
        }
        // printf("%s\n",ptr->release_year);
        ptr->next = NULL;                           // make last ptr  of 2016 element null
        MergeSort_score(&head);                     // sort the list of 2016 elements
                                       
        Node *tmp2 = head, *tmp3;
        
        while(tmp2 != NULL){
            tmp3 = tmp2;
            tmp2 = tmp2->next;
        }
        
        tmp3->next = tmp;
        head = tmp;
        if(ptr3 == NULL){                           //first loop make the head pointer point to the first node
            ptr3 = tmp3;
            *list = head;
        }
        else{
            ptr3->next = head;                      /// make the next 2015,2014... pointer point from last to first element
        }
    }
}
void MergeSort_score(Node** list){
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
	MergeSort_score(&ptr1); 
	MergeSort_score(&ptr2); 

	// Sorted List.
	*list = MergeSortedList_score(ptr1, ptr2); 
    
}
Node* MergeSortedList_score(Node* lst1, Node* lst2){
Node* result = NULL; 

	// Base Cases
	if (lst1 == NULL) 
		return (lst2); 
	else if (lst2 == NULL) 
		return (lst1); 
    
    int x = atoi(lst1->score);
    int y =atoi(lst2->score);
	// recursively merging two lists
	if (x <= y) { 
		result = lst1; 
		result->next = MergeSortedList(lst1->next, lst2); 
	} 
	else { 
		result = lst2; 
		result->next = MergeSortedList(lst1, lst2->next); 
	} 
	return result; 
}