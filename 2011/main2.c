#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 20
#define LINE 100

typedef struct info{
    char eng[LENGTH];
    char viet[LENGTH];
}Info;

typedef Info Content_t;
typedef Content_t Content;

typedef struct node{
  Content_t data;
  struct node *left, *right;
}NodeTree;

typedef NodeTree *TreeType;

//////////////////////////////////////

TreeType makeNodeTree(Content_t v);
TreeType insertNodeTree(TreeType root, NodeTree *newNode);
void inOrder(TreeType root);
void convertLower(char s[]);
TreeType searchBinTree(TreeType root, char key[]);
void traverse(TreeType root, FILE *write);

//////////////////////////////////////

int main(){
    int choice;
    FILE *read = fopen("data.txt", "r");
    char line[LINE];
    char temp_line[LINE];
    char word[LINE];
    char *breakpoint;
    Content temp_info;
    TreeType root = NULL;
    TreeType temp_ptr = NULL;
    TreeType ptr = NULL;


    printf("\
            1 - Doc file\n\
            2 - Hien thi cay\n\
            3 - Dich Anh Viet\n\
            4 - EXIT\n\
            ?");
    scanf("%d", &choice);
    getchar();

    while(choice != 4){
        switch(choice){
            case 1:
                printf("\nDOC FILE\n\n");
                while(fgets(line, LINE - 1, read) != NULL){
                    breakpoint = strtok(line, "\t");
                    strcpy(temp_info.eng, breakpoint);

                    breakpoint = strtok(NULL, "\t");
                    if(isspace(breakpoint[strlen(breakpoint) - 1]))
                        breakpoint[strlen(breakpoint) - 1] = '\0';
                    strcpy(temp_info.viet, breakpoint);

                    temp_ptr = makeNodeTree(temp_info);
                    root = insertNodeTree(root, temp_ptr);
                }
                fclose(read);
                break;
            case 2:
                printf("\nHIEN THI CAY\n\n");
                inOrder(root);
                break;
            case 3:
                printf("\nDICH ANH VIET\n\n");
                printf("Nhap vao cau can dich: ");
                fgets(line, LINE - 1, stdin);
                line[strlen(line) - 1] = '\0';
                strcpy(temp_line, line);

                printf("Dich:\n\n");

                //CHECK
                breakpoint = strtok(line, " ");

                while(breakpoint){
                    convertLower(breakpoint);
                    temp_ptr = searchBinTree(root, breakpoint);
                    if(temp_ptr == NULL){
                        strcpy(temp_info.eng, breakpoint);
                        printf("Thieu tu %s!\n", breakpoint);
                        printf("Nhap bo sung: ");
                        fgets(temp_info.viet, LINE - 1, stdin);
                        temp_info.viet[strlen(temp_info.viet) -  1] = '\0';
                        ptr = makeNodeTree(temp_info);
                        root = insertNodeTree(root, ptr);
                    }
                    breakpoint = strtok(NULL, " ");
                }

                //TRANSLATE
                printf("%s\n", temp_line);
                breakpoint = strtok(temp_line, " ");

                while(breakpoint){
                    convertLower(breakpoint);
                    temp_ptr = searchBinTree(root, breakpoint);
                    if(temp_ptr == NULL)
                        printf("**");
                    printf("%s ", temp_ptr->data.viet);
                    breakpoint = strtok(NULL, " ");
                }

                printf("\n");

                break;
            default:
                printf("\nOut of range!\n\n");
                break;
        }
        printf("\
            1 - Doc file\n\
            2 - Hien thi cay\n\
            3 - Dich Anh Viet\n\
            4 - EXIT\n\
            ?");
        scanf("%d", &choice);
        getchar();
    }
    printf("\nEXIT\n");

    FILE *write = fopen("data.txt", "w");
    traverse(root, write);
    fclose(write);
    printf("Successfully updated data.txt!\n");

    return 0;
}


///////////////////////////////////////////////////////////////

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
  if(strcmp(root->data.eng, newNode->data.eng) < 0)
    root->right = insertNodeTree(root->right, newNode);
  else
    root->left = insertNodeTree(root->left, newNode);
  return root;
}

void inOrder(TreeType root){
  if(root != NULL){
    inOrder(root->left);
    printf("%-15s%15s\n", (root->data).eng, (root->data).viet);
    inOrder(root->right);
  }
}

void convertLower(char s[]){
    int i = 0;
    while(s[i] != '\0'){
        if(isupper(s[i]))
            s[i] = tolower(s[i]);
        i++;
    }
}

TreeType searchBinTree(TreeType root, char key[]){
  if(root == NULL)
    return NULL;
  if(!strcmp(root->data.eng, key))
    return root;
  if(strcmp(root->data.eng, key) < 0)
    return searchBinTree(root->right, key);
  return searchBinTree(root->left, key);
}

void traverse(TreeType root, FILE *write){
    if(root != NULL){
        traverse(root->left, write);
        fprintf(write, "%s\t%s\n", root->data.eng, root->data.viet);
        traverse(root->right, write);
    }
}