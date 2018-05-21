#include "lib.h"

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
	//edit temp value
	Element *temp = NULL;//
	if(!isEmpty((*q))){
		temp = (Element *)q->arr[q->front];
		q->front = (q->front + 1) % QUEUE_SIZE;
		q->counter--;
	}
	return temp;
}

/*
void freeQueue(Queue *q){
    Element *temp = NULL;
    while(!isEmpty(*q)){
        temp = dequeue(q);
        free(temp;)
    }
}

int main(){
    // Element *ptr = makeContent(5);
    Queue q1;
    Element *temp = NULL;
    q1.counter = 0;
    q1.rear = 0;
    q1.front = 0;

    for(int i = 0; i < 10; i++){
        enqueue(&q1, i);
    }
    printQueue(q1);
    /*
    int n = q1.counter;
    int j = q1.front;


    for(int i = 0; i < n; i++){
        printElement((Element *)q1.arr[j]);
        j++;
    }

    // Element *ptr = makeContent(5);
    // printf("%d", *ptr);
    while(!isEmpty(q1)){
        temp = dequeue(&q1);
        printf("%d ", *((int *)temp));
    }
    printf("\n");

    return 0;
}
*/


//////////////////////////////////////////////////////

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
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void inOrder(TreeType root){
  if(root != NULL){
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
  }
}

void postOrder(TreeType root){
  if(root != NULL){
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
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
      printf("%d ", (*ptr)->data);
      if((*ptr)->left != NULL)
        enqueue(&q1, (*ptr)->left);
      if((*ptr)->right != NULL)
        enqueue(&q1, (*ptr)->right);
    }
  }
}
