#include <stdio.h>
#include <stdlib.h>
typedef struct Tree
{
	int data;
	struct Tree *left ;
	struct Tree *right ;
} Tree;

Tree *makeNode(int data)
{
	Tree *Return = NULL;
	Return = (Tree *)malloc(sizeof(Tree));

	Return->data = data;
	Return->left = NULL;
	Return->right = NULL;
	
	return Return;
}
void delete(Tree *del)
{
	free(del);
	printf("delete memory\n");
	if(del->left != NULL)
		delete(del->left);
	if(del->right !=NULL)
		delete(del->right);
}
int get_data(Tree *p)
{
	return p->data;
}
/*void set_data(Tree *p,int data2)
{
	p->data = data2;
}*/  // i do not need this function
Tree* get_left(Tree *mom)
{
	return mom->left;
}
Tree* get_right(Tree *mom)
{
	return mom->right;
}

void link_left(Tree *mom,Tree *child)
{
	if(mom->left != NULL)
	{
		printf("child alreay exit is delete !\n");
		delete(mom->left);
	}
	mom->left = child;
}

void link_right(Tree *mom,Tree *child)
{
	if(mom->right != NULL)
	{
		printf("child alreay exit is delete !\n");
		delete(mom->right);
	}
	mom->right = child;
}
void traversal(Tree* tr) //preorder traversal
{
	//printf("%d \n",tr->data);

	if(tr->left != NULL)
		traversal(tr->left);
	//printf("%d \n",tr->data);
	if(tr->right !=NULL)
		traversal(tr->right);
	printf("%d \n",tr->data);
}
int main()
{
	Tree* tree1 = makeNode(1);
	Tree* tree2 = makeNode(2);
	Tree* tree3 = makeNode(3);
	Tree* tree4 = makeNode(4);

	link_left(tree1,tree2);
	link_right(tree1,tree3);
	link_left(tree3,tree4);

//	printf("%d \n",tree1->right->right->data);

	traversal(tree1);
	
	delete(tree1);
	return 0;
}
