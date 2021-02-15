#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int const ARRAY_SIZE = 41, MAX_STRING_SIZE = 20 ;
int prime = 10009;

typedef struct hashTable hashTable;
struct hashTable{
    char key[20];
    int frequen;
};

int hash2(char* s);
int readCSV(FILE *csv , char *buffer );
void PrintTable(hashTable* table);

int main(){
    //declarations
    FILE *fp = fopen("names.csv","r");
    char string[20];
    int endFile, Capacity = ARRAY_SIZE, Num_Terms = 0, Collision = 0;
    double load = 0;

    hashTable Hash_table[ARRAY_SIZE];//50

    //initiation of hashtable
    for(int i = 0; i < ARRAY_SIZE; i++){
        strcpy(Hash_table[i].key, "x");
        Hash_table[i].frequen = 0;
    }

    //loop to read through the names.csv file
    while(endFile != 1){
        
        int linearProb = 0, Hash, check = 0, tmp; 
        endFile = readCSV(fp,string);
        Hash = hash2(&string[0]);
        tmp = Hash;
        
        while(check == 0){
            
            if( *Hash_table[Hash].key == 'x'){//new cell
                strcpy(Hash_table[Hash].key, string);
                
                Hash_table[Hash].frequen += 1;
                check = 1;
                ++Num_Terms;
            }
            else if (strcmp(Hash_table[Hash].key ,  string) == 0){ // same cell
                Hash_table[Hash].frequen += 1;
                check = 1;
             }
            else{// linear prob and coliisions
                
                linearProb++;
                Collision++;
                Hash = (tmp+linearProb)%ARRAY_SIZE;
                if (tmp == Hash){
                    break;
                }
                
            }
        }
    }
    load = (double)Num_Terms/(double)Capacity;
    
    //print
    //PrintTable(Hash_table);
    printf("Capacity\t: %d\n",Capacity);
    printf("Num Terms\t: %d", Num_Terms);
    printf("\nCollisions\t: %d\n", Collision);
    printf("Load\t\t:  %0.2f%% \n", load);

    //search
    int end=0  ;
    char temp;
    printf("Enter Term to get the frequency or type 'quit' to escape: ");
     scanf("%[^\n]", string);
     scanf("%c", &temp);
    if (strcmp(string, "quit") == 0){ end = 1;}
    
    while(end == 0){
        int linearProb = 0, Hash = hash2(&string[0]);
        int tmp = Hash ,notFound = 0;
        // printf("%s : %s\n",Hash_table[ Hash ].key,string);
        while(strcmp(Hash_table[ Hash ].key , string) != 0){
            
            linearProb++;
            Hash = (tmp+linearProb)%ARRAY_SIZE;

            if (Hash == tmp){
                printf("%s not Found\n",string);
                notFound = 1;
                break;
            }    
        }
        linearProb = 0;
        if(notFound == 0){
            printf("%s: %d\n", string, Hash_table[Hash].frequen);
            printf("Enter another one: ");
            scanf("%[^\n]", string);
            scanf("%c", &temp);
        }
        else{
            printf("Enter another one: ");
            scanf("%[^\n]", string);    
            scanf("%c", &temp);
        }

        if (strcmp(string, "quit") == 0){
            break;
        }   

    }
    return 0;
}
int hash2(char* s){   
    int hash2 = 0;
    
    while(*s){
    hash2 = ( hash2 + *s * prime  );
    s++;
    
    }
    
    return (hash2)%ARRAY_SIZE;
}

int readCSV(FILE *csv , char *buffer ){
    char c;
    int i = 0;
    do{
        c = fgetc(csv);
        if (c == '\n') {
            buffer[i] = '\0';
            return 0;
        }
        buffer[i] = c;
        i++;
    }while(c != EOF);
    return 1;
}
void PrintTable(hashTable* table){
    for(int i = 0; i < ARRAY_SIZE; i++){
        printf("%s : %d\n", table[i].key, table[i].frequen);
    }
}
