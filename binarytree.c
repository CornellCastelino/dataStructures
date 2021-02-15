#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

typedef struct Tree_Node Tree_Node;
struct Tree_Node{
    char data;
    int checked;
    Tree_Node *left;
    Tree_Node *right;
};

void tree_insert ( Tree_Node** root, char data );           //insert one char 
Tree_Node* tree_search ( Tree_Node* root, char data );      // search and check if the char is present
void tree_print_sorted ( Tree_Node* root );                 // print the entire tree sorted
void tree_delete ( Tree_Node* root );            // delete

void QuickSort(char *Arr, int low, int high);
int partition(char *Arr, int start, int end);

Tree_Node* newNode(char data);

int main(){
    char input[] = "FLOCCINAUCINIHILIPILIFICATTION";
    char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    Tree_Node *head = NULL;

    for(int i =0; i <= sizeof(input)-2; i++){ // inserting input
        tree_insert(&head,input[i]);
    }
    // //printing sorted
    tree_print_sorted(head);
    printf("\n");

    //SEARCH
    Tree_Node *tmp;
    char chr = 'c';
    int loop = 0; 
    
    srand(time(NULL));
    while(loop<2){
        
        chr =alphabets[rand()%(sizeof(alphabets)-2)];
        tmp = tree_search(head,chr);
        if(tmp==NULL){
            printf("%c not in tree \n",chr);
        }
        else    { 
            printf("%c is in tree\n",chr);
        }
        loop++;
    }

    tree_delete(head);
    
    printf("deleted\n");
    tree_print_sorted(head);
    return 0;
}
void tree_insert ( Tree_Node** root, char data ){
   
    if (*root == NULL){
        *root = (Tree_Node*)malloc(sizeof(Tree_Node));
        (*root)->data = data;
        (*root)->checked = 0;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if ( data < (*root)->data)
    {
        tree_insert(&(*root)->left, data);
    }
    else if (data >= (*root)->data)
    {
        tree_insert(&(*root)->right, data);
    }
    
}
void tree_delete ( Tree_Node* root ){

    tree_delete (root->left);
    tree_delete (root->right);
    free(root);

}

Tree_Node* tree_search ( Tree_Node* root, char data ){

    if( root){
		if( data == root->data){
			return root;
		}
		else if( data < root->data){
			return tree_search(root->left,data);
		}
		else{
			return tree_search(root->right,data);
		}
	}
	else return NULL;
}

void tree_print_sorted ( Tree_Node* root ){
   if(root==NULL)
           return;
    tree_print_sorted(root->left);
    printf("%c", root->data);
    tree_print_sorted(root->right);
 }

void QuickSort(char *Arr, int low, int high){
    int r;
    if ( low < high){
        r = partition(Arr, low, high);
       
        QuickSort(Arr, low, r );
        QuickSort(Arr, r + 1,high);
    } 
}
int partition(char *Arr, int start, int end){
  
    if (start == end)   //best case
        return start;
    int x = (start + end)/2;
    char pivot = Arr[x];
    int low = start-1;
    int high = end+1;

    for(;;){
        
        do{
            low++;   
        }
        while(Arr[low] < pivot);
        
        do{
            high--;   
        }while(Arr[high]>pivot);

        if(low >= high){    
            return high;
        }
        char tmp = Arr[low];
        Arr[low] = Arr[high];
        Arr[high] = tmp;     
    }
}
Tree_Node* newNode(char data) 
{ 
Tree_Node* node = (Tree_Node*)malloc(sizeof(Tree_Node)); 
node->data = data;  
node->checked = 0;
node->left = NULL; 
node->right = NULL; 
return(node); 
} 
