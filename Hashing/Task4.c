#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int const ARRAY_SIZE = 100000, MAX_STRING_SIZE = 20 ;

typedef struct Node Node;
struct Node{
    char Person_ID[20],Deposition_ID[20],Surname[30],Forename[100],Age[3],Person_Type[20],Gender[20],Nationality[20],Religion[20],Occupation[20];
    Node* next;
};

typedef struct hashTable hashTable;
struct hashTable{
    char key[20];
    Node* list;
};

int hash2(char* s);
int hash3(int hash, int i);
void readCSV(FILE *csv , Node** link );
void delete_list(Node** list);
void PrintTable(Node* table);

hashTable table[100000]; // outside declaration since declaring high capacity array in the main file crashes while running  ¯\_(ツ)_/¯

int main(){
    //declarations
    FILE *fp = fopen("people.csv","r");
    char string[20];
    int endFile, Capacity = ARRAY_SIZE, Num_Terms = 0, Collision = 0;
    double load = 0;
   
    Node* head = NULL;

    //initiation of hashtable
    for(int i = 0; i < ARRAY_SIZE; i++){
        strcpy(table[i].key, "x");
    }
    
    readCSV(fp,&head);           // reads and creates the linked lists for all inputs
    
    // hashing the list and using the linked list as values
    Node* tmp = head;
    while (tmp != NULL){
        // printf("test");
        int Hash = hash2(tmp->Surname);
        int scanned = Hash;
        int hashed = 0, linearProb = 0;
        while(hashed == 0){
            if(strcmp(table[Hash].key,"x") == 0 ){
                strcpy(table[Hash].key,tmp->Surname);
                table[Hash].list = tmp;                 // each hash key has a pointer to its Node in the linked list for efficiency
                Num_Terms++;
                hashed = 1;
            }
            else{
                 linearProb++;
                 Collision++;
                 Hash = hash3(Hash, linearProb);   
                 if (scanned == Hash){break;} // checks if it new hash is the same as initial hash value for the given string
            }
        }
        tmp = tmp->next;
    }

    load = (double)Num_Terms/(double)Capacity;
    
    //print
    //PrintTable(Hash_table);
    printf("Capacity\t: %d\n",Capacity);
    printf("Num Terms\t: %d", Num_Terms);
    printf("\nCollisions\t: %d\n", Collision);
    printf("Load\t:  %0.2f%% \n", load);


    //search
    int exit = 0;
    char temp;
    tmp = NULL;
    int repeatCheck[ARRAY_SIZE];
    for (int i=0;i<ARRAY_SIZE;i++){repeatCheck[i] = 0;}

    printf("enter term to get the frequency or type 'quit' to exit: ");
    scanf("%[^\n]", string);
    scanf("%c", &temp);
    if (strcmp(string, "quit") == 0){ exit = 1;}

    while(exit == 0){

        int Hash = hash2(&string[0]), linearProb = 0, first = 0, repeated = 0;
        char x[10];
        
        while(linearProb <= Num_Terms){
            
            for (int i = 0; i < ARRAY_SIZE; i ++){
                if (repeatCheck[Hash] != 0){
                    repeated = 1;
                    break;
                }
            }
            if(strcmp(table[Hash].key,string) == 0 && repeated == 0){
                if(first == 0){
                    printf("Person ID | Deposition ID | Surname    | Forename  \t\t\t\t       | Age | Person Type | Gender   | Nationality | Religion\t       | Occupation\n");
                    first++;
                }
                tmp = table[Hash].list;
                PrintTable(tmp);
                strcpy(x , tmp->Person_ID);
                repeatCheck[atoi(x)] = 1;
            }

            // printf("%d\n", linearProb);
            linearProb++;
            Hash = hash3(Hash,linearProb);
            
        }
        
        if(linearProb > Collision/2 && first == 0){
            printf("Not found\n");
        }
            printf("\nEnter another one:");
            scanf("%[^\n]", string);
            scanf("%c", &temp);
        if (strcmp(string, "quit") == 0){
            exit = 1;
            break;
        }   


    }
    delete_list(&head);
    return 0;
}
int hash2(char* s){   
    int hash2 = 0;
    while(*s){
    hash2 = ( hash2 + *s );
    s++;
    }
    return (hash2)%ARRAY_SIZE;
}

int hash3(int hash, int i){
    return (hash+i)%ARRAY_SIZE;
}

// void add_node(Node** list, char data){
//     Node* head = (Node*)malloc( sizeof( Node ) );
//     head->Data = data;
//     head->next = *list;
//     *list = head;
// }

void delete_list(Node** list){
    
    Node* tmp = *list;
    tmp = tmp->next;
    free(*list);
    //printf("deleted\n");
    delete_list(&tmp);
    
}

void readCSV(FILE *csv , Node** link ){
    char c, buffer[100];
    int i = 0, quotes = 0, column = 0;
    // int count = 0;
    while(c != EOF){                                                //loop for entire file

        Node* head = (Node*)malloc( sizeof( Node ) );
        column = 0;
        
        while(column <= 9 ){    //loop for each line
           
            i = 0;                                    
            do{                                                    
                c = fgetc(csv);
                
                if (c == ','   || c == '\n') {
                    buffer[i] = '\0';
                    break;   
                }
                if (c!= '"'){
                    buffer[i] = c;
                    i++;
                }
            }while(c != EOF); //loop for each word
                    
            // insert words in designated variables
            switch(column){
                case 0:
                    strcpy(head->Person_ID , buffer);
                    break;
                case 1:
                    strcpy(head->Deposition_ID , buffer);
                    break;
                case 2:
                    strcpy(head->Surname , buffer);
                    break;
                case 3:
                    strcpy(head->Forename , buffer);
                    break;
                case 4: 
                    strcpy(head->Age , buffer);
                    break;
                case 5:
                    strcpy(head->Person_Type , buffer);
                    break;
                case 6:
                    strcpy(head->Gender , buffer);
                    break;
                case 7:
                    strcpy(head->Nationality , buffer);
                    break;
                case 8:
                    strcpy(head->Religion , buffer);
                    break;
                 case 9:
                     strcpy(head->Occupation , buffer);
                     break;
            }
            if(c == '\n'){break;} // break if reached end of line
            ++column;
        }
        
        head->next = *link;
        *link = head;
        
    }
}

void PrintTable(Node* table){
    
    Node* tmp = table;
    // Person ID,Deposition ID,Surname,Forename,Age,Person Type,Gender,Nationality,Religion,Occupation
    printf("%-9s | %-10s    | %-10s | %-44s  | %-3s | %-10s  | %-7s  | %-10s  | %-15s  | %s\n", tmp->Person_ID,tmp->Deposition_ID,tmp->Surname,tmp->Forename,tmp->Age,tmp->Person_Type,tmp->Gender,tmp->Nationality,tmp->Religion,tmp->Occupation );
    //printf("%s\n",tmp->Deposition_ID);

}
