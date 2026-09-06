#include<iostream>
#include <string>
#include <map>
using namespace std;

typedef map<int ,int> INTVER;
typedef map<char,int> INTVER_;
//int main()
//{
//	INTVER num;
//	int i;
//	cout<<"请输入数字以0结束"<<endl;
//	while(cin>>i&&i!=0)
//	{
//		++num[i];
//	}
//	INTVER::const_iterator it;
//	int sum=0;
//	for (it=num.begin();it!=num.end();++it)
//	{
//		cout<<it->first<<"出现 "<<it->second<<"次"<<endl;
//		sum+=it->first;
//	}
//	cout<<"统计输入的数总和:"<<sum<<endl;
//}

int main()
{
	char number;
	cout<<"请输入一个数字以y结束"<<endl;
	

	INTVER_ num;
	while(cin>>number&&number!='y')
	{
		++num[number];
	}
	INTVER_::const_iterator it;
	for (it=num.begin();it!=num.end();++it)
	{
		cout<<it->first<<"出现 "<<it->second<<"次"<<endl;
		
	}
}