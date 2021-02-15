#include<stdio.h>
#include<stdlib.h>

// Cornell Castelino 18302358

int next_field ( FILE *csv , char *buffer , int max_len );

int const  SIZE = 100;
int main(){
    FILE *fp = fopen("pokemon.csv","r");
    char Name;
    int check=0;
    char array[500];
    while(check == 0){
        check = next_field(fp,array,SIZE);
        printf("\n#: %s", array);//#
 
        check = next_field(fp,array,SIZE);
        printf("\nName: %s", array);//name

        check = next_field(fp,array,SIZE);
        printf("\nType 1: %s", array);//type1

        check = next_field(fp,array,SIZE);
        printf("\nType 2: %s", array);//typ2

        check = next_field(fp,array,SIZE);
        printf("\nTotal: %s", array);//tot

        check = next_field(fp,array,SIZE);
        printf("\nHP: %s", array);//hp

        check = next_field(fp,array,SIZE);
        printf("\nAttack: %s", array);//atk

        check = next_field(fp,array,SIZE);
        printf("\nDefence: %s", array);//def

        check = next_field(fp,array,SIZE);
        printf("\nSp.Attack: %s", array);//sp.atk

        check = next_field(fp,array,SIZE);
        printf("\nSp.Defence: %s", array);//sp.def

        check = next_field(fp,array,SIZE);
        printf("\nSpeed: %s", array);//speed

        check = next_field(fp,array,SIZE);
        printf("\nGeneration: %s", array);//gen

        check = next_field(fp,array,SIZE);
        printf("\nLegendary: %s", array);//legend bool

        check = next_field(fp,array,SIZE);
        printf("\nPokemon Entry: %s\n", array);//pokemon entry
        
    }
    return 0;
}
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