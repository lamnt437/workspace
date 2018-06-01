#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 30
#define LINE 100

typedef struct user{
    char username[LENGTH];
    char password[LENGTH];
    double diem;
}User;

typedef User Content_t;
typedef Content_t Content;

//Tree

typedef struct node{
  Content_t data;
  struct node *left, *right;
}NodeTree;

typedef NodeTree *TreeType;

//////////////////////////////////////////////

TreeType makeNodeTree(Content_t v);
TreeType insertNodeTree(TreeType root, NodeTree *newNode);
void inOrder(TreeType root);
TreeType searchBinTree(TreeType root, char key[]);
void swapValueNodeTree(TreeType a, TreeType b);
TreeType delete1(TreeType root);
TreeType deleteNodeTree(TreeType root, char key[]);
void traverseWrite(TreeType root, FILE *write);
void printElement(TreeType root);
void inOrder(TreeType root);

////////////////////////////////////////////////

int main(){
    int login_choice;
    int login_counter = 0;
    int choice;
    TreeType root = NULL;
    TreeType ptr = NULL;
    char line[LINE];
    Content temp_info;
    FILE *read = fopen("sinhvien.txt", "r");
    FILE *write = NULL;
    char *breakpoint = NULL;
    int success_trigger = 0;
    char string1[30];
    char string2[30];
    TreeType temp_ptr = NULL;
    
    while(fgets(line, LINE - 1, read) != NULL){
        if(isspace(line[strlen(line) - 1])){
            line[strlen(line) - 1] = '\0';
        }
        breakpoint = strtok(line, "\t");
        strcpy(temp_info.username, breakpoint);

        breakpoint = strtok(NULL, "\t");
        strcpy(temp_info.password, breakpoint);

        breakpoint = strtok(NULL, "\t");
        temp_info.diem = atof(breakpoint);

        ptr = makeNodeTree(temp_info);
        root = insertNodeTree(root, ptr);
    }
    fclose(read);

    printf("Menu:\n1.Dang nhap\n2.Thoat\n?");
    scanf("%d", &login_choice);
    getchar();

    while(login_choice != 2)
    {
        //LOGIN 3 times
        do{
            printf("Username: ");
            scanf("%s", temp_info.username);
            getchar();
            printf("Password: ");
            scanf("%s", temp_info.password);
            getchar();
            temp_info.diem = 0;

            ptr = searchBinTree(root, temp_info.username);
            if(ptr == NULL){
                login_counter++;
            }
                
            else{
                if(!strcmp(ptr->data.password, temp_info.password)){
                    success_trigger = 1;
                    break;
                }
                else{
                    login_counter++;
                }
            }

            printf("Ten tai khoan hoac mat khau sai, vui long nhap lai!\n");
            printf("So lan nhap sai: %d\n\n", login_counter);
        }while(success_trigger == 0 && login_counter < 3);

        if(success_trigger == 0)
            break;
        else{
            printf("Dang nhap thanh cong!\n");
            success_trigger = 0;
            login_counter = 0;
            //SINH VIEN

            if(strcmp(temp_info.username, "Admin")){
                printf("\
                    1 - Xem diem\n\
                    2 - Thay doi mat khau\n\
                    3 - EXIT\n\
                    ?");
                scanf("%d", &choice);
                getchar();

                while(choice != 3){
                    switch(choice){
                        case 1:
                            printf("\nXem diem\n\n");
                            printf("%s\t%s\n\n", "Ten", "Diem");
                            printElement(ptr);
                            
                            break;
                        case 2:
                            printf("\nThay doi mat khau\n\n");
                            printf("Nhap mat khau moi: ");
                            scanf("%s", string1);
                            getchar();

                            printf("Nhap lai: ");
                            scanf("%s", string2);
                            getchar();

                            if(strcmp(string1, string2))
                                printf("Mat khau khong khop nhau!\n");
                            else{
                                strcpy(ptr->data.password, string1);
                                printf("Doi mat khau thanh cong!\n");
                            }
                            
                            break;
                        default:
                            printf("\nOut of range!\n\n");
                            break;
                    }
                    printf("\
                    1 - Xem diem\n\
                    2 - Thay doi mat khau\n\
                    3 - EXIT\n\
                    ?");
                    scanf("%d", &choice);
                    getchar();
                }
                write = fopen("sinhvien.txt", "w");
                traverseWrite(root, write);
                fclose(write);
            }
            /*end if sinhvien*/

            else{//ADMIN
                printf("\
                    1 - Them mot sinh vien\n\
                    2 - In ra danh sach\n\
                    3 - Xoa sinh vien\n\
                    4 - EXIT\n\
                    ?");
                scanf("%d", &choice);
                getchar();

                while(choice != 4){
                    switch(choice){
                        case 1:
                            printf("\nThem mot sinh vien\n\n");
                            printf("Nhap username: ");
                            scanf("%s", temp_info.username);
                            getchar();

                            printf("Nhap password: ");
                            scanf("%s", temp_info.password);
                            getchar();

                            printf("Nhap diem: ");
                            scanf("%lf", &temp_info.diem);
                            getchar();

                            temp_ptr = makeNodeTree(temp_info);
                            root = insertNodeTree(root, temp_ptr);

                            printf("Them sinh vien thanh cong!\n");
    
                            break;
                        case 2:
                            printf("\nIn ra danh sach\n\n");
                            inOrder(root);
                            
                            break;
                        case 3:
                            printf("\nXoa sinh vien\n\n");
                            printf("Nhap username can xoa: ");
                            scanf("%s", string1);
                            getchar();

                            if(strcmp(string1, "Admin") == 0){
                                printf("Khong the xoa Admin!\n");
                            }
                            else{
                                temp_ptr = searchBinTree(root, string1);
                                // printf("%d\n", temp_ptr == NULL);
                                if(temp_ptr == NULL){
                                    printf("Username khong ton tai!\n");
                                }
                                else{
                                    printElement(temp_ptr);
                                    root = deleteNodeTree(root, string1);
                                    printf("Xoa thanh cong!\n");
                                    inOrder(root);
                                }
                            }
                            break;
                        default:
                            printf("\nOut of range!\n\n");
                            break;
                    }
                    printf("\
                    1 - Them mot sinh vien\n\
                    2 - In ra danh sach\n\
                    3 - Xoa sinh vien\n\
                    4 - EXIT\n\
                    ?");
                    scanf("%d", &choice);
                    getchar();
                }
                write = fopen("sinhvien.txt", "w");
                traverseWrite(root, write);
                fclose(write);
            }
            
            printf("Menu:\n1.Dang nhap\n2.Thoat\n?");
            scanf("%d", &login_choice);
            getchar();
        }
    }
    printf("\nThoat\n");

    return 0;
}

///////////////////////////////////////////////

void printElement(TreeType root){
    printf("%s\t%.2lf\n", root->data.username, root->data.diem);
}


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
  if(strcmp(root->data.username, newNode->data.username) < 0)
    root->right = insertNodeTree(root->right, newNode);
  else
    root->left = insertNodeTree(root->left, newNode);
  return root;
}

TreeType searchBinTree(TreeType root, char key[]){
  if(root == NULL)
    return NULL;
  if(strcmp(root->data.username, key) == 0)
    return root;
  if(strcmp(root->data.username, key) < 0)
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

TreeType deleteNodeTree(TreeType root, char key[]){
  if(root != NULL){
    if(strcmp(root->data.username, key) == 0)
      root = delete1(root);
    else if(strcmp(root->data.username, key)  < 0)
      root->right = deleteNodeTree(root->right, key);
    else
      root->left = deleteNodeTree(root->left, key);
  }
  return root;
}

void traverseWrite(TreeType root, FILE *write){
    if(root != NULL){
        traverseWrite(root->left, write);
        fprintf(write, "%s\t%s\t%.2lf\n", root->data.username, root->data.password, root->data.diem);
        traverseWrite(root->right, write);
    }
}

void inOrder(TreeType root){
  if(root != NULL){
    inOrder(root->left);
    if(strcmp(root->data.username, "Admin"))
        printf("%-15s%-15s\t%.2lf\n", root->data.username, root->data.password, root->data.diem);
    inOrder(root->right);
  }
}