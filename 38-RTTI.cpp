#include<iostream>
#include <string>
using namespace std;

class Shape
{
public:
	virtual void Draw()=0;
	virtual ~Shape(){}
};

class Circle:public Shape
{
public:
	void Draw()
	{
		cout<<"Circle Draw..."<<endl;
	}
};
class Square:public Shape
{
public:
	void Draw()
	{
		cout<<"Square Draw..."<<endl;
	}
};



int main()
{
	Shape* p;
	Circle c;
	p=&c;//基类指针指向派生类的对象
	p->Draw();//经由基类指针调用虚函数,它调用的是派生类的虚函数
//如果这个指针能经过dynamic_cast运算。能够进行转换，它得到的是Circle类指针
	//派生类指针，如果这个指针能够转换。则它的真正对象是Circle类对象
	if(dynamic_cast<Circle*>(p))//要在多态关系的继承体系上.就是基类有虚函数
	{
		cout<<"p is point to a Circle Object"<<endl;
		Circle* cp=dynamic_cast<Circle*>(p);//这句实际就是安全的向下转型
		cp->Draw();
	}
	else if(dynamic_cast<Square*>(p))
	{
		cout<<"p is point to a Square Object"<<endl;
	}
	else
	{
		cout<<"p is point to a other Object"<<endl;
	}
	cout<<typeid(*p).name()<<endl;//返回的是type_info。name就是对象实际的类型
	int len=strlen(typeid(*p).name())+1;
	char *newstr=new char[len];
	memset(newstr,0,len);
	memcpy(newstr,typeid(*p).name(),len-1);
	cout<<"转换成功:"<<newstr<<endl;
	delete[] newstr;

	if (typeid(Circle).name()==typeid(*p).name())//可以用在类型上或对象上
	{
		cout<<"p is point to a Circle Object"<<endl;
		((Circle*)p)->Draw();
	}
	else if (typeid(Square).name()==typeid(*p).name())//可以用在类型上或对象上
	{
		cout<<"p is point to a Circle Object"<<endl;
		((Square*)p)->Draw();
	}
	else
	{
		cout<<"p is point to a other Object"<<endl;
	}


	return 0;
}