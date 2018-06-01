#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LENGTH 30
#define LINE 100

//STRUCT STUDENT
typedef struct student{
    char name[NAME_LENGTH];
    double grade;
}Student;

typedef Student Content;


//LIST
typedef struct e{
	Content data;
	struct e *next;
}Element;

typedef Element *List;

//////////////////////////////////////////////////

void printContent(Content v);
void printList(Element *root);

Element *makeNode(Content v);
void insert(List *root, Content v);
// void insertFirst(List *root, Content v);


int main(){
    int choice;
    char line[LINE];
    Content temp_info;
    int counter_D = 0;
    int counter_E = 0;
    FILE *read_D = fopen("6D.txt", "r");
    FILE *read_E = fopen("6E.txt", "r");
    FILE *write = fopen("Excellent.txt", "w");
    List root_D = NULL;
    List root_E = NULL;
    List temp_ptr = NULL;
    double x;
    List excellent = NULL;
    List newList = NULL;
    // List ptrD = NULL;
    // List ptrE = NULL;


    printf("\
            1 - Doc file\n\
            2 - Tim kiem\n\
            3 - Danh sach xuat sac\n\
            4 - Ghi file\n\
            5 - Gop danh sach\n\
            6 - EXIT\n\
            ?");
    scanf("%d", &choice);
    // getchar();

    while(choice != 6){
        switch(choice){
            case 1:
                printf("\nDOC FILE\n\n");
                
                //D
                while(fgets(line, LINE -1, read_D) != NULL){
                    counter_D++;
                    if(counter_D % 2 == 1){
                        line[strlen(line) - 1] = '\0';
                        strcpy(temp_info.name, line);
                    }
                    else{
                        temp_info.grade = atof(line);
                        insert(&root_D, temp_info);
                    }
                }
                if(counter_D % 2 != 0){
                    printf("Them diem bi thieu: ");
                    scanf("%lf", &temp_info.grade);
                    insert(&root_D, temp_info);
                }

                //E
                while(fgets(line, LINE -1, read_E) != NULL){
                    counter_E++;
                    if(counter_E % 2 == 1){
                        line[strlen(line) - 1] = '\0';
                        strcpy(temp_info.name, line);
                    }
                    else{
                        temp_info.grade = atof(line);
                        insert(&root_E, temp_info);
                    }
                }
                if(counter_E % 2 != 0){
                    printf("Them diem bi thieu: ");
                    scanf("%lf", &temp_info.grade);
                    insert(&root_E, temp_info);
                }

                printf("D:\n");
                printList(root_D);
                printf("E:\n");
                printList(root_E);

                fclose(read_D);
                fclose(read_E);

                break;
            case 2:
                printf("\nTIM KIEM\n\n");
                
                printf("Nhap diem x: ");
                scanf("%lf", &x);
                printf("Nhung hoc sinh co diem cao hon %.2lf:\n", x);
                temp_ptr = root_D;
                printf("*Lop 6D:\n");
                while(temp_ptr != NULL){
                    if(temp_ptr->data.grade >= x)
                        break;
                    else
                        temp_ptr = temp_ptr->next;
                }
                if(temp_ptr != NULL)
                    printList(temp_ptr);
                else
                    printf("Khong co!\n");



                temp_ptr = root_E;
                printf("*Lop 6E:\n");
                while(temp_ptr != NULL){
                    if(temp_ptr->data.grade >= x)
                        break;
                    else
                        temp_ptr = temp_ptr->next;
                }
                if(temp_ptr != NULL)
                    printList(temp_ptr);
                else
                    printf("Khong co!\n");
                break;
            case 3:
                printf("\nDANH SACH XUAT SAC\n\n");

                temp_ptr = root_D;
                while(temp_ptr != NULL){
                    if(temp_ptr->data.grade >= 8.5)
                        insert(&excellent, temp_ptr->data);
                    temp_ptr  = temp_ptr->next;
                }
                temp_ptr = root_E;
                while(temp_ptr != NULL){
                    if(temp_ptr->data.grade >= 8.5)
                        insert(&excellent, temp_ptr->data);
                    temp_ptr = temp_ptr->next;
                }
                printf("Excellent:\n\n");
                temp_ptr = excellent;
                while(temp_ptr != NULL){
                    printf("%s\t%.2lf\t%d\n", temp_ptr->data.name, temp_ptr->data.grade, temp_ptr);
                    temp_ptr = temp_ptr->next;
                }
                break;
            case 4:
                printf("\nGHI FILE\n\n");
                temp_ptr = excellent;
                while(temp_ptr != NULL){
                    fprintf(write, "%s\n%.2lf\n", temp_ptr->data.name, temp_ptr->data.grade);
                    temp_ptr = temp_ptr->next;
                }
                fclose(write);
                printf("Successfully written!\n");

                break;
            case 5:
                printf("\nGOP DANH SACH\n\n");
                temp_ptr = root_D;
                while(temp_ptr != NULL){
                    insert(&newList, temp_ptr->data);
                    temp_ptr = temp_ptr->next;
                }
                temp_ptr = root_E;
                while(temp_ptr != NULL){
                    insert(&newList, temp_ptr->data);
                    temp_ptr = temp_ptr->next;
                }

                printf("Danh sach duoc gop:\n\n");
                printList(newList);
                
                break;
            default:
                printf("\nOut of range!\n\n");
                break;
        }
        printf("\
            1 - Doc file\n\
            2 - Tim kiem\n\
            3 - Danh sach xuat sac\n\
            4 - Ghi file\n\
            5 - Gop danh sach\n\
            6 - EXIT\n\
            ?");
        scanf("%d", &choice);
        // getchar();
    }
    printf("\nEXIT\n");

    return 0;
}



/////////////////////////////////////////////////////

void printContent(Content v)
{
	//edit according to elements of content
	printf("%s\t%.2lf\n", v.name, v.grade);
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

	//edit condition of while according to the value being sorted
	while(cur != NULL && v.grade > (cur->data).grade){//
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