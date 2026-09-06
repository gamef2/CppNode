#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Shape
{
public:
	virtual void Draw() = 0;
	virtual ~Shape() {}//如果不用虚析构函数,将不会调用派生类的析构函数
};//抽象类不能实例化

class Circle :public Shape
{
public:
	void Draw()
	{
		cout << "Circle::Draw()..." << endl;
	}
	~Circle()
	{
		cout << "~Circle()..." << endl;
	}
};

class Square :public Shape
{
public:
	void Draw()
	{
		cout << "Square::Draw()..." << endl;
	}
	~Square()
	{
		cout << "~Square()..." << endl;
	}
};

class Rectangle :public Shape
{
public:
	void Draw()
	{
		cout << "Rectangle::Draw()..." << endl;
	}
	~Rectangle()
	{
		cout << "~Rectangle()..." << endl;
	}
};
void DrawAllShape(const vector<Shape*>& v)
{
	vector<Shape*>::const_iterator it;//*it=shape*
	for (it = v.begin(); it != v.end(); ++it)
	{
		(*it)->Draw();
	}
}
void DeleteAllShape(const vector<Shape*>& v)
{
	vector<Shape*>::const_iterator it;//*it=shape*
	for (it = v.begin(); it != v.end(); ++it)
	{
		delete (*it);
	}
}
//第二种方案1
class ShapeFactory
{
public:
	static Shape* CreateShape(const string &name)
	{
		Shape* ps=nullptr;
		if (name == "Circle")
		{
			ps = new Circle;
		}
		else if (name == "Square")
		{
			ps = new Square;
		}
		else if (name == "Rectangle")
		{
			ps = new Rectangle;
		}
		return ps;
	}
};

int main()
{
	//Shape s;//“Shape”: 不能实例化抽象类
	vector<Shape*> v;//容器保存形状
	//第一种方案
	/*Shape* ps;
	ps=new Circle;//new一个Circle
	v.push_back(ps);//将形状放到向量当中.vector
	ps=new Square;
	v.push_back(ps);
	ps=new Rectangle;
	v.push_back(ps);*/


	//第二种方案2
	Shape* ps;
	ps = ShapeFactory::CreateShape("Circle");
	v.push_back(ps);
	ps = ShapeFactory::CreateShape("Square");
	v.push_back(ps);
	ps = ShapeFactory::CreateShape("Rectangle");
	v.push_back(ps);
	DrawAllShape(v);
	DeleteAllShape(v);
	return 0;
}