#include<iostream>
#include <string>
using namespace std;

class Manager;
class Manager2;

class Employee
{
  public:
	Employee(const string & name, const int age, const int deptno):name_(name), age_(age),
		deptno_(deptno)
	{

	}
	operator   Manager();
	operator   Manager2();
  private:
	string name_;
	int age_;
	int deptno_;
};

class Manager:public Employee
{
  public:
	Manager(const string & name, const int age, const int deptno, int level):Employee(name, age,
																					  deptno),
		level_(level)
	{

	}
	/* Manager(const Employee& other):Employee(other),level_(-1) {

	   } */
  private:
	int level_;
};

Employee::operator   Manager()
{
	return Manager(name_, age_, deptno_, -1);
}

class Manager2:private Employee
{
  public:
	Manager2(const string & name, const int age, const int deptno, int level):Employee(name, age,
																					   deptno),
		level_(level)
	{

	}
	/* Manager2(const Employee& other):Employee(other),level_(1) {

	   } */
  private:
	int level_;
};

Employee::operator   Manager2()
{
	return Manager2(name_, age_, deptno_, -1);
}

int main()
{
	Employee e1("张三", 25, 20);
	Manager m1("李四", 38, 20, 10);
	Manager2 m2("王五", 40, 15, 8);
	Employee *pe;
	Manager *pm;
	Manager2 *pm2;

	pe = &e1;					// 基类指针指向基类对象(可以)
	pm = &m1;					// 派生类指针指向派生类对象(可以)
	pm2 = &m2;
	// -------------------------------
	pe = &m1;					// 基类指针指向公有继承派生类对象(可以)//派生类指针可以转化成基类指针
	pe = pm;					// 基类指针可以指向公有继承的派生类指针
	pe = reinterpret_cast < Employee * >(pm2);	// 基类不能指向私有继承的派生类指针,
	// 但能指向强制转换的私有继承的派生类指针

	// 私有继承派生类指针不能直接转换成基类指针,但能强制转换
	// --------------------------------------------------
	// pm=&e1;//公有继承派生类指针无法指向基类对象(不可以)//基指针不可以转化成公有继承派生类指针
	pm = static_cast < Manager * >(&e1);	// 公有继承派生类指针可以指向被强制转换的基类对象
	pm = static_cast < Manager * >(pe);	// 基类指针无法转换成公有继承派生类指针,但可以强制转换//不安全
	// --------------------------------------------------
	pm2 = reinterpret_cast < Manager2 * >(&e1);	// 私有继承只能指向被强制转换的基类对象
	pm2 = reinterpret_cast < Manager2 * >(pe);	// 基类指针无法转换成私有继承派生类指针,但可以强制转换//不安全


	e1 = m1;					// 派生类对象可以转换成基类对象//转换过程派生类特有的成员消失了

	// m1=reinterpret_cast<Manager>(e1);//基类对象不能转化成派生类对象,派生类对象不能指向基类对象


	// e1=static_cast<Employee>(m2);//私有派生类对象不可以转换成基类对象
	cout << "添加类型转换构造函数后" << endl;
	m1 = e1;					// Manager加入转换构造函数Manager(const 
								// 
	// Employee&
	// other):Employee(other),level_(-1)后可以转换
	m2 = e1;
}
