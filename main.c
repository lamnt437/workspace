#include "lib.h"
#include <ctype.h>

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
                break;
            case 4:
                printf("\nTONG HOP\n\n");
                break;
            case 5:
                printf("\nTHONG KE\n\n");
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
    
    printf("Enter key to search: ");
    scanf("%d", &key_temp);

    TreeType ptr = searchBinTree(rootA, key_temp);
    if(ptr != NULL){
      printf("%d\t%s\n", (ptr->data).id, (ptr->data).toy);
      ptr = getParent(rootA, ptr);
      printf("%d\t%s\n", (ptr->data).id, (ptr->data).toy);
    }
    printf("Enter key to delete: ");
    scanf("%d", &key_temp);

    rootA = deleteNodeTree(rootA, key_temp);
    inOrder(rootA);

    return 0;
}
