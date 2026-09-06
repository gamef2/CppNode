/*
#include<iostream>
using namespace std;

class Base
{
public:
	virtual void Fun1()
	{
		cout<<"Base::Fun1()..."<<endl;
	}
	virtual void Fun2()
	{
		cout<<"Base::Fun2()..."<<endl;
	}

	void Fun3()
	{
		cout<<"Base::Fun3()..."<<endl;
	}
	
};

class Derived:public Base
{
public:
	 void Fun1()
	{
		cout<<"Derived::Fun1()..."<<endl;
	}
	void Fun2()
	{
		cout<<"Derived::Fun2()..."<<endl;
	}
	void Fun3()
	{
		cout<<"Derived::Fun3()..."<<endl;
	}
	
};





int main()
{
	
	Base *p;
	Derived d;
	p=&d;
	p->Fun1();//Fun1是虚函数,基类的指针指向派生类对象时,调用的是派生类的对象的虚函数
	p->Fun2();
	p->Fun3();//Fun3非虚函数,根据p指针实际类型来调用相应函数
	return 0;
}
*/
//第二部分析构部分
/*
#include<iostream>
using namespace std;

class Base
{
public:
	virtual void Fun1()
	{
		cout<<"Base::Fun1()..."<<endl;
	}
	virtual void Fun2()
	{
		cout<<"Base::Fun2()..."<<endl;
	}

	void Fun3()
	{
		cout<<"Base::Fun3()..."<<endl;
	}
	Base()
	{
		cout<<"Base()..."<<endl;
	}
	//如果一个类要作为多态基类,要将基类析构函数定义成虚析构函数
	virtual ~Base()//这里加上virtual保证p会认为调用的是p 所指向的类类型，派生类,
		//调用派生类的析构防止内存泄露
	{
		cout<<"~Base()..."<<endl;
	}
//如果一个类永远不会被派生类继承.那也没有必要将它定义成虚析构函数
	//当你通过基类指针删除派生类对象的时候,如果没定义虚析构函数.它只会调用基类的析构函数.//
	//不会调用派生类的析构函数
};

class Derived:public Base
{
public:
	void Fun1()
	{
		cout<<"Derived::Fun1()..."<<endl;
	}
	void Fun2()
	{
		cout<<"Derived::Fun2()..."<<endl;
	}
	void Fun3()
	{
		cout<<"Derived::Fun3()..."<<endl;
	}
	Derived()
	{
		cout<<"Derived()..."<<endl;
	}

	~Derived()
	{
		cout<<"~Derived()..."<<endl;
	}

};





int main()
{
	Base* p;
	p=new Derived;//基类指针指向派生类对象.构造一个派生类对象
	p->Fun1();//基类指针指向派生类对象,调用虚函数。肯定会调用派生类的虚函数
	delete p;//如果析构函数不是虚的，它会根据p这个类型来调用析构函数
	//p等于基类类型。很自然就调用基类类型。
	//如果析构函数是虚的，p会认为调用的是p 所指向的类类型，派生类
	

	return 0;
}
*/
//第三部分虚表指针

#include<iostream>
using namespace std;

class Base//头四个字节是指向虚表的指针
{//
public:
/*private:*///虚函数与成员公有私有无关
	virtual void Fun1()
	{
		cout<<"Base::Fun1()..."<<endl;
	}
	virtual void Fun2()
	{
		cout<<"Base::Fun2()..."<<endl;
	}
	

	int data1_;
	
};

class Derived:public Base
{
public:
	
	void Fun2()
	{
		cout<<"Derived::Fun2()..."<<endl;
	}
	virtual void Fun3()
	{
		cout<<"Derived::Fun3()..."<<endl;
	}
	int data2_;

};


typedef void(*Func)();//定义一个函数指针


int main()
{
	//vptr->vbtl虚函数入口地址base::Fun1,Base::Fun2

	cout<<sizeof(Base)<<endl;
	cout<<sizeof(Derived)<<endl;
	Base b;
	long ** p=(long **)&b;

	Func fun=(Func)p[0][0];//将这个指针强制转换成Func,这个指针就是指向基类的虚函数
	fun();//调用一下.
	fun=(Func)p[0][1];
	fun();
	Derived d;
	p=(long**)&d;

	//第一个是基类的.第二与三是派生类的fun
	fun=(Func)p[0][0];
	fun();
	fun=(Func)p[0][1];
	fun();
	fun=(Func)p[0][2];
	fun();

	Base *pp=&d;
	pp->Fun2();
	Base *pb=new Derived;
	pb->Fun2();
	return 0;
}