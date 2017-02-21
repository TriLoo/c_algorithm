#ifndef __CURSOR_H
#define __CURSOR_H

#include <stdio.h>
#include <stdlib.h>

typedef int ptrToCursor;
typedef ptrToList Cursor;
typedef ptrToList Position;

#define CursorSize 100

void InitializeCursorSpace(void);
Cursor MakeEmpty(Cursor L);
static Position CursorAlloc(void);
static void CursroFree(Position P); //delete an element from the array.
int IsEmpty(Cursor L);
int IsLast(Cursor L, Position P);
Position Find(int x, Cursor L);
void Delete(int x, Cursor L);
void Insert(int x, Cursor L, Position P);
#endif
