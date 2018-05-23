#include "lib.h"
#include <ctype.h>

int main(){
    FILE *readA = fopen("A.txt", "r");

    TreeType root = NULL;
    char s_line[LINE_LENGTH];
    char *breakpoint = NULL;
    Info temp_info;
    TreeType temp_insert = NULL;
    int key_temp;
    char string_temp[LINE_LENGTH];

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
        root = insertNodeTree(root, temp_insert);
    }
    fclose(readA);

    BFS(root);
    printf("Enter key to search: ");
    scanf("%d", &key_temp);

    TreeType ptr = searchBinTree(root, key_temp);
    if(ptr != NULL)
      printf("%d\t%s\n", (ptr->data).id, (ptr->data).toy);
    printf("Enter key to delete: ");
    scanf("%d", &key_temp);

    root = deleteNodeTree(root, key_temp);
    inOrder(root);

    return 0;
}
