#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ID_LENGTH 10
#define LINE 100

typedef struct team{
    char id[ID_LENGTH];
    int score;
}Team;

typedef Team Content_t;
typedef Content_t Content;

typedef struct node{
    Content_t data;
    struct node *left;
    struct node *right;
}NodeTree;

typedef NodeTree *TreeType;

/////////////////////////////////////////////////////////
TreeType makeNodeTree(Content_t v);
TreeType insertNodeTree(TreeType root, NodeTree *newNode);
void inOrder(TreeType root);
TreeType searchBinTree(TreeType root, char key[]);
TreeType getParent(TreeType root, TreeType ptr);
void swapValueNodeTree(TreeType a, TreeType b);
TreeType delete1(TreeType root);

/////////////////////////////////////////////////////////


int main(){
    //INPUT
    FILE *read = fopen("BongDa.txt", "r");
    char temp_id1[ID_LENGTH];
    char temp_id2[ID_LENGTH];
    int temp_goal1, temp_goal2;
    int temp_score1 = 0, temp_score2 = 0;
    Content_t temp_info1, temp_info2;
    TreeType root = NULL;
    char line[LINE];
    char *breakpoint = NULL;

    TreeType temp_ptr1 = NULL;
    TreeType temp_ptr2 = NULL;

    int nodeCounter = 0;



    int choice;


    printf("\
            1 - Tao cay\n\
            2 - Ket qua\n\
            3 - Tim kiem\n\
            4 - Xuong hang\n\
            5 - Xuat file\n\
            6 - EXIT\n\
            ?");
    scanf("%d", &choice);
    // getchar();

    while(choice != 6){
        switch(choice){
            case 1:
                printf("\nTAO CAY\n\n");

                while(fgets(line, LINE - 1, read) != NULL){
                    breakpoint = strtok(line, "\t");
                    strcpy(temp_id1, breakpoint);

                    breakpoint = strtok(NULL, "\t");
                    strcpy(temp_id2, breakpoint);

                    breakpoint = strtok(NULL, "\t");
                    temp_goal1 = atoi(breakpoint);

                    breakpoint = strtok(NULL, "\t");
                    temp_goal2 = atoi(breakpoint);

                    //process score
                    if(temp_goal1 == temp_goal2){
                        temp_score1 = 1;
                        temp_score2 = 1;
                    }
                    else if(temp_goal1 < temp_goal2){
                        temp_score2 = 3;
                    }
                    else{
                        temp_score1 = 3;
                    }

                    //search for existing id
                    temp_ptr1 = searchBinTree(root, temp_id1);
                    if(temp_ptr1 != NULL){
                        temp_ptr1->data.score += temp_score1;
                    }
                    else{
                        nodeCounter++;
                        printf("Nut moi thu %d\n", nodeCounter);
                        strcpy(temp_info1.id, temp_id1);
                        temp_info1.score = temp_score1;
                        temp_ptr1 = makeNodeTree(temp_info1);
                        printf("Dia chi: %d\n", temp_ptr1);
                        root = insertNodeTree(root, temp_ptr1);
                    }

                    temp_ptr2 = searchBinTree(root, temp_id2);
                    if(temp_ptr2 != NULL){
                        temp_ptr2->data.score += temp_score2;
                    }
                    else{
                        nodeCounter++;
                        printf("Nut moi thu %d\n", nodeCounter);
                        strcpy(temp_info2.id, temp_id2);
                        temp_info2.score = temp_score2;
                        temp_ptr2 = makeNodeTree(temp_info2);
                        printf("Dia chi: %d\n", temp_ptr2);
                        root = insertNodeTree(root, temp_ptr2);
                    }
                }
                
                break;
            case 2:
                printf("\nKET QUA\n\n");
                inOrder(root);
                break;
            case 3:
                printf("\nTIM KIEM\n\n");

                printf("Nhap ma doi bong muon tim kiem: ");
                scanf("%s", temp_id1);
                getchar();

                temp_ptr1 = searchBinTree(root, temp_id1);
                if(temp_ptr1 != NULL){
                    printf("%-15s\t%5d\n", (temp_ptr1->data).id, (temp_ptr1->data).score);
                }
                else
                    printf("Khong co doi bong nay!\n");
                break;
            case 4:
                printf("\nXUONG HANG\n\n");

                break;
            case 5:
                printf("\nXUAT FILE\n\n");
                
                break;
            default:
                printf("\nOut of range!\n\n");
                break;
        }
        printf("\
            1 - Tao cay\n\
            2 - Ket qua\n\
            3 - Tim kiem\n\
            4 - Xuong hang\n\
            5 - Xuat file\n\
            6 - EXIT\n\
            ?");
        scanf("%d", &choice);
        // getchar();
    }
    printf("\nEXIT\n");

    return 0;
}




///////////////////////////////////////////////////////


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
  if(strcmp((root->data).id, (newNode->data).id) < 0)
    root->right = insertNodeTree(root->right, newNode);
  else
    root->left = insertNodeTree(root->left, newNode);
  return root;
}
/*
void preOrder(TreeType root){
  if(root != NULL){
    // printf("%d\t%s\n", (root->data).id, (root->data).toy);
    preOrder(root->left);
    preOrder(root->right);
  }
}
*/
void inOrder(TreeType root){
  if(root != NULL){
    inOrder(root->left);
    printf("%-15s\t%5d\n", (root->data).id, (root->data).score);
    inOrder(root->right);
  }
}

void postOrder(TreeType root){
  if(root != NULL){
    postOrder(root->left);
    postOrder(root->right);
    // printf("%d\t%s\n", (root->data).id, (root->data).toy);
  }
}

TreeType searchBinTree(TreeType root, char key[]){
  if(root == NULL)
    return NULL;
  if(!strcmp(root->data.id, key))
    return root;
  if(strcmp(root->data.id, key) < 0)
    return searchBinTree(root->right, key);
  return searchBinTree(root->left, key);
}

void swapValueNodeTree(TreeType a, TreeType b){
  Content_t temp = a->data;
  a->data = b->data;
  b->data = temp;
}

TreeType delete1(TreeType root){
  if(root->left == NULL && root->right == NULL)
    return NULL;
  if(root->left == NULL && root->right != NULL)
    return root->right;
  if(root->left != NULL && root->right == NULL)
    return root->left;
  NodeTree *lmrParent = root;
  NodeTree *lmr = root->right;//both left and right different from NULL
  while(lmr->left != NULL){
    lmrParent = lmr;
    lmr = lmr->left;
  } 
  //swap
  swapValueNodeTree(root, lmr);
  if(lmrParent == root)
    lmrParent->right = NULL;
  else
    lmrParent->left = NULL;
  free(lmr);
  return root;
}
/*
TreeType deleteNodeTree(TreeType root, int key){
  if(root != NULL){
    
    if((root->data).id == key)
      root = delete1(root);
    else if((root->data).id < key)
      root->right = deleteNodeTree(root->right, key);
    else
      root->left = deleteNodeTree(root->left, key);
    
  }
  return root;
}
*/