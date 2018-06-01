#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 100
#define SIZE 100

typedef struct info{
    int id;
    int gia;
    int sl;
    char ten[LENGTH];
}Info;

typedef Info Content;

typedef struct e{
	Content data;
	struct e *next;
}Element;

typedef Element *List;

typedef struct trung{
    Element *ptr;
    int sl;
}Trung;

/////////////////////////////////////////////

void printContent(Content elm);
void printList(Element *root);
Element *makeNode(Content v);
void insert(List *root, Content v);
void printListSL(List root, int sl);
int listCounter(List root);

//////////////////////////////////////////////

int main(){
    int choice;
    FILE *read = fopen("data.txt", "r");
    List root = NULL;
    char line[LENGTH];
    char *breakpoint = NULL;
    Content temp_info;

    List ptr = NULL;
    List run_ptr = NULL;
    Trung arrTrung[100];
    int type_counter = 0;
    int dem_trung = 1;
    int trigger = 0;

    List arrTrungTen[100];
    int type_counter_ten = 0;
    for(int i= 0; i < 100; i++){
        arrTrungTen[i] = NULL;
    }





    printf("\
            1 - Nhap san pham\n\
            2 - Sap xep\n\
            3 - Gia trung\n\
            4 - Ten trung\n\
            5 - EXIT\n\
            ?");
    scanf("%d", &choice);
    // getchar();

    while(choice != 5){
        switch(choice){
            case 1:
                printf("\nNhap san pham\n\n");
                while(fgets(line, LENGTH - 1, read) != NULL){
                    if(isspace(line[strlen(line) - 1])){
                        line[strlen(line) - 1] = '\0';
                    }

                    breakpoint = strtok(line, "\t");
                    temp_info.id = atoi(breakpoint);

                    breakpoint = strtok(NULL, "\t");
                    temp_info.gia = atoi(breakpoint);

                    breakpoint = strtok(NULL, "\t");
                    temp_info.sl = atoi(breakpoint);

                    breakpoint = strtok(NULL, "\t");
                    strcpy(temp_info.ten, breakpoint);


                    //add list
                    insert(&root, temp_info);
                }

                
                break;
            case 2:
                printf("\nSap xep\n\n");

                printList(root);
                
                break;
            case 3:
                printf("\nTrung gia\n\n");

                ptr = root;
                while(ptr != NULL){
                    run_ptr = ptr->next;
                    while(run_ptr != NULL){
                        if(run_ptr->data.gia != ptr->data.gia){
                            break;
                        }
                        else{
                            trigger = 1;
                            dem_trung++;
                            run_ptr = run_ptr->next;
                        }
                    }
                    if(trigger != 0){
                        arrTrung[type_counter].ptr = ptr;
                        arrTrung[type_counter].sl = dem_trung;
                        type_counter++;
                    }
                    trigger = 0;
                    dem_trung = 1;
                    ptr = run_ptr;
                }

                printf("Cac loai trung gia:\n");
                for(int i = 0; i < type_counter; i++){
                    printListSL(arrTrung[i].ptr, arrTrung[i].sl);
                }

                break;
            case 4:
                printf("\nTrung ten\n\n");

                trigger = 0;
                ptr = root;
                while(ptr != NULL){
                    for(int i = 0; i < type_counter_ten; i++){
                        if(!strcmp(ptr->data.ten, arrTrungTen[i]->data.ten)){
                            insert(&arrTrungTen[i], ptr->data);
                            trigger = 1;
                            break;
                        }
                    }
                    if(trigger == 0){
                        insert(&arrTrungTen[type_counter_ten], ptr->data);
                        type_counter_ten++;
                    }
                    trigger = 0;
                    ptr = ptr->next;
                }

                for(int i = 0; i < type_counter_ten; i++){
                    if(listCounter(arrTrungTen[i]) > 1){
                        printList(arrTrungTen[i]);
                        printf("\n");
                    }
                }

                break;
            default:
                printf("\nOut of range!\n\n");
                break;
        }
        printf("\
            1 - Nhap san pham\n\
            2 - Sap xep\n\
            3 - Gia trung\n\
            4 - Ten trung\n\
            5 - EXIT\n\
            ?");
        scanf("%d", &choice);
        // getchar();
    }
    printf("\nEXIT\n");

    return 0;
}


////////////////////////////////////////////////////

void printContent(Content v)
{
	printf("%d\t%d\t%d\t%s\n", v.id, v.gia, v.sl, v.ten);
}

void printList(Element *root)
{
	Element *ptr = root;
	while(ptr != NULL){
		printContent(ptr->data);
		ptr = ptr->next;
	}
}

Element *makeNode(Content v)
{
	Element *newNode = (Element *)malloc(sizeof(Element));
	newNode->data = v;
	newNode->next = NULL;

	return newNode;
}

void insert(List *root, Content v)
{
	Element *newNode = makeNode(v);
	Element *cur = *root;
	Element *prev = NULL;

	while(cur != NULL && v.gia < (cur->data).gia){//
		prev = cur;
		cur = cur->next;
	}
	if(prev == NULL){
		newNode->next = *root;
		*root = newNode;
	}
	else{
		newNode->next = cur;
		prev->next = newNode;
	}
}

void printListSL(List root, int sl){
    List ptr = root;
    for(int i = 0; i < sl; i++){
        printContent(ptr->data);
        ptr = ptr->next;
    }
}

int listCounter(List root){
    List ptr = root;
    int counter = 0;
    while(ptr != NULL){
        counter++;
        ptr = ptr->next;
    }
    return counter;
}