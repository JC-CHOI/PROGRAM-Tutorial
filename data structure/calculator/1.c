#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define LEN 100

typedef struct arrayStack
{
	int stackArr[LEN];
	int top;
} Stack;

void initialize(Stack *pstack);
int is_empty(Stack *pstack);

void push(Stack *pstack, int data);
int pop(Stack *pstack);
int peek(Stack *pstack); // stack function

int priority(char op);
void convert(char exp[],char exp2[]); 
						// convert function
void calculate(char exp[]);
						// calculate function
int main()
{
	char modify[LEN];
	char converted[LEN]="0";
	memset(modify,0,LEN);	
	printf("input : ");

	fgets(modify,100,stdin);
	modify[strlen(modify)-1] = '\0';
	
	convert(modify,converted);
	
	printf("%s\n",converted);
	
	calculate(converted);

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
		
