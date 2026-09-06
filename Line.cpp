#include <iostream>
#include <assert.h>
using namespace std;


struct Line
{
	int num_;
	int size_;
	struct Line* head_;
	struct Line* next_;
};
void InitLine(struct Line* line)
{
	line->head_=NULL;
	line->size_=0;
}
bool EmptyLine(struct Line* line)
{
	return (line->size_==0);
}

void FirstLine(struct Line* line,int num)
{
	struct Line* node=(struct Line*)malloc(sizeof(struct Line));
	assert(node!=NULL);
	node->num_=num;
	node->next_=line->head_;
	line->head_=node;
	++line->size_;

}

int LastLine(struct Line* line,int &num)
{
	if (EmptyLine(line))
	{
		return 0;
	}
	struct Line *tmp=line->head_;
	num=line->head_->num_;
	line->head_=line->head_->next_;
	free(tmp);
	--line->size_;
	return 1;
}
void  ClearLine(struct Line* line)
{
	struct Line* tmp;
	while(line->head_)
	{
		tmp=line->head_;
		line->head_=line->head_->next_;
		free(tmp);
	}
	line->size_=0;
}
int main()
{
	Line line;
	int i=0;
	InitLine(&line);
	for (i=1;i<=10;i++)
	{
		FirstLine(&line,i);
		cout<<i<<" ";
	}
	cout<<endl;
	
	while(!EmptyLine(&line))
	{
		LastLine(&line,i);
		cout<<i<<" ";
	}
	cout<<endl;
	return 0;
}