#include <iostream>
#include <assert.h>
using namespace std;

struct Line
{
	int num;
	struct Line* next_;
};
struct Stack
{
	struct Line* head_;
	int size_;
};
void InitStack(struct Stack* stack)
{
	stack->head_=NULL;
	stack->size_=0;
}
void PushStack(struct Stack* stack,int data)
{
	Line* node=(struct Line*)malloc(sizeof(struct Line));
	assert(node!=NULL);
	node->num=data;
	node->next_=stack->head_;
	stack->head_=node;
	stack->size_++;
}
bool EmptyStack(struct Stack* stack)
{
	return stack->size_==0;
}
int PopStack(struct Stack* stack,int &data)
{
	if (EmptyStack(stack))
	{
		return 0;
	}
	Line* tmp=stack->head_;
	data=stack->head_->num;
	stack->head_=stack->head_->next_;
	free(tmp);
	stack->size_--;
	return 1;
}
void StackClearup(struct Stack* stack)
{
	struct Line* tmp;
	while(stack->head_)
	{
		tmp=stack->head_;
		stack->head_=stack->head_->next_;
		free(tmp);
	}
	stack->size_=0;
}

int main()
{
	Stack stack;
	InitStack(&stack);
	int i;
	for(i=1;i<=5;i++)
	{
		PushStack(&stack,i);
	}
	while(!EmptyStack(&stack))
	{
		PopStack(&stack,i);
		cout<<i<<" ";
	}
	return 0;
}