#include "cursor.h"

struct node 
{
	int num;
	ptrToCursor next;
};

struct node CursorSpace[CursorSize];

void InitializeCursorSpace(void)
{
	int i = 0;
	for(i=0;i<CursorSize; i++)
	{
		CursorSpace[i].next = i+1;
	}
	CursorSpace[i-1].next = 0;
}

static Position CursorAlloc(void)
{
	Position P;
	P = CursorSpace[0].next;

	CursorSpace[0].next = CursorSpace[P].next;

	return P;
}

static void CursorFree(Position P)
{
	CursorSpace[P].next = CursorSpace[0].next;
	CursorSpace[0].next = P;
}

int IsEmpty(Cursor L)
{
	return CursorSpace[L].next==0;
}

int IsLast(Cursor L, Position P)
{
	return CursorSpace[P].next == 0;
}

Position Find(int x, Cursor L)
{
	Position P = CursorSpace[L].next;
	while (P != 0 && CursorSpace[P].num != 0)
	{
		P = CursorSpace[P].next;
	}
	return P;  // if not found, P = 0
}

void Delete(int x, Cursor L)
{
	Position P, tmp;
	/*
	P = CursorSpace[L].next;
	while(P && CursorSpace[L].num != x)
	{
		tmp = P;
		P= CursorSpace[L].next;
	}
	CursorSpace[tmp].next = CursorSpace[P].next;
	*/
	P = FindPrevious(x, L);

	if !IsLast(L, P)
	{
		tmp = CursorSpace[P].next;
		CursorSpace[P].next = CursorSpace[tmp].next;
		CursorFree(tmp);
	}
}

void Insert(int x, Cursor L, Position P)
{
	Position tmp;
	tmp = CursorAlloc();
	if(tmp == 0)
		FatalError("out of range!");
	CursorSpace[tmp].num = x;
	CursorSpace[tmp].next = CursorSpace[P].next;
	CursorSpace[P].next = tmp;
}
