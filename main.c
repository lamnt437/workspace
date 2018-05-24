#include "lib.h"
#include <ctype.h>

char toy_type[100][100];
int type_counter = 0;
int freq[100] = {0};

void Traverse(TreeType root);


int main(){
    FILE *readA = fopen("A.txt", "r");
    FILE *readB = fopen("B.txt", "r");

    TreeType rootA = NULL;
    Content rootB[100];
    int counter = 0;

    char s_line[LINE_LENGTH];
    char *breakpoint = NULL;
    Info temp_info;
    TreeType temp_insert = NULL;
    TreeType ptr_search = NULL;
    TreeType newNode = NULL;
    int key_temp;
    char string_temp[LINE_LENGTH];

    int choice;

    printf("\
            1 - Doc file A\n\
            2 - Doc file B\n\
            3 - Tim kiem\n\
            4 - Tong hop\n\
            5 - Thong ke\n\
            6 - Thoat\n\
            ?");
    scanf("%d", &choice);
    getchar();

    while(choice != 6){
        switch(choice){
            case 1:
                printf("\nDOC FILE A\n\n");
                
                while(fgets(s_line, LINE_LENGTH - 1, readA) != NULL){
                    //get id
                    breakpoint = strtok(s_line, "\t");
                    temp_info.id = atoi(breakpoint);

                    //get toy name
                    breakpoint = strtok(NULL, "\t");
                    if(isspace(breakpoint[0])){//meet \n -> empty toy name
                        printf("Id %d doesn't have any toy name, please fill in: ", temp_info.id);
                        fgets(string_temp, LINE_LENGTH - 1, stdin);
                        string_temp[strlen(string_temp) - 1] = '\0';

                        temp_info.toy = (char *)malloc(TOY_LENGTH * sizeof(char));
                        strcpy(temp_info.toy, string_temp);
                    }
                    else{
                        temp_info.toy = (char *)malloc(TOY_LENGTH * sizeof(char));
                        breakpoint[strlen(breakpoint) -1] = '\0';
                        strcpy(temp_info.toy, breakpoint);
                    }
                    temp_insert = makeNodeTree(temp_info);
                    rootA = insertNodeTree(rootA, temp_insert);
                }
                fclose(readA);

                inOrder(rootA);
                break;
            case 2:
                printf("\nDOC FILE B\n\n");
                while(fgets(s_line, LINE_LENGTH - 1, readB) != NULL){
                    breakpoint = strtok(s_line, "\t");
                    temp_info.id = atoi(breakpoint);

                    //get toy name
                    breakpoint = strtok(NULL, "\t");
                    if(isspace(breakpoint[0])){//meet \n -> empty toy name
                        printf("Id %d doesn't have any toy name, please fill in: ", temp_info.id);
                        fgets(string_temp, LINE_LENGTH - 1, stdin);
                        string_temp[strlen(string_temp) - 1] = '\0';

                        temp_info.toy = (char *)malloc(TOY_LENGTH * sizeof(char));
                        strcpy(temp_info.toy, string_temp);
                    }
                    else{
                        temp_info.toy = (char *)malloc(TOY_LENGTH * sizeof(char));
                        breakpoint[strlen(breakpoint) -1] = '\0';
                        strcpy(temp_info.toy, breakpoint);
                    }
                    rootB[counter] = temp_info;
                    counter++;
                }

                for(int i = 0; i < counter; i++){
                    printf("%d\t%s\n", rootB[i].id, rootB[i].toy);
                }

                fclose(readB);
                break;
            case 3:
                printf("\nTIM KIEM\n\n");

                printf("Du lieu bi trung:\n");
                for(int i = 0; i < counter; i++){
                    ptr_search = searchBinTree(rootA, rootB[i].id);
                    if(ptr_search != NULL){
                        printf("%d\t%s\n", (ptr_search->data).id, (ptr_search->data).toy);
                        rootA = deleteNodeTree(rootA, rootB[i].id);
                    }
                }
                printf("Cay da cap nhat:\n");
                inOrder(rootA);

                break;
            case 4:
                printf("\nTONG HOP\n\n");
                
                for(int i = 0; i < counter; i++){
                    newNode = makeNodeTree(rootB[i]);
                    rootA = insertNodeTree(rootA, newNode);
                }

                printf("Cay A da duoc tong hop:\n");
                inOrderReverse(rootA);

                break;
            case 5:
                printf("\nTHONG KE\n\n");
                Traverse(rootA);
                for(int i = 0; i < type_counter; i++){
                    printf("%s\t%d\n", toy_type[i], freq[i]);
                }
                break;
            default:
                printf("\nOut of range 1 - 6!\n\n");
                break;
        }
        printf("\
            1 - Doc file A\n\
            2 - Doc file B\n\
            3 - Tim kiem\n\
            4 - Tong hop\n\
            5 - Thong ke\n\
            6 - Thoat\n\
            ?");
        scanf("%d", &choice);
        getchar();
    }
    printf("\nEXIT\n");

    return 0;
}



void Traverse(TreeType root){
  if(root != NULL){
    Traverse(root->left);
    int trigger = 0;
    for(int i = 0; i < type_counter; i++){
        if(!strcmp(toy_type[i], (root->data).toy)){
            freq[i]++;
            trigger = 1;
            break;
        }
    }
    if(trigger == 0){
        strcpy(toy_type[type_counter], (root->data).toy);
        freq[type_counter]++;
        type_counter++;
    }
    Traverse(root->right);
  }
}