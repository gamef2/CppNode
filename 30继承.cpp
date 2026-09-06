#include<iostream>
using namespace std;

class ObjectB
{
public:
	ObjectB(int objb):objb_(objb)
	{
		cout<<"ObjectB..."<<endl;
	}
	~ObjectB()
	{
		cout<<"~ObjectB..."<<endl;
	}
	int objb_;
};
class ObjectD
{
public:
	ObjectD(int objd):objd_(objd)
	{
		cout<<"ObjectD..."<<endl;
	}
	~ObjectD()
	{
		cout<<"~ObjectD..."<<endl;
	}
	int objd_;
};
/////
class Base
{

public:
	Base(int b=0):b_( b),objb_(111)
	{
		cout<<"Base::b_"<<endl;
	}
	Base(const Base& other):objb_(other.objb_),b_(other.b_)
	{
		/*b_=other.b_;*/
	}
	~Base()
	{
		cout<<"~Base"<<endl;
	}
//private:
	ObjectB objb_;

	int b_;
	
};

class Derived:public Base
{
public:

	Derived(int b=0,int d=0):d_(d),Base(b),objd_(222)
	{
		cout<<"Derived...."<<endl;
	}
	Derived(const Derived& other):Base(other),objd_(other.objd_),d_(other.d_)
	{

	}
	~Derived()
	{
		cout<<"~Derived..."<<endl;
	}

//private:
	ObjectD objd_;

	int d_;
};
//
int main()
{
	Derived d(100,200);
	Derived d1(d);
	cout<<d.b_<<" "<<d.d_<<endl;
	cout<<d.objb_.objb_<<" "<<d.objd_.objd_<<endl;
	cout<<"--------------------------"<<endl;
	cout<<d1.b_<<" "<<d1.d_<<endl;
	cout<<d1.objb_.objb_<<" "<<d1.objd_.objd_<<endl;
	system("pause");
	return 0;//
}

//#include<iostream>
//using namespace std;
//
//
//class A
//{
//	int a_;
//public:
//	A(int a):a_(a)
//	{
//
//	}
//	A(A& other):a_(other.a_)
//	{
//
//	}
//	~A()
//	{
//
//	}
//};
//class B:public A
//{
//	int b_;
//public:
//	B(int a,int b):A(a),b_(b)
//	{
//
//	}
//	B(B& other):A(other),b_(other.b_)
//	{
//		
//	}
//	~B()
//	{
//
//	}
//};
//
//int main()
//{
//	B b(10,20);
//	B b1(b);
//
//}

