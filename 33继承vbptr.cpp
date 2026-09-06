#include<iostream>
using namespace std;

class BB
{
public:
	int bb_;

};
class B1:virtual public BB
{
public:
	int b1_;

};

class B2:virtual public BB
{
public:
	int b2_;
};

class DD:public B1,public B2
{
public:
	int dd_;
};

int main()
{
	cout<<sizeof(BB)<<endl;
	cout<<sizeof(B1)<<endl;
	cout<<sizeof(DD)<<endl;
		
		
	B1 b1;
	cout<<&b1<<endl;	
	cout<<&b1.bb_<<endl;
	cout<<&b1.b1_<<endl;
	//&b1		001AFE4C//类对象首地址virtual base table pointer//本类地址
	//vbptr虚基类表指针1：vbtl本类地址与虚基类表指针地址的差0	
	//2:虚基类地址与虚基类表指针地址的差8
	
	//&b1.b1_	001AFE50
	//虚基类地址
	//&b1.bb_	001AFE54//虚基类部分	BB

	long** p=(long**)&b1;
	cout<<p[0][0]<<endl;//p[0][0]=vbptr取出第0项
	cout<<p[0][1]<<endl;//取出第一项

	DD dd;
	cout<<&dd<<endl;
	cout<<&dd.bb_<<endl;
	cout<<&dd.b1_<<endl;
	cout<<&dd.b2_<<endl;
	cout<<&dd.dd_<<endl;
	//&dd		002AF830	类对象首地址virtual base table pointer//本类地址b1虚基类地址与虚基类指针表指针地址间隔5
	//&dd.b1_	002AF834	b1
	//vbptr		002AF838	b2虚基类地址与虚基类指针表指针地址间隔3
	//&dd.b2_	002AF83C	b2
	//&dd.dd_	002AF840
	//&dd.bb_	002AF844	BB包含b1,b2

	p=(long**)&dd;
	cout<<p[0][0]<<endl;
	cout<<p[0][1]<<endl;
	cout<<p[2][0]<<endl;
	cout<<p[2][1]<<endl;

	BB* pp;
	pp=&dd;
	pp->bb_;//经由BB指针访问虚基类成员//通过间接访问,需要运行时支持
	return 0;
}
