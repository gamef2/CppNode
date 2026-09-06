#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STACK_INIT_SIZE 20

typedef void* ElemType;
typedef struct  
{
	ElemType elem;
	int elemSize;//每个元素的大小
	int destLen;//当前所占的位置
	int stackSize;//栈的大小
}Stack,*pStack;

void StackInit(pStack s, int elemSize)
{
	/* 得到类型大小 */
	s->elemSize = elemSize;
	/* 当前栈大小 */
	s->destLen = 0;
	/* 实际栈的大小20 */
	s->stackSize = 4;
	/* 分配元素大小(栈大小 * 元素大小) */
	s->elem = (ElemType)malloc(s->stackSize * s->elemSize);
	if (!s->elem)
		exit(0);
}
void StackDestroy(pStack s)
{
	/* 释放内存 */
	free(s->elem);
}
/* 获取当前大小 */
int StackLen(pStack s)
{
	return s->destLen;
}

void StackPush(pStack s,ElemType e)
{
	/* 判断当前大小与栈大小是不是一样 */
	if (s->destLen ==s->stackSize)
	{
		s->stackSize *= 2;
		s->elem = realloc(s->elem, s->stackSize * s->elemSize);
		if (!s->elem)
			exit(0);
	}
	/* 创建一个元素位置 */
	void *t = (char*)s->elem + s->destLen * s->elemSize;
	/* 拷贝内容 */
	memcpy(t, e, s->elemSize);
	/* 当前大小自增 */
	++s->destLen;
}
void StackPop(pStack s, ElemType e)
{
	if (!StackLen(s))
		exit(0);
	/* 先自减当前栈的位置 */
	--s->destLen;
	/* 获取批针位置 */
	void *source = (char*)s->elem + s->destLen * s->elemSize;
	/* 拷贝元素 */
	memcpy(e, source, s->elemSize);
}

int main()
{
	Stack s;
	const char* str[] = { "hello","world","good" };
	/* 初始化字符串元素大小为 10 */
	StackInit(&s, sizeof(char*));
	for (int i = 0; i < 3; i++) {
		StackPush(&s, (char*)&str[i]);
	}
	for (int i = 0; i < 3; i++) {
		char *getS;
		StackPop(&s, &getS);
		printf("The string %d is %s.\n", i, getS);
	}
	StackDestroy(&s);

	StackInit(&s, sizeof(int));
	int arr[3] = { 5,6,7 };
	for (int i = 0; i < 3; i++) {
		StackPush(&s, (char*)&arr[i]);
	}
	for (int i = 0; i < 3; i++) {
		int num;
		StackPop(&s, &num);
		printf("The string %d is %d.\n", i, num);
	}
	StackDestroy(&s);
	return 0;
}