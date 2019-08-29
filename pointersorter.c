#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct node{
    char* word;
    struct node *left, *right;
};

void type_one(char *str1, struct node *n1); 
void type_two(char *str1,struct node *n1);
bool contains_upper(char *str){
    int i = 0;
    for(i = 0 ; str[i]!='\0'; i++){
        if(str[i]>='A' && str[i]<='Z'){
            return true;
        }
    }
    return false;
}

bool chasprecedence(char *str1, char *str2){

    int i=0;

    while(str1!=NULL || str2!=NULL){
        if((str1[i]<='Z' && str1[i] >='A') && (str2[i] <= 'Z' && str2[i]>='A')){
            if(str1[i] > str2[i]){
               return true; 
            }
            else if(str1[i] == str2[i] ){
                i++;
                continue;
            }
            else{
                return false;
            }
        }
        if((str1[i]>='a' && str1[i]<='z') && (str2[i]>='a' && str2[i]<='z')){
            if(str1[i] > str2[i]){
                return true;
            }
            else if(str1[i] == str2[i]){
                i++;
                continue;
            }
            else{
                return false;
            }
        }
        //meaning str1 has precedence over str2
        if((str1[i]<='Z' && str1[i]>='A') && !(str2[i]<='Z' && str2[i]>='A')){
            if(str2[i] == '\0'){
                return false;
            }
            return true;
        }
        if(!(str1[i] >= 'a' && str1[i] <='z') && (str1[i] >='a' && str2[i]<='z')){
            return true;
        }
        i++;
    }
    return false;
}

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s\n", root->word);
        inorder(root->right);
    }
}

struct node *newNode(char* item)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->word = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* insert(struct node* node, char* word)
{
    /* If the tree is empty, return a new node */
    if (node == NULL){
     return newNode(word);
    }
    /* Otherwise, recur down the tree */
    else if (strcmp(word, node->word) >0) {
        if(contains_upper(word) && !contains_upper(node->word)){

            type_one(word,node);
        }
        else if(!contains_upper(word) && contains_upper(node->word)){
            type_one(word,node);
            }
        else if(contains_upper(word) && contains_upper(node->word)){
          type_one(word,node);
        }
        else{
            node->left  = insert(node->left, word);
        }
    } 
    else if (strcmp(word,node->word)<0){
        if(contains_upper(word) && !contains_upper(node->word)){
            type_two(word,node);
        }else if(!contains_upper(word) && contains_upper(node->word)){
            type_two(word,node);
        }
        else if(contains_upper(word) && contains_upper(node->word)){
            type_two(word,node);
        }
        else{
            node->right = insert(node->right, word);
        }
    }
    else if (strcmp(word,node->word)==0){
        node->right = insert(node->right,word);
         
    }
    /* return the (unchanged) node pointer */
    return node;
}

void type_one(char *str1, struct node* n1){
    if(chasprecedence(n1->word,str1)){
        n1->right = insert(n1->right, str1);
    }
    else{
        n1->left = insert(n1->left,str1);
    }
}

void type_two(char *str1, struct node* n1){
    if(chasprecedence(str1, n1->word)){
        n1->left = insert(n1->left,str1);
    }
    else{
        n1->right = insert(n1->right,str1);
    }
}

int main(int argc, char **argv){
   
    if(argv[2]!=NULL){
        printf("No words/letters, too many arguments, or something wrong with code\n");
        return -1;
    }
    char *temp = argv[1];
    int i = 0;

    for( i = 0 ; i < strlen(temp); i++){
      if(!isalpha(temp[i])){
           temp[i] = ' ';
           continue;
       }
    }

struct node *root = NULL;
char *token = strtok(temp, " ");

while(token!=NULL){
    if(root == NULL){
        root = insert(root, token);
        token = strtok(NULL, " ");
        continue;
    }
    insert(root,token);
    token = strtok(NULL ," ");
}
inorder(root);
return 0;
}


