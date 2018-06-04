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

int ipCompare(char ip1[], char ip2[]);
TreeType insertNodeTreeIP(TreeType root, NodeTree *newNode);

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
    char blockList[1000][100];
    int blockCounter = 0;
    int blockTrigger = 0;

    char string[LINE];
    char temp_string[LINE];

    TreeType ipTree = NULL;
    FILE *readIP = NULL;

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
    fclose(read);

    //get block
    while(fgets(line, LINE - 1, blockFile)){
        if(isspace(line[strlen(line) - 1])){
            line[strlen(line) - 1] = '\0';
        }
        strcpy(blockList[blockCounter], line);;
        blockCounter++;
    }
    fclose(blockFile);


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
                printf("\n");
                
                break;
            case 2:
                printf("\nTra cuu ten mien\n\n");
                
                printf("Nhap ten mien: ");
                scanf("%s", string);
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

                for(int i = 0; i < blockCounter; i++){
                    printf("%s\n", blockList[i]);
                }

                blockTrigger = 0;
                printf("\nTra cuu ten mien\n\n");
                printf("Nhap ten mien: ");
                scanf("%s", string);

                if(checkW(string) == 1)
                    temp_ptr = searchBinTree(root, &string[4]);

                else
                    temp_ptr = searchBinTree(root, string);

                //check    
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
                printf("\nIP sort\n\n");

                readIP = fopen("ip.txt", "r");

                while(fgets(line, LINE - 1, readIP) != NULL){
                    if(isspace(line[strlen(line) - 1])){
                        line[strlen(line) - 1] = '\0';
                    }
                    breakpoint = strtok(line, " \t\n");
                    strcpy(temp_info.address, breakpoint);

                    breakpoint = strtok(NULL, "\n");
                    strcpy(temp_info.ip, breakpoint);

                    temp_ptr = makeNodeTree(temp_info);
                    ipTree = insertNodeTreeIP(ipTree, temp_ptr);
                }
                fclose(readIP);

                inOrder(ipTree);
                printf("\n");

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
    printf("%s (%s); ", (root->data).address, (root->data).ip);
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

int ipCompare(char ip1[], char ip2[]){
    char temp_ip1[LENGTH];
    char temp_ip2[LENGTH];
    // int intIP1, int intIP2;
    char *breakpoint = NULL;
    int i = 0;

    strcpy(temp_ip1, ip1);
    strcpy(temp_ip2, ip2);

    // char p1[4][10];
    // char p2[4][10];
    int intIP1[4];
    int intIP2[4];

    breakpoint = strtok(temp_ip1, ".");
    while(breakpoint != NULL){
        // strcpy(p1[i], breakpoint);
        intIP1[i] = atoi(breakpoint);
        breakpoint = strtok(NULL , ".");
        i++;
    }

    i = 0;

    breakpoint = strtok(temp_ip2, ".");
    while(breakpoint != NULL){
        // strcpy(p2[i], breakpoint);
        intIP2[i] = atoi(breakpoint);
        breakpoint = strtok(NULL , ".");
        i++;
    }

    for(i = 0; i < 4; i++){
        // if(strcmp(p1[i], p2[i]) > 0){
        if(intIP1[i] > intIP2[i]){
            return 1;
        }
        // else if(strcmp(p1[i], p2[i]) < 0){
        else if(intIP1[i] < intIP2[i]){
            return -1;
        }
    }

    return 0;
}

TreeType insertNodeTreeIP(TreeType root, NodeTree *newNode){
  if(root == NULL)
    return newNode;
  if(ipCompare(root->data.ip, newNode->data.ip) < 0)
    root->right = insertNodeTreeIP(root->right, newNode);
  else
    root->left = insertNodeTreeIP(root->left, newNode);
  return root;
}

