#include "Shape.h"
#include "DynBase.h"
#include <iostream>
using namespace std;

void Circle::Draw()
{
	cout<<"Circle::Draw..."<<endl;
}

Circle::~Circle()
{
	cout<<"~Circle..."<<endl;
}

void Square::Draw()
{
	cout<<"Square::Draw..."<<endl;
}

Square::~Square()
{
	cout<<"~Square..."<<endl;
}

void Rectangle::Draw()
{
	cout<<"Rectangle::Draw..."<<endl;
}

Rectangle::~Rectangle()
{
	cout<<"~Rectangle..."<<endl;
}

//3注册动态创建类名
class CircleRegister 
{ 
public:
	static void* NewInstance() 
	{
	return new Circle;
	}
private:
	static Register reg_;
};
Register CircleRegister::reg_("Circle",CircleRegister::NewInstance);
//REGISTER_CLASS(Circle);
REGISTER_CLASS(Square);
REGISTER_CLASS(Rectangle);

