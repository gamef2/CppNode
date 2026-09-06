#ifndef _DYN_BASE_H_
#define _DYN_BASE_H_

#include <map>
#include <string>
using namespace std;



typedef void* (*CREATE_FUNC)();//1创建方法
 class DynObjectFactory
 {
 public:
	 static void* CreateObject(const string& name)//接口
	 {
		 map<string,CREATE_FUNC>::const_iterator it;
		 it=mapCls_.find(name);//查找name
		 if (it==mapCls_.end())
			 return 0;
		 else
			 return it->second();
	 }
	 static void Register(const string& name,CREATE_FUNC func)//5注册方法
	 {
		mapCls_[name]=func;
	 }
 private:
	 static map<string,CREATE_FUNC> mapCls_;//2保存字符串/动态创建类的信息
 };
 _declspec(selectany) map<string,CREATE_FUNC> DynObjectFactory::mapCls_;

 class Register//6调用DynObjectFactory::Register
 {
 public:
	 Register(const string& name,CREATE_FUNC func)
	 {
		 DynObjectFactory::Register(name,func);
	 }
 };
//4传递class类/并注册到map的string

#define  REGISTER_CLASS(class_name) \
 class class_name##Register { \
 public:\
	static void* NewInstance() \
	{\
		return new class_name;\
	}\
 private:\
	static Register reg_;\
 };\
 Register class_name##Register::reg_(#class_name,class_name##Register::NewInstance)

#endif