#include "lib.h"

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
