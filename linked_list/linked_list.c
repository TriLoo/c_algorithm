#include "linked_list.h"

<<<<<<< HEAD

=======
#define SpaceSize 10

/* define CursorSpace array*/
struct node CursorSpace[ SpaceSize ];

/* test wether the list is empty*/
>>>>>>> 2a2a169a5a9b19a17279c47eba94dafcc7d7fb1d
int IsEmpty(List L)
{
	/*
	if(L->next == NULL)
		return 1;
	else
		return 0;
		*/
	return L->next == NULL;
}

/* test the P whether is the last element
 * here, the L is unused.
 * */
int IsLast(Position P, List L)
<<<<<<< HEAD
{
	return P->next==NULL;
}

/* function find, return the position of to be found element*/
Position Find(int x, List L)
{
	Position tmp = L->next;
	if(L->num == x)
		tmp = L;
	else
	{
		while (tmp != NULL && tmp->num != x)
		{
			tmp = tmp->next;
		}
	}
	return tmp;
=======
{
	return P->next==NULL;
}

/* function find, return the position of to be found element*/
Position Find(int x, List L)
{
	Position tmp = L->next;
	if(L->num == x)
		tmp = L;
	else
	{
		while (tmp != NULL && tmp->num != x)
		{
			tmp = tmp->next;
		}
	}
	return tmp;
}

/* Delete a element from the list*/
void Delete(int x, List L)
{
	Position tmp;
	Position P = FindPrevious(x, L);
	if( !IsLast(P, L))
	{
		tmp = P->next;
		P->next = tmp->next;
		free(tmp);
	}
}

/* Find the prevoius element to be found element */
Position FindPrevious(int x, List L)
{
	Position P = L;
	while(P->next != NULL && P->next->num != x)
	{
		P = P->next;
	}

	return P;
	//Position tmp = L;
	/*
	if(L == x)
		tmp = L;
	else
	{
		while(P->next != NULL && P->num != x)
		{
			tmp = P;
			P = P->next;
		}
	}
	return tmp;
	*/
}

/* Insert an element to List*/
void Insert(int x, List L, Position P)
{
	Position tmp;
	
	tmp = (struct node)malloc(sizeof(struct node));
	if(tmp == NULL)
		FatalError("Out of space!!");
	tmp->num = x;
	tmp->next = P->next;
	P->next = tmp;
}

/* Delete a list*/
void DeleteList(List L)
{
	Positioin P, tmp;
	P = L->next;
	L->next = NULL;
	while(P->next != NULL)
	{
		tmp = P->next;
		free(P);
		P = tmp;
	}
}

/* Implement CursorSpace initialization*/
void InitializeCursorSpace(ptrToList L)
{
	int i = 1;
	for(i=0; i<SpaceSize; i++)
	{
		L[i]->num = 0;
		L[i]->next = NULL;
	}
>>>>>>> 2a2a169a5a9b19a17279c47eba94dafcc7d7fb1d
}

/* Delete a element from the list*/
void Delete(int x, List L)
{
	Position tmp;
	Position P = FindPrevious(x, L);
	if( !IsLast(P, L))
	{
		tmp = P->next;
		P->next = tmp->next;
		free(tmp);
	}
}

/* Find the prevoius element to be found element */
Position FindPrevious(int x, List L)
{
	Position P = L;
	while(P->next != NULL && P->next->num != x)
	{
		P = P->next;
	}

	return P;
	//Position tmp = L;
	/*
	if(L == x)
		tmp = L;
	else
	{
		while(P->next != NULL && P->num != x)
		{
			tmp = P;
			P = P->next;
		}
	}
	return tmp;
	*/
}

/* Insert an element to List*/
void Insert(int x, List L, Position P)
{
	Position tmp;
	
	tmp = (struct node)malloc(sizeof(struct node));
	if(tmp == NULL)
		FatalError("Out of space!!");
	tmp->num = x;
	tmp->next = P->next;
	P->next = tmp;
}

