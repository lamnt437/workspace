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


typedef struct e{
	Content data;
	struct e *next;
}Element;

typedef Element *List;

typedef struct m{
    int first;
    int second;
}MatchResult;

void printContent(Content elm);
void printList(Element *root);
Element *makeNode(Content v);
void insertFirst(List *root, Content v);
List insertLast(List root, List ptr);
Element *search(List root, int key);
int delete(List *root, int key);



int main(){
    FILE *read = fopen("bongda.txt", "r");
    char line[LINE];
    char *breakpoint = NULL;
    int number;
    Content temp_info;
    List root =  NULL;
    List temp_ptr1 = NULL;
    List temp_ptr2 = NULL;
    int temp_thang1 = 0;
    int temp_thang2 = 0;
    int chon_vong;
    int trigger[3] = {0};
    
    
    //LOAD NUMBER OF TEAMS
    fscanf(read, "%d\n", &number);

    int round[number - 1][number / 2][2];
    MatchResult id_match[number - 1][number/2];


    for(int i = 0; i < number; i++){
        fgets(line, LINE-1, read);
        breakpoint = strtok(line, "\t");
        temp_info.id = atoi(breakpoint);
        breakpoint = strtok(NULL, "\n");
        breakpoint[strlen(breakpoint) - 1] = '\0';
        strcpy(temp_info.name, breakpoint);

        temp_info.score = 0;
        temp_info.thang = 0;
        temp_info.thua = 0;


        List temp_ptr3 = makeNode(temp_info);
        // insertFirst(&root, temp_info);
        root = insertLast(root, temp_ptr3);
    }

    for(int j = 0; j < number - 1; j++){
        fgets(line, LINE, read);
        for(int i = 0; i < number /2; i++){
            fscanf(read, "%d %d\n", &round[j][i][0], &round[j][i][1]);
        }
    }

    fclose(read);

    int choice;


    printf("\
            1 - In thong tin doi bong\n\
            2 - In thong tin lich thi dau\n\
            3 - Cap nhat ket qua vong dau\n\
            4 - Thong ke\n\
            5 - EXIT\n\
            ?");
    scanf("%d", &choice);
    // getchar();

    while(choice != 5){
        switch(choice){
            case 1:
                printf("\nIn thong tin doi bong\n\n");
                printList(root);

                break;
            case 2:
                printf("\nIn thong tin lich thi dau\n\n");
                for(int i = 0; i < number - 1; i++){
                    printf("Vong %d\n", i + 1);
                    for(int j = 0; j < number/2; j++){
                        temp_ptr1 = search(root, round[i][j][0]);
                        temp_ptr2 = search(root, round[i][j][1]);
                        printf("%s - %s\n", (temp_ptr1->data).name, (temp_ptr2->data).name);
                    }
                }

                break;
            case 3:
                printf("\nCap nhat ket qua vong dau\n\n");
                printf("Chon vong dau muon cap nhat: ");
                scanf("%d", &chon_vong);
                if(1 <= chon_vong && chon_vong <= number - 1){
                    chon_vong--;
                    if(trigger[chon_vong] == 1){
                        printf("Vong dau da duoc cap nhat!\n");
                    }
                    else{
                        trigger[chon_vong] = 1;
                        for(int i = 0; i < number/2; i++){
                            temp_ptr1 = search(root, round[chon_vong][i][0]);
                            temp_ptr2 = search(root, round[chon_vong][i][1]);

                            printf("%s - %s:\n", temp_ptr1->data.name, temp_ptr2->data.name);
                            scanf("%d-%d", &temp_thang1, &temp_thang2);

                            temp_ptr1->data.thang += temp_thang1;
                            temp_ptr2->data.thua += temp_thang1;

                            temp_ptr2->data.thang += temp_thang2;
                            temp_ptr1->data.thua += temp_thang2;

                            //SAVE MATCH RESULT

                            id_match[chon_vong][i].first = temp_thang1;
                            id_match[chon_vong][i].second = temp_thang2;

                            if(temp_thang1 == temp_thang2){
                                (temp_ptr1->data.score) += 1;
                                (temp_ptr2->data.score) += 1;
                            }
                            else if(temp_thang1 < temp_thang2){
                                temp_ptr2->data.score +=3;
                            }
                            else{
                                temp_ptr1->data.score +=3;
                            }
                        }
                    }
                

                    printf("Cap nhat vong dau %d:\n", chon_vong + 1);
                    for(int i = 0; i < number/2; i++){
                        temp_ptr1 = search(root, round[chon_vong][i][0]);
                        temp_ptr2 = search(root, round[chon_vong][i][1]);
                        printf("%s - %s: %d - %d\n", (temp_ptr1->data).name, (temp_ptr2->data).name, 
                        id_match[chon_vong][i].first, id_match[chon_vong][i].second);
                    }
                }

                break;
            case 4:
                printf("\nThong ke\n\n");
                printList(root);

                temp_ptr1 = root;
                temp_ptr2 = root;
                while(temp_ptr1 != NULL){
                    if(temp_ptr1->data.score < temp_ptr2->data.score){
                        temp_ptr2 = temp_ptr1;
                    }
                    temp_ptr1 = temp_ptr1->next;
                }

                delete(&root, temp_ptr2->data.id);
                printf("New:\n\n");
                printList(root);

                break;
            default:
                printf("\nOut of range!\n\n");
                break;
        }
        printf("\
            1 - In thong tin doi bong\n\
            2 - In thong tin lich thi dau\n\
            3 - Cap nhat ket qua vong dau\n\
            4 - Thong ke\n\
            5 - EXIT\n\
            ?");
        scanf("%d", &choice);
        // getchar();
    }
    printf("\nEXIT\n");

    return 0;
}





///////////////////////////////////////////////////////////////

void printContent(Content v)
{
	printf("%5d%15s\t%d\t%d\t%d\n", v.id, v.name, v.score, v.thang, v.thua);
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


void insertFirst(List *root, Content v){
	Element *newNode = makeNode(v);
	newNode->next = *root;
	*root = newNode;
}

List insertLast(List root, List ptr){
    if(root == NULL)
        return ptr;
    root->next = insertLast(root->next, ptr);
    return root;
}



Element *search(List root, int key){              
	Element *ptr = root;
	while(ptr != NULL){
		if(key == (ptr->data).id)
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}

int delete(List *root, int key){
	Element *cur = *root;
	Element *prev = NULL;

    while(cur != NULL && cur->data.id != key){
		prev = cur;
		cur = cur->next;
	}
	if(cur != NULL){
		if(prev == NULL){
			*root = cur->next;
			free(cur);
		}
		else{
			prev->next = cur->next;
			free(cur);
		}

		return 1;
	}
	return 0;
}