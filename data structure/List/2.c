#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char name[50];
	char number[30];
	struct node *next;
} node;

node *head;
node *tail;
void print()
{
	node *house = head;

	if(head == NULL)
	{
		printf("no data ! \n");
		return;	
	}
	else
	{
		while(house)
		{
			printf("%s\t%s\n",house->name,house->number);
			house = house->next;
		}
	}
}
void find()
{
	char namespace[50];

	printf("input name you want to find : ");
	scanf("%s",namespace);

	node *house = head;
	while(1)
	{
		if(!strcmp(house->name,namespace))
		{
			printf("%s\n",house->number);
			break;
		}		
		house = house->next;
	}
}
void insert(char *name, char *number)
{
	node *new = (node *)malloc(sizeof(node));
	strcpy(new->name,name);
	strcpy(new->number,number);
	new->next = 0;

	if(head == NULL)
	{
		head = new;
		tail = new;
	}
	else
		tail->next = new;

	tail = new;
}
void delete()
{
	char name2[50];
	node* cur;
	node* prev;

	prev = head;
	cur = head->next;
	printf("input name you want to delete : ");
	scanf("%s",name2);

	while(prev != NULL)
	{
		if(!strcmp(head->name,name2))
		{
			head = head->next;
			free(prev);
			break;

		}
		else if(!strcmp(cur->name,name2))
		{
			prev->next = cur->next;
			free(cur);
			break;
		}

		prev = cur;
		cur = cur->next;
	}
}
void sort()
{
	node *finger1,*finger2,*buf,*compare;
	
	char tmp[50];

	if(head == NULL)
	{
		printf("sorry no data\n");
		return;
	}

	finger1 = head;
	finger2 = head->next;

	for(tail = head ; head->next != NULL ; tail = tail->next);
	
	while(finger2 != NULL)
	{
		strcpy(tmp,finger1->name);

		if(strcmp(finger2->name,tmp) > 0)
		{
			buf = finger2;
		
int main()
{
	char command[10];
	char name[50];
	char number[20];

	while(1)
	{
		printf("command(print,find,insert,quit) : ");
		scanf("%s",command);

		if(!strcmp(command,"print"))
		{
			print();
		}
		if(!strcmp(command,"find"))
		{
			find();
		}
		if(!strcmp(command,"insert"))
		{
			printf("name : ");	
			scanf("%s",name);
			printf("number : ");
			scanf("%s",number);

			insert(name,number);
		}
		if(!strcmp(command,"delete"))
		{
			delete();
		}
		if(!strcmp(command,"quit"))
		{
			return 0;
		}
	}
		
	return 0;
}
