#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node* ptrToList;
typedef ptrToList List;
typedef ptrToList Position;

struct node 
{
	int num;
	Position next;
};

List MakeEmpty(List L);
int IsEmpty(Position P, List L);
int IsLast(List L);
Position Find(int x, List L);
void Delete(int x, List L);
Position FindPrevious(int x, List L);
void Insert(int x, List L, Position P);
void DeleteList(List L);
/*
Position Header(List L);
Position First(List L);
Position Advance(Position P);
int Retrieve(Position P);
*/

#endif
