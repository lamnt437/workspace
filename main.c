#include "lib.h"

int main(){
    FILE *readA = fopen("A.txt", "r");

    TreeType root = NULL;
    char s_line[LINE_LENGTH];
    char *breakpoint = NULL;
    Info temp_info;
    TreeType temp_insert = NULL;
    int key_temp;

    while(fgets(s_line, LINE_LENGTH - 1, readA) != NULL){
        breakpoint = strtok(s_line, "\t");
        temp_info.id = atoi(breakpoint);
        breakpoint = strtok(NULL, "\t");
        if(breakpoint == NULL){
            temp_info.toy = NULL;
        }
        else{
            temp_info.toy = (char *)malloc(TOY_LENGTH * sizeof(char));
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
