#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int const ARRAY_SIZE = 41, MAX_STRING_SIZE = 20 ;

typedef struct hashTable hashTable;
struct hashTable{
    char key[20];
    int frequen;
};

int hash1(char* s);
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
    
    //loop to read through the names.csv  file
    while(endFile != 1){
        
        int linearProb = 0, Hash, check = 0; 
        endFile = readCSV(fp,string);
        Hash = hash1(&string[0]);
        while(check == 0){
            if( *Hash_table[Hash + linearProb].key == 'x'){                     // adds hash key in a new cell
                strcpy(Hash_table[Hash + linearProb].key, string);
                
                Hash_table[Hash + linearProb].frequen += 1;
                check = 1;
                ++Num_Terms;                                                    //Number of new turms
                
            }
            else if (strcmp(Hash_table[Hash + linearProb].key ,  string) == 0){ // if the same cell is found increments the existing value
                Hash_table[Hash + linearProb].frequen += 1;
                check = 1;
             }
            else{                                                              // increments linear prob  and collision counter
                if (linearProb+Hash>=ARRAY_SIZE-1){
                    linearProb = -1*Hash;
                }
                else{
                    linearProb++;
                }
                Collision++;
                check = 0;
            }
        }
    }
    load = (double)Num_Terms/(double)Capacity;
    
    //print whole hashtable and the data
    //PrintTable(Hash_table);
    printf("Capacity\t: %d\n",Capacity);
    printf("Num Terms\t: %d", Num_Terms);
    printf("\nCollisions\t: %d\n", Collision);
    printf("Load\t\t:  %0.2f%% \n", load);
    
    //search
    int end=0;
    char temp;

    printf("Enter Term to get the frequency or type 'quit' to escape: ");
    scanf("%[^\n]", string);
    scanf("%c", &temp);
    if (strcmp(string, "quit") == 0){ end = 1;} // to quit

    while(end == 0){                            // loop to search again and again
        int i = 0, Hash = hash1(&string[0]), false = 0;
        
        while(strcmp(Hash_table[ Hash + i].key , string) != 0){         //finds the index number for the given string
            if (i+Hash>=ARRAY_SIZE -1 && false == 0){
                    i = -1*Hash;
                    false = 1;                                          // it has looped around the hashtable
                }
            else{
                    i++;
                }
            if (i+Hash == Hash && false == 1){
                printf("'%s' not Found",string);
                break;
            }
        }
        i = 0;
        if(false == 0){
            printf("%s: %d\n", string, Hash_table[Hash+i].frequen);
            printf("Enter another one: ");
            scanf("%[^\n]", string);
            scanf("%c", &temp);
        }
        else{
            printf("\nEnter another one: ");
            scanf("%[^\n]", string);    
            scanf("%c", &temp);
        }

        if (strcmp(string, "quit") == 0){
            break;
        }  
    }
    return 0;
}

int hash1(char* s){   
    int hash1 = 0;
    
    while(*s){
    hash1 = (hash1 + *s);
    s++;
    }
    
    return (hash1 % ARRAY_SIZE);
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
