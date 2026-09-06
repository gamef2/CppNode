#include "Shape.h"
#include "DynBase.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<Shape*> Pointer_;

void DrawAllShape(Pointer_& v)
{
	Pointer_::const_iterator it;
	for (it=v.begin();it != v.end();++it)
	{
		(*it)->Draw();
	}
}
void DeleteAllShape(Pointer_& v)
{
	Pointer_::const_iterator it;
	for (it=v.begin();it != v.end();++it)
	{
		delete(*it);
	}
}

//class ShapeFactory
//{
//public:
//	static Shape* CreateShape(const string& name)
//	{
//		Shape* p;
//		if (name=="Circle")
//			p=new Circle;
//		if (name=="Square")
//			p=new Square;
//		if (name=="Rectangle")
//			p=new Rectangle;
//		return p;
//	}
//};

int main()
{
	Pointer_ v;
	Shape* p=static_cast<Shape*>(DynObjectFactory::CreateObject(("Circle")));
	v.push_back(p);
	p=static_cast<Shape*>(DynObjectFactory::CreateObject("Square"));
	v.push_back(p);
	p=static_cast<Shape*>(DynObjectFactory::CreateObject("Rectangle"));
	v.push_back(p);
	DrawAllShape(v);
	DeleteAllShape(v);


}