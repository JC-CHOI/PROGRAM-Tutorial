#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
Node *root;
typedef struct voca_node
{
	char alpha;
	char meaning[SIZE];
	struct voca_node* next;
	struct voca_node* bro;
} Node;

Node* add(Node* no,char *word,char *mean)
{
	if(root==NULL)
	{
			
Node* MakeNode(Node* no,char *word,char *voca)
{
	Node *pReturn = NULL;
	pReturn = (Tree *)malloc(sizeof(Node));

	pReturn->next = NULL;
	pReturn->bro = NULL;

	no->next = pReturn;

	return pReturn;	
}
