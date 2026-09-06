#include<iostream>
using namespace std;

class CObject
{
public:
	virtual void Serialize()
	{
		cout<<"Object::Serialize()..."<<endl;
	}
};

class CDocument:public CObject
{
	int data1_;
public:
	void func()
	{
		cout<<"CDocument::func()..."<<endl;
		Serialize();
	}
	void Serialize()
	{
		cout<<"CDocument::Serialize()..."<<endl;
	}
};
class CMydoc:public CDocument
{
public:
	int data2_;
	void Serialize()
	{
		cout<<"CMyodc::Serialize()..."<<endl;
	}
};

int main()
{
	CMydoc mydoc;
	CMydoc * pmydoc=new CMydoc;
	cout<<"#1 testing"<<endl;
	mydoc.func();

	cout<<"#2 testing"<<endl;
	((CDocument*)(&mydoc))->func();//取地址强制转换成基类的指针

	cout<<"#3 testing"<<endl;
	pmydoc->func();

	cout<<"#4 testing"<<endl;
	((CDocument)mydoc).func();//mydoc对象强制转换为CDocument对象



	return 0;
}