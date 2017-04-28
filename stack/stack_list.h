#ifndef __STACK_LIST_H
#define __STACK_LIST_H

struct node;
typedef struct node* ptrToStack;
typedef ptrToStack Stack;
typedef ptrToStack Position;
typedef int ElementType num;

/*
 * Stack implementation is a linked list with header.
 * */
struct node
{
	ElementType num;
	Stack next;
}

int IsEmpty(Stack S);
Stack CreateStack(void);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType x, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);

#endif
