#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Cornell Castelino 18302358

//declaration
int next_field ( FILE *csv , char *buffer , int max_len );
// struct declaration
typedef struct data data;
struct data{
    char index[5],Name[20],Type1[5],Type2[5],Total[5],HP[5],Attack[5],Defense[5],SpAtk[5],SpDef[5],Speed[5],Generation[5],Legendary[5],PokedexEntry[200];
};

int const  SIZE = 500;
int main(){
    FILE *fp = fopen("pokemon.csv","r");
    char Name;
    int check=0, x = 0;// x is counter for amt of elements
    data NewData[1000];
    char array[SIZE];

    //reading and writing to struct/print
    while(check == 0){
        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].index, array);
        printf("\n#: %s", array);//#
 
        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].Name , array);
        printf("\nName: %s", array);//name

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].Type1 , array);
        printf("\nType 1: %s", array);//type1

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].Type2 , array);
        printf("\nType 2: %s", array);//typ2

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].Total , array);
        printf("\nTotal: %s", array);//tot

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].HP , array);
        printf("\nHP: %s", array);//hp

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].Attack , array);
        printf("\nAttack: %s", array);//atk

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].Defense , array);
        printf("\nDefence: %s", array);//def

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].SpAtk , array);
        printf("\nSp.Attack: %s", array);//sp.atk

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].SpDef , array);
        printf("\nSp.Defence: %s", array);//sp.def

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].Speed , array);
        printf("\nSpeed: %s", array);//speed

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].Generation , array);
        printf("\nGeneration: %s", array);//gen

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].Legendary, array);
        printf("\nLegendary: %s", array);//legend bool

        check = next_field(fp,array,SIZE);
        strcpy(NewData[x].PokedexEntry , array);
        printf("\nPokemon Entry: %s\n", array);//pokemon entry
        x++;
    }

    //processing
    x--; // for excluding the first line
    int avgAtk = 0;
    int y;
    for (int i = 0; i < x;i++){
        avgAtk += atoi(NewData[i].Attack);
    }
    y = avgAtk;
    avgAtk = avgAtk/x;
    printf("\nThe Average attack of all pokemons is: %d pts and %d",avgAtk,y);

    int avgHP = 0;
    for (int i = 0; i < x;i++){
        avgHP += atoi(NewData[i].HP);
    }
    avgHP = avgHP/x;
    printf("\nThe Average HP of all pokemons is: %d pts",avgHP);

    return 0;
}
//reading char from pokemon.csv
int next_field ( FILE *csv , char *buffer , int max_len ){
    char c;
    int i = 0, quotes = 0;
    do{
        c = fgetc(csv);
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