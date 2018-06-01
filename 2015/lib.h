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
