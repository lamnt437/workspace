#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 30
#define LINE 100

typedef struct info{
    int id;
    char name[MAX_LENGTH];
    int score;
    int thang;
    int thua;
}Info;

typedef Info Content;

int main(){
    FILE *read = fopen("bongda.txt", "r");
    char line[LINE];
    char *breakpoint;
    int number;
    Content temp_info;
    fscanf(read, "%d\n", &number);

    for(int i = 0; i < number; i++){
        fgets(line, LINE - 1, read);
        printf("line: %s\n", line);
        breakpoint = strtok(line, "\t");
        printf("%s\n", breakpoint);
        // temp_info.id = atoi(breakpoint);

        // breakpoint = strtok(NULL, "\t");
        // printf("%s\n", breakpoint);
    }
    fclose(read);
}