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

//////////////////////////////////////

int main(){
    int choice;
    FILE *read = fopen("data.txt", "r");
    char line[LINE];
    char *breakpoint;
    Content temp_info;
    TreeType root = NULL;
    TreeType temp_ptr = NULL;


    printf("\
            1 - Doc file\n\
            2 - Hien thi cay\n\
            3 - Dich Anh Viet\n\
            4 - EXIT\n\
            ?");
    scanf("%d", &choice);
    // getchar();

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
                break;
            case 2:
                printf("\nHIEN THI CAY\n\n");
                inOrder(root);
                break;
            case 3:
                printf("\nDICH ANH VIET\n\n");

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
        // getchar();
    }
    printf("\nEXIT\n");

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
    printf("%s\t%s\n", (root->data).eng, (root->data).viet);
    inOrder(root->right);
  }
}