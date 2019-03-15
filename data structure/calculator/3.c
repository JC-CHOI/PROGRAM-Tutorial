#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_SIZE 256

int isOperator(char str);
void getNumber(char *str, int startPos);
int isNumber(char str);
int Calculate(char str);
char data[MAX_SIZE];
int stack[MAX_SIZE]; 
int stackCount=0;

void main()
{
	int i=0,j,sum=0;
	
	memset(stack,0,MAX_SIZE);
	memset(data,0,MAX_SIZE);
	printf("수식을 입력하세요.\n");
	fgets(data,MAX_SIZE,stdin);
	while(data[i]!='=')
	{
		if(isOperator(data[i]))
		{
			stack[stackCount]=i, stackCount++;
		}
		i++;
	}

	j=stackCount++; 
	
	for(i=0; i<stackCount; i++)
	{
		if(stack[stackCount]=='*'||stack[stackCount]=='/')
		{
			getNumber(data, i);
			stack[++stackCount]=Calculate(stack[stackCount-1]);
		}
	}
	for(i=0; i<stackCount; i++)
	{
		if(stack[stackCount]=='+'||stack[stackCount]=='-')
		{
				getNumber(data, i);
																												stack[++stackCount]=Calculate(stack[stackCount-1]);
																														}
																															}
	
																																while(stackCount>j)
																																	{
																																			sum+=stack[stackCount];
																																				}
	
																																					printf("Ansswer : %d",sum);
																																							
	
																																							}
	
																																							int isOperator(char str)
																																							{
																																								return (str=='+'||str=='-'||str=='*'||str=='/') ? TRUE : FALSE;
																																								}
	
																																								int isNumber(char str)
																																								{
																																									return (str<'0'||str>'9') ? FALSE : TRUE;
																																									}
	
																																									void getNumber(char *str, int startPos)
																																									{
																																										int temp=1, pos=startPos;
																																											//먼저 왼쪽의 수를 얻어낸다.
																																												while(isNumber(str[--pos]))
																																													{
																																															stack[stackCount]+=temp*(str[pos]-'0');
																																																	temp*=10;
																																																		}
																																																			stackCount++, temp=1, pos=startPos; // 스택카운트를 증가시키고, temp 및 pos를 초기화한다.
																																																				while(isNumber(str[++pos])){}
	
																																																					while(isNumber(str[--pos]))
																																																						{
																																																								stack[stackCount]+=temp*(str[pos]-'0');
																																																										temp*=10;
																																																											}
	
																																																												stackCount++;
																																																												}
	
																																																												int Calculate(char str)
																																																												{
																																																													int temp=stackCount, ret;
																																																														ret=(str=='*'||str=='/') ? 1 : 0;
																																																															
																																																																switch (str)
																																																																	{
																																																																			case '+':
																																																																					while(temp)
																																																																							{
																																																																										ret+=(stack[--temp]);
																																																																												}
																																																																														break;
	
																																																																																case '*':
																																																																																		while(temp)
																																																																																				{
																																																																																							ret*=(stack[--temp]);
																																																																																									}
																																																																																											break;
	
																																																																																													case '-':
																																																																																															ret=(stack[temp-2]-stack[temp-1]);
																																																																																																	break;
	
																																																																																																			case '/':
																																																																																																					ret=(stack[temp-2]/stack[temp-1]);
																																																																																																							break;
																																																																																																								}
	
																																																																																																									return ret;
																																																																																																									}
