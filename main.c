#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexerf.h"
#include "parserf.h" 


int main(int argc, char *argv[]){
    if(argc<2){
        printf("Error: correct syntax: %s <filename.unn> <output_filename>\n", argv[0]);
        exit(1);
    }
    FILE *file;
	file=fopen(argv[1],"r");
    if(!file){
        printf("ERROR: File not found\n");
        exit(1);
    }
    Token *tokens=lexer(file);
     
    for(size_t i=0;tokens[i].type!=END_OF_TOKENS;i++){
        print_token(tokens[i]);
    }
    parser(tokens);  
    return 0;
	
}

