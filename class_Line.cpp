#include <iostream>
using namespace std;

class Stack
{
	typedef struct Line
	{
		int num_;
		Line* next_;
		Line(int num,Line* next):num_(num),next_(next)
		{

		}
	};
public:
	Stack():head_(0),size_(0)
	{

	}
	~Stack()
	{
		Line* tmp;
		while(head_)
		{
			tmp=head_;
			head_=head_->next_;
			delete tmp;
		}
		size_=0;
	}
	void Push(int num)
	{
		Line* node=new Line(num,head_);
		head_=node;
		++size_;
	}
	bool Empty()
	{
		return size_==0;
	}
	int Pop(int &num)
	{
		if (Empty())
		{
			return false;
		}
		Line* tmp=head_;
		num=head_->num_;
		head_=head_->next_;
		delete tmp;
		--size_;
		return true;
	}
private:
	Line* head_;
	int size_;
};
int main()
{
	Stack stack;
	int i;
	for (i=1;i<=5;i++)
	{
		stack.Push(i);
	}
	while(!stack.Empty())
	{
		stack.Pop(i);
		cout<<" "<<i;
	}
	return 0;
}