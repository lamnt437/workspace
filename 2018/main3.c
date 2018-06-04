#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 30
#define LINE 100

typedef struct ip_struct{
    char address[LENGTH];
    char ip[LENGTH];
}IP;

typedef IP Content_t;
typedef Content_t Content;

typedef struct node{
  Content_t data;
  struct node *left, *right;
}NodeTree;

typedef NodeTree *TreeType;

////////////////////////////////////////////

TreeType makeNodeTree(Content_t v);
TreeType insertNodeTree(TreeType root, NodeTree *newNode);
void inOrder(TreeType root);
TreeType searchBinTree(TreeType root, char key[]);

int checkW(char string[]);

/////////////////////////////////////////////

int main(){
    int choice;
    FILE *read = fopen("ip.txt", "r");
    
    char line[LINE];
    char *breakpoint = NULL;
    Content temp_info;
    TreeType temp_ptr = NULL;
    TreeType root = NULL;

    FILE *blockFile = fopen("blockedip.txt", "r");
    char blockList[100][100];
    int blockCounter = 0;
    int blockTrigger = 0;

    char string[LINE];
    char temp_string[LINE];

    //get address
    while(fgets(line, LINE - 1, read) != NULL){
        if(isspace(line[strlen(line) - 1])){
            line[strlen(line) - 1] = '\0';
        }
        breakpoint = strtok(line, " \t\n");
        strcpy(temp_info.address, breakpoint);

        breakpoint = strtok(NULL, "\n");
        strcpy(temp_info.ip, breakpoint);

        temp_ptr = makeNodeTree(temp_info);
        root = insertNodeTree(root, temp_ptr);
    }

    //get block
    while(fgets(line, LINE - 1, blockFile)){
        if(isspace(line[strlen(line) - 1])){
            line[strlen(line) - 1] = '\0';
        }
        strcpy(blockList[blockCounter], line);;
        blockCounter++;
    }


    printf("\
            1 - Reading data\n\
            2 - IP lookup\n\
            3 - Block websites\n\
            4 - IP sort\n\
            5 - EXIT\n\
            ?");
    scanf("%d", &choice);
    getchar();

    while(choice != 5){
        switch(choice){
            case 1:
                printf("\nReading data\n\n");

                inOrder(root);
                
                break;
            case 2:
                printf("\nTra cuu ten mien\n\n");
                
                printf("Nhap ten mien: ");
                // fgets(string, LINE -1, read);
                // string[strlen(string) - 1] = '\0';
                scanf("%s", string);
                // printf("Status: %d\n", checkW(string));
                if(checkW(string) == 1)
                    temp_ptr = searchBinTree(root, &string[4]);

                else
                    temp_ptr = searchBinTree(root, string);

                if(temp_ptr == NULL){
                    puts("This site can't be reached");
                }
                else{
                    printf("Redirecting to %s\n", temp_ptr->data.ip);
                }
                
                break;
            case 3:
                printf("\nBlock websites\n\n");

                blockTrigger = 0;
                printf("\nTra cuu ten mien\n\n");
                printf("Nhap ten mien: ");
                // fgets(string, LINE -1, read);
                // string[strlen(string) - 1] = '\0';
                scanf("%s", string);

                temp_ptr = searchBinTree(root, string);
                if(temp_ptr == NULL){
                    puts("This site can't be reached.");
                }
                else{
                    
                    for(int i = 0; i < blockCounter; i++){
                        if(strcmp(temp_ptr->data.address, blockList[i]) == 0 || strcmp(temp_ptr->data.ip, blockList[i]) == 0)
                            blockTrigger = 1;
                    }
                    if(blockTrigger == 1){
                        puts("This site  has been blocked.");
                    }
                    else{
                        printf("Redirecting to %s\n", temp_ptr->data.ip);
                    }
                }

                break;
            case 4:
                printf("\n\n\n");

                break;
            case 5:
                printf("\n\n\n");
                
                break;
            default:
                printf("\nOut of range!\n\n");
                break;
        }
        printf("\
            1 - Reading data\n\
            2 - IP lookup\n\
            3 - Block websites\n\
            4 - IP sort\n\
            5 - EXIT\n\
            ?");
        scanf("%d", &choice);
        getchar();
    }
    printf("\nEXIT\n");

    return 0;
}

////////////////////////////////////////

TreeType makeNodeTree(Content_t v){
  TreeType newNode = (TreeType)malloc(sizeof(NodeTree));
  newNode->data = v;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

TreeType insertNodeTree(TreeType root, NodeTree *newNode){
  if(root == NULL)
    return newNode;
  if(strcmp(root->data.address, newNode->data.address) < 0)
    root->right = insertNodeTree(root->right, newNode);
  else
    root->left = insertNodeTree(root->left, newNode);
  return root;
}

void inOrder(TreeType root){
  if(root != NULL){
    inOrder(root->left);
    printf("%-15s%15s\n", (root->data).address, (root->data).ip);
    inOrder(root->right);
  }
}

TreeType searchBinTree(TreeType root, char key[]){
  if(root == NULL)
    return NULL;
  if(strcmp(root->data.address, key) == 0)
    return root;
  if(strcmp(root->data.address, key) < 0)
    return searchBinTree(root->right, key);
  return searchBinTree(root->left, key);
}

int checkW(char string[]){
    char temp[LINE];
    strcpy(temp, string);
    if(strlen(temp) < 4)
        return 0;
    temp[4] = '\0';
    if(strcmp(temp, "www.") == 0)
        return 1;
    else
        return 0;
}