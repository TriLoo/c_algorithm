#include <stdio.h>
#include <stdlib.h>
#include "stack_list.h"

int IsEmpty(Stack S)
{
	return S->next == NULL;
}

void MakeEmpty(Stack S)
{
	if(S == NULL)
		Error("You must create a Stack first!");
	else
		while(!IsEmpty(S))
			Pop(S);
}

Stack CreateStack(void)
{
	Stack S;
	S = (Stack)malloc(sizeof(struct node));
	if (S == NULL)
		FatalError("out of space!!!");
	S->next = NULL;
	MakeEmpty(S);

	return S;
}

void Pop(Stack S)
{
	Stack tmp;
	if (IsEmpty(S))
	{
		Error("Empty Stack ... ");
	}
	else
	{
		tmp = S->next;
		S->next = S->next->next;
		free(tmp);
	}
}

ElementType Top(Stack S)
{
	if(!IsEmpty(S))
		return S->next->num;
	
	Error("Empty Stack...");
	return 0;
	/*
	if(IsEmpty(S))
		Error("Empty Stack...");
	else
	{
		return S->next->num;
	}
	*/
}

void Push(ElementType x, Stack S)
{
	Stack tmp = (Stack)malloc(sizeof(struct node));
	if(tmp == NULL)
		Error("No enough space...");
	else
	{
		tmp->num = x;
		tmp->next = S->next;
		S->next = tmp;
	}
}

void DisposeStack(Stack S)
{
	MakeEmpty(S);
	free(S);
}
