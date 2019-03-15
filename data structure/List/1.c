#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct address *last=NULL;

typedef struct address {
	char name[20];
	struct address *next;
} ar;

void store(ar *item)
{
	if(last == NULL)
		last = item;
	else
		last->next = item;

	item->next = 0;
	last = item;
}

void display(ar *top)
{
	while(top)
	{
		printf("%s\n",top->name);
		top = top->next;
	}
}

void main()
{
	ar *head=0;
	ar *tmp;

	head=tmp=(ar *)malloc(sizeof(ar));
	strcpy(tmp->name,"HONG GIL DONG");
	store(tmp);
	tmp = (ar *)malloc(sizeof(ar));
	strcpy(tmp->name,"KIM CHUL SU");
	store(tmp);
	display(head);
}
