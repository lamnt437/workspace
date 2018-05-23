#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 100
#define TOY_LENGTH 30

#define QUEUE_SIZE 100

typedef struct info{
    int id;
    char *toy;
}Info;

typedef Info Content_t;

typedef Content_t Content;

typedef struct node{
  Content_t data;
  struct node *left, *right;
}NodeTree;

typedef NodeTree *TreeType;


typedef TreeType Element;

typedef struct q{
	int counter;
	int front;
	int rear;
	void *arr[QUEUE_SIZE];
}Queue;

int isEmpty(Queue q);
int isFull(Queue q);
void printElement(Element *v);
void printQueue(Queue q);
void *makeContent(Element v);
int enqueue(Queue *q, Element v);
Element *dequeue(Queue *q);



TreeType makeNodeTree(Content_t v);
TreeType insertNodeTree(TreeType root, NodeTree *newNode);
void preOrder(TreeType root);
void inOrder(TreeType root);
void postOrder(TreeType root);
void BFS(TreeType root);
TreeType searchBinTree(TreeType root, int key);
TreeType getParent(TreeType root, TreeType ptr);///not tested
void swapValueNodeTree(TreeType a, TreeType b);
TreeType delete1(TreeType root);
TreeType deleteNodeTree(TreeType root, int key);
void inOrderReverse(TreeType root);

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
    //   ptr = getParent(rootA, ptr);
      printf("%d\t%s\n", (ptr->data).id, (ptr->data).toy);
    }
    printf("Enter key to delete: ");
    scanf("%d", &key_temp);

    rootA = deleteNodeTree(rootA, key_temp);
    inOrder(rootA);

    return 0;
}




/*==========================Queue============================*/

int isEmpty(Queue q){
	return q.counter == 0;
}

int isFull(Queue q){
	return q.counter == QUEUE_SIZE;
}

/*
void printElement(Element *v){
	//edit according to element content
	printf("%d ", *v);
}

void printQueue(Queue q){
	int i, ptr;
	for(i = 1, ptr = q.front; i <= q.counter; i++){
        printElement((Element *)q.arr[ptr]);
        ptr = (ptr + 1) % QUEUE_SIZE;
	}
	printf("\n");
}
*/

void *makeContent(Element v){
    Element *newContent = malloc(sizeof(Element));
    *newContent = v;
    return newContent;
}

int enqueue(Queue *q, Element v){
	if(!isFull((*q))){
		(*q).arr[(*q).rear] = makeContent(v);
		(*q).rear = ((*q).rear + 1) %	QUEUE_SIZE;
		(*q).counter++;
		return 1;
	}
	return 0;
}

Element *dequeue(Queue *q){
	Element *temp = NULL;
	if(!isEmpty((*q))){
		temp = (Element *)q->arr[q->front];
		q->front = (q->front + 1) % QUEUE_SIZE;
		q->counter--;
	}
	return temp;
}




//////////////////////////////////////////////////////
/*=================Binary Tree======================*/


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
  if((root->data).id < (newNode->data).id)
    root->right = insertNodeTree(root->right, newNode);
  else
    root->left = insertNodeTree(root->left, newNode);
  return root;
}

void preOrder(TreeType root){
  if(root != NULL){
    printf("%d\t%s\n", (root->data).id, (root->data).toy);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void inOrder(TreeType root){
  if(root != NULL){
    inOrder(root->left);
    printf("%d\t%s\n", (root->data).id, (root->data).toy);
    inOrder(root->right);
  }
}

void inOrderReverse(TreeType root){
  if(root != NULL){
    inOrderReverse(root->right);
    printf("%d\t%s\n", (root->data).id, (root->data).toy);
    inOrderReverse(root->left);
  }
}

void postOrder(TreeType root){
  if(root != NULL){
    postOrder(root->left);
    postOrder(root->right);
    printf("%d\t%s\n", (root->data).id, (root->data).toy);
  }
}

void BFS(TreeType root){
  if(root != NULL){
    Queue q1;
    q1.counter = 0;
    q1.front = 0;
    q1.rear = 0;
    TreeType *ptr = NULL;

    enqueue(&q1, root);
    while(!isEmpty(q1)){
      ptr = dequeue(&q1);
      printf("%d\t%s\n", ((*ptr)->data).id, ((*ptr)->data).toy);
      if((*ptr)->left != NULL)
        enqueue(&q1, (*ptr)->left);
      if((*ptr)->right != NULL)
        enqueue(&q1, (*ptr)->right);
    }
  }
}

TreeType searchBinTree(TreeType root, int key){
  if(root == NULL)
    return NULL;
  if((root->data).id == key)
    return root;
  if((root->data).id < key)
    return searchBinTree(root->right, key);
  return searchBinTree(root->left, key);
}

TreeType getParent(TreeType root, TreeType ptr){//not tested
  if(root == NULL || root == ptr)
    return NULL;
  if(root->left == ptr || root->right == ptr)
    return root;
  TreeType p = getParent(root->left, ptr);
  if(p != NULL)
    return p;
  return getParent(root->right, ptr);
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