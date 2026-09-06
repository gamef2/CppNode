#include <iostream>
using namespace std;

class Rectangle
{
private:
	double width;
	double length;
public:
	Rectangle(double w=0,double l=0)
	{
		width=w;
		length=l;
	}
	~Rectangle()
	{

	}
	void Set_Width_Length(double w,double l)
	{
		width=w;
		length=l;
	}
	void Rectangle_Perimeter()
	{
		cout<<"(长+宽)乘2 周长=\t"<<(width+length)*2<<endl;//计算周长
	}
	void Rectangle_area()
	{
		cout<<"长乘宽\t面积=\t\t"<<width*length<<endl;//计算面积
	}
};
int main()
{
	Rectangle rectangle;//创建对象rectangle
	char c;//用来接收y或n
	double w,l;//定义传值变量
	while(1)//进入循环
	{
		cout<<"----计算矩形周长与面积-----\n"<<endl;
		cout<<"请输入Width:\t";cin>>w;//输入长
		cout<<"请输入Length:\t";cin>>l;//输入宽
		rectangle.Set_Width_Length(w,l);//调用对象成员给长宽赋值
		rectangle.Rectangle_Perimeter();//调用对象成员函数计算周长
		rectangle.Rectangle_area();//调用对象成员函数计算面积
		cout<<"是否继续Y/N"<<endl;
		cin>>c;
		while(c!='y'&&c!='n'&&c!='Y'&&c!='N')//当不是大写或小写的y或n时循环直到输入正确
		{
			cout<<"输入错误!请重新输入"<<endl;
			cout<<"是否继续Y/N"<<endl;
			cin>>c;
		}
		if (c!='y'&&c!='Y')//当等于y或Y时继续,否则退出
		{
			break;
		}
	}

	cout<<"退出成功!"<<endl;
	return 0;
}