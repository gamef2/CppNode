#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

class Student 
{
public:
	char name_[100];
	int age_;

	Student* head_;
	Student* saved_;
	Student* next_;
	Student()
	{
		head_=saved_=next_=NULL;
	}

	virtual void store(char *name="",int age=0)=0;
	virtual void retrieve(char *name,int &age)=0;
	virtual void Display(Student *p)=0;
};

class Queue:public Student
{
public:
	void store(char *name/* ="" */,int age);
	void retrieve(char *name,int &age);
	void Display(Student *p);
};

void Queue::store(char *name,int age)
{
	Student *stu=new Queue;
	if (!stu)
	{
		cout<<"error"<<endl;
		exit(1);
	}
	strcpy(stu->name_,name);
	
	stu->age_=age;
	if (saved_)
	{
		saved_->next_=stu;
	}
	saved_=stu;
	stu->next_=NULL;
	if (!head_)
	{
		head_=saved_;
	}
}
void Queue::retrieve(char *name,int &age)
{
	if (!head_)
	{
		cout<<"empty"<<endl;
		exit(1);
	}
	Student* p=head_;
	strcpy(name,head_->name_);
	age=head_->age_;
	Display(p);
	head_=head_->next_;
	delete p;

}
void Queue::Display(Student *p)
{
	cout<<"队列显示："<<p->name_<<"\t "<<p->age_<<endl;
}

class Stack:public Student
{
public:
	void store(char *name/* ="" */,int age/* =0 */);
	void retrieve(char *name,int &age);
	void Display(Student *p);
};
void Stack::store(char *name,int age)
{
	Student *stu=new Stack;
	if (!stu)
	{
		cout<<"error"<<endl;
		exit(1);
	}
	strcpy(stu->name_,name);
	stu->age_=age;
	stu->next_=head_;
	head_=stu;
	stu->head_=NULL;
	if (!saved_)
	{
		saved_=head_;
	}
}
void Stack::retrieve(char *name,int &age)
{
	if (!head_)
	{
		cout<<"empty"<<endl;
		exit(1);
	}
	Student* p;
	p=head_;
	strcpy(name,head_->name_);
	age=head_->age_;
	Display(p);
	head_=head_->next_;
	delete p;

}

void Stack::Display(Student *p)
{
	cout<<"栈显示："<<p->name_<<"\t "<<p->age_<<endl;
}

int main()
{
	char ch[100];
	int age,i,num;
	Student *p;
	Queue qb;
	p=&qb;
	
	cout<<"请输入多少人"<<endl;
	cin>>num;
	for (i=0;i<num;i++)
	{
		cout<<"请输入姓名与年龄:"<<endl;
		cin>>ch>>age;
		p->store(ch,age);
	}
	for (i=0;i<num;i++)
	{
		p->retrieve(ch,age);
	}
	Stack st;
	p=&st;

	cout<<"请输入多少人"<<endl;
	cin>>num;
	for (i=0;i<num;i++)
	{
		cout<<"请输入姓名与年龄:"<<endl;
		cin>>ch>>age;
		p->store(ch,age);
	}
	for (i=0;i<num;i++)
	{
		p->retrieve(ch,age);
	}
	return 0;
}