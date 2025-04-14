#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "lexerf.h"


typedef enum{
    INT_LIT,
    STATEMENT,
    EXTRAS,
    BEGINNING,
}NodeTypes;


typedef struct  Node{

    char *value;
    NodeTypes type;
    struct Node *left;
    struct Node *right;
}Node;


Node *init_node(Node *node, char *value, NodeTypes type){

    node=malloc(sizeof(Node));
    node->value=malloc(sizeof(char)*2);
    node->value=value;
    node->type=type;
    node->left=NULL;
    node->right=NULL;
    return node;
}

void print_tree(Node *node){
    if(node==NULL){
        return;
    }
    for(size_t i=0;node->value[i]!='\0';i++){
        printf("%c",node->value[i]);
    }
    printf("\n");
    print_tree(node->left);
    print_tree(node->right);
}


Token *parser(Token *tokens){
    Token *current_token=&tokens[0];
    Node *root=malloc(sizeof(Node));
       
    Node *left=malloc(sizeof(Node));
    Node *right=malloc(sizeof(Node));  
  
    root=init_node(root,"EXIT",STATEMENT);
    left=init_node(left,"1",INT_LIT);
    right=init_node(root,";",EXTRAS);


   
    root->left=left;
    root->right=right;
    print_tree(root);
    while(current_token->type!=END_OF_TOKENS){ 
        current_token++;
    }
    return current_token;
}
