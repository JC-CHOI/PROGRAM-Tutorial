#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 7
struct graph* frame;

typedef struct graph
{
	int V;
	struct node *pan[30];
}graph;

typedef struct node 
{
	int data;
	struct node *link;
}node;

node* makenode(int data)
{
	node* new;
		
	new = (node *)malloc(sizeof(node));

	new->data = data;

	return new;
}
void init_graph(graph* graph,int v)
{
	graph->V = v;

}
	
int load_maze(char *mazefile,char maze[7][7])
{
	FILE *fp;
	char tmp;
	int i,j,count=1;
	
	fp = fopen(mazefile,"r");
	
	if(!fp)
	{
		printf("error");
		return -1;
	}
	
	for(i=0; !feof(fp); i++)
	{
		for(j=0; !feof(fp); j++)
		{
			fscanf(fp,"%c",&tmp);
			if(tmp == '#')
				maze[i][j] = 0;
			if(tmp == ' ')
				maze[i][j] = count++;
	
			printf("%3d",maze[i][j]);
			if(tmp == '\n')
			{
				printf("\n");
			}
		}
	}
}
void draw_node(char** maze_array)
{
	int i,j;
	char tok;
	node* tmp;

	frame = (graph *)malloc(sizeof(graph));

	for(i=0; i<SIZE ; i++)
	{
		for(j=0; j<SIZE ; j++)
		{
			tok = maze_array[i][j];

			if(tok >= 1)
				frame->pan[tok] = makenode(tok);
		}
	}
}		
void connect_node(node *node1, node* node2)
{
	node* tmp1 = node1;
	node* tmp2 = node2;
	
	if(node1->link != NULL)
	{
		while(tmp1->link != NULL)
		{
			tmp1 = node1->link;
		}
		tmp1->link = node2;
	}
	else
		node1->link = node2;

	if(node2->link != NULL)
	{
		while(tmp2->link != NULL)
		{
			tmp2 = node2->link;
		}
		tmp2->link = node1;
	}
	else
		node2->link = node1;
}
void draw_line(graph* graph, char **maze_array)
{
	int i,j;
	char tok,tok2;

	for(i=0; i<SIZE ; i++)
	{
		for(j=0; j<SIZE ; j++)
		{
			tok = maze_array[i][j];
			
			if(tok >= 1)
			{
				tok2 = maze_array[i-1][j]; // 	
				if(tok2 >= 1)
				{
					connect_node(graph->pan[tok],graph->pan[tok2]);
				}
				tok2 = maze_array[i+1][j];
				if(tok2 >= 1)
					connect_node(graph->pan[tok],graph->pan[tok2]);
				tok2 = maze_array[i][j-1];
				if(tok2 >= 1)
					connect_node(graph->pan[tok],graph->pan[tok2]);
				tok2 = maze_array[i][j+1];
				if(tok2 >= 1)
					connect_node(graph->pan[tok],graph->pan[tok2]);
			}
		}
	}
}				
int main(int argc,char *argv[])
{
	char maze_array[SIZE][SIZE] = {0};
	
	load_maze(argv[1],maze_array);

	init_graph(frame,19);

	draw_node(maze_array);
	
	draw_line(frame,maze_array);

	return 0;
}
					

	
