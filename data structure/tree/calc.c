#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define LEN 100

typedef struct arrayStack
{
	char stackArr[LEN];
	int top;
} Stack;

void initialize(Stack *pstack);
int is_empty(Stack *pstack);

void push(Stack *pstack,int data);
int pop(Stack *pstack);
int peek(Stack *pstack); // stack function

int priority(char op);
void convert(char exp[],char exp2[]); 
						// convert function
void calculate(char exp[]);
						// calculate function
/*************stack function****************/
typedef struct TreeNode
{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} Tree;

Tree *makeNode(int data);

void delete(Tree *del);
int get_data(Tree *p);

Tree* get_left(Tree *mom);
Tree* get_right(Tree *mom);

void link_left(Tree *mom, Tree *child);
void link_right(Tree *mom, Tree *child);

/************Tree function*****************/
Tree* link_Tree(char exp[]);

void calc_tree(Tree* root);
/*************************/

int main()
{
	char modify[LEN]="0",buf[LEN]="0";
	Tree* tt = NULL; 

	printf("input : ");
	fgets(modify,LEN,stdin);
	modify[strlen(modify)-1] = '\0';

	convert(modify,buf);		
	puts(buf);
	tt = link_Tree(buf);

	calc_tree(tt);
	printf("root data = %d \n",get_data(tt));

	return 0;
}
void initialize(Stack *pstack)
{
	pstack->top = -1;
}

int is_empty(Stack *pstack)
{
	if(pstack->top == -1)
		return TRUE;
	else
		return FALSE;
}

void push(Stack *pstack, int data)
{
	if(pstack->top+1 == LEN)
	{
		printf("it's full");
		return ;
	}

	pstack->top += 1;
	pstack->stackArr[pstack->top] = data;
}

int pop(Stack *pstack)
{
	int del_index;

	if(is_empty(pstack))
	{
		printf("no memory!!");
		return -1;
	}
	
	del_index = pstack->top;
	pstack->top -= 1;

	return pstack->stackArr[del_index] ;
}

int peek(Stack *pstack)
{
	if(is_empty(pstack))
	{
		printf("no memory!!");
		return -1;
	}

	return pstack->stackArr[pstack->top] ;
}

int priority(char op)
{
	switch(op)
	{
		case '*':
		case '/':
			return 3;
		case '+':
		case '-':
			return 2;
		case '(':
			return 1;
	}
	
	return -1;
}
void convert(char exp[],char exp2[])
{
	Stack stack;// operator stack
	int len=strlen(exp);
	char convert_exp[100] ;

	int i, idx =0;
	char tok, pop2;
	char tmp[100] ;
	
	initialize(&stack);

	memset(convert_exp,0,100);
	memset(tmp,0,100);
	
	for(i=0; i<len ; i++)
	{
		tok = exp[i];
		
		if(isdigit(tok))
		{	
			convert_exp[idx++] = tok;
		}
		else
		{
			switch(tok)
			{
				case '(' :
					push(&stack,tok);
					break;
				case ')' :
					convert_exp[idx++] = ' ';
					while(1)
					{
						pop2 = pop(&stack);
						if(pop2 == '(')
							break;
						convert_exp[idx++] = pop2;
					}
					break;
				case '+':
				case '-':
				case '*':
				case '/':
					if(isdigit(exp[i - 1]))
						convert_exp[idx++] = ' ';
					while(!is_empty(&stack) && (priority(peek(&stack)) > priority(tok)))
						convert_exp[idx++] = pop(&stack);
					push(&stack,tok);
				
					break;
			}

		}
	}
	if(isdigit(tok))
		convert_exp[idx++] = ' ';

	while(!is_empty(&stack))
		convert_exp[idx++] = pop(&stack);	

	strcpy(exp2,convert_exp);
}
void calculate(char exp[])
{
	Stack stack;
	int len = strlen(exp);
	char tok;
	char tmp[100];
	int i,j=0,push2,tmp1,tmp2;
	
	initialize(&stack);
	memset(tmp,0,100);

	for(i=0; i<len; i++)
	{
		tok = exp[i];

		if(isdigit(tok))
		{
			tmp[j++] = tok;
		}
		else if(tok == ' ')
		{
			push(&stack,atoi(tmp));
			memset(tmp,0,j);
			j=0;
		}
		else
		{
			tmp1 = pop(&stack);
			tmp2 = pop(&stack);
			switch(tok)
			{
				case '+':
					push2 = tmp2 + tmp1;
					break;
				case '-':
					push2 = tmp2 - tmp1;
					break;
				case '*':
					push2 = tmp2 * tmp1;
					break;
				case '/':									
					push2 = tmp2 / tmp1;
					if(tmp1 == 0)
						printf("divided 0 ! warning\n");
					break;
			}

			push(&stack,push2);
		}
	}
	
	printf("result = %d\n",pop(&stack));
}
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
	printf("delete memory !\n");
	
	if(del->left != NULL)
		delete(del->left);
	if(del->right != NULL)
		delete(del->right);
}
int get_data(Tree *p)
{
	return p->data;
}
Tree *get_left(Tree *mom)
{
	return mom->left;
}
Tree *get_right(Tree *mom)
{
	return mom->right;
}
void link_left(Tree *mom,Tree *child)
{
	if(mom->left != NULL)
	{
		printf("child (already exist) is deleted \n");
		delete(mom->left);
	}

	mom->left = child;
}
void link_right(Tree *mom, Tree *child)
{
	if(mom->right != NULL)
	{
		printf("child (already exist) is deleted \n");
		delete(mom->right);
	}
	
	mom->right = child;
}
Tree* link_Tree(char exp[])
{
	int i;
	char tok;
	Stack stack;
	Tree* tr=NULL;
	Tree* tr1=NULL;
	Tree* tr2=NULL;
	initialize(&stack);

	for(i=0; i<strlen(exp) ; i++)
	{
		tok = exp[i];
		if(isdigit(tok))
		{
			tr = makeNode(tok);
		}
		else if(tok == ' ')
			continue;
		else 
		{			
			tr = makeNode(tok);
			tr1 = pop(&stack);
			tr2 = pop(&stack);
		
			link_right(tr,tr1);
			link_left(tr,tr2);
		}
	
		push(&stack,tr);
	}

	return pop(&stack);
}

void calc_tree(Tree* root)
{
	if(root->left != NULL)
		calc_tree(root->left);
	if(root->right != NULL)
		calc_tree(root->right);
	
	if(root->data == 43)//+ 43
		root->data = (root->left->data + root->right->data);
	if(root->data == 47)/// 47
		root->data = (root->left->data / root->right->data);
	if(root->data == 42)//* 42 
		root->data = (root->left->data * root->right->data);
	if(root->data == 45)//- 45
		root->data = (root->left->data - root->right->data);
}
