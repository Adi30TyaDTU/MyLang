#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef enum{
    INT,
    BEGINNING,
    KEYWORD,
    SEPARATOR,
    END_OF_TOKENS,

}TokenType;

 
typedef struct{
    TokenType type;
    char *value;
}Token;


void print_token(Token token){
    printf("TOKEN VALUE: ");
    printf("'");

    for(int i=0;token.value[i]!='\0';i++){
        printf("%c",token.value[i]);
    }
    printf("'");
    switch(token.type){
        case INT:
            printf(" TOKEN TYPE: INT\n");
            break;
        case KEYWORD:
            printf(" TOKEN TYPE: KEYWORD\n");
            break;
        case SEPARATOR:
            printf(" TOKEN TYPE: SEPARATOR\n");
            break;
        case END_OF_TOKENS:
            printf(" END OF TOKENS\n");
            break;
        case BEGINNING:
            printf("BEGINNING\n");
            break;

    }
    
}


Token* generate_number(char *current,int *current_index){

    Token *token=malloc(sizeof(Token));
    token->type=INT;
    char *value=malloc(sizeof(char)*8);
    int value_index=0;
                           

    while(isdigit(current[*current_index])&&current[*current_index]!='\0'){ 
        if(!isdigit(current[*current_index])){
                break;
        }
        value[value_index]=current[*current_index];
        value_index++;
        *current_index+=1;
    }
    value[value_index]='\0';
    token->value=value; 
    return token;
}


Token* generate_keyword(char *current, int *current_index){

    Token *token=malloc(sizeof(Token));
    char *keyword = malloc(sizeof(char)*8);
    int keyword_index=0;
  
    while(isalpha(current[*current_index]) && current[*current_index]!='\0'){
        keyword[keyword_index]=current[*current_index];
        keyword_index++;
        *current_index+=1;
    }
    keyword[keyword_index]='\0';
    if(strcmp(keyword,"exit")==0){
        token->type=KEYWORD;
        token->value="EXIT";
    }
    return token;

}


Token *generate_separator(char *current,int *current_index){
    Token *token=malloc(sizeof(token));
    token->value=malloc(sizeof(char)*2);
    token->value[0]=current[*current_index];
    token->value[1]='\0';
    token->type=SEPARATOR; 
    return token;
            

} 


size_t tokens_index;

Token *lexer(FILE *file){
    int length;
    char *current=0;    
   
    fseek(file,0,SEEK_END);
    length=ftell(file);
    fseek(file,0,SEEK_SET);
   
    current=malloc(sizeof(char)*length);
    fread(current,1,length,file);
    
    fclose(file);
    
    current[length+1]='\0';
    int current_index=0;
   
    Token *tokens=malloc(sizeof(Token));
    tokens_index=0;
         
    while(current[current_index]!='\0'){
        //printf("Curr: %c\n",current[current_index]);
        Token *token=malloc(sizeof(Token));
        if(current[current_index]==';'){
            token=generate_separator(current,&current_index);
            tokens[tokens_index]=*token;
            tokens_index++;
        }
        else if(current[current_index]=='('){

            token=generate_separator(current,&current_index);
            tokens[tokens_index]=*token;
            tokens_index++;
        }
        else if (current[current_index]==')'){
            token=generate_separator(current,&current_index);
            tokens[tokens_index]=*token;
            tokens_index++;
        }
        else if(isdigit(current[current_index])){
            token=generate_number(current,&current_index);
            // printf("TEST TOKEN VALUE : %s\n",test_token->value);
            //print_token(*test_token); 
            current_index--;
            tokens[tokens_index]=*token;
            tokens_index++;
            // printf("FOUND DIGIT: %d\n",(int)current-'0');
        }
        else if(isalpha(current[current_index])){
            token=generate_keyword(current,&current_index);
            current_index--;
            //print_token(*test_keyword);
            tokens[tokens_index]=*token;
            tokens_index++;
            //current=fgetc(file)-1;
            //printf("TEST TOKEN KEYWORD : %s\n",test_token->type);
            //printf("FOUND CHARACTER: %c\n",current);
        }
        
    
        tokens[tokens_index].value='\0';
        tokens[tokens_index].type=END_OF_TOKENS;

        free(token);
        current_index++;
   }
     return tokens;


}


